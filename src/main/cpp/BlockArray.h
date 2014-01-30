/*
 * BlockArray.h
 *
 *  Created on: Jul 26, 2011
 *      Author: Jon
 */

#ifndef BLOCKARRAY_H_
#define BLOCKARRAY_H_

#include "SimpleDynamicArray.h"

template<class T>
class BlockArray {
public:
	BlockArray(unsigned int blockSize = 256) :
		mBlockPointers(), mBlockSize(blockSize), mBlockCount(0), mElements(0) {
	}

	BlockArray(unsigned int size, unsigned int blockSize);

	unsigned int getBlockSize() const {
		return mBlockSize;
	}

	unsigned int getSize() const {
		return mElements;
	}

	unsigned int getBlockCount() const {
		return mBlockCount;
	}

	T& pushBack(T data);

	void resize(unsigned int size);

	/**
	 *   Gets the block number which the current index resides in
	 */
	unsigned int getBlockIndex(unsigned int index) const;

	void swapBlocks(unsigned int indexFrom, unsigned int indexTo);
	void moveBlock(unsigned int indexFrom, unsigned int indexTo);
	void deleteBlock(unsigned int index);

	unsigned int getIndexOfAddress(const T* const address) const;

	unsigned int getElementsPerBlock() const;
	unsigned int getMemoryUsage() const;

	T& at(unsigned int index);
	const T& at(unsigned int index) const;

	T& operator[](unsigned int index) {
		return this->at(index);
	}
	;
	const T& operator[](unsigned int index) const {
		return this->at(index);
	}
	;

private:
	T* initializeNewBlock() const;
	void clearBlock(T* block);
	unsigned int getBlockOffset(unsigned int index) const;

	SimpleDynamicArray<T*> mBlockPointers;
	unsigned int mBlockSize, mBlockCount, mElements;
};

template<class T>
BlockArray<T>::BlockArray(unsigned int size, unsigned int blockSize) :
	mBlockPointers(), mBlockSize(blockSize), mBlockCount(0), mElements(size) {
	mBlockCount = (size / this->getElementsPerBlock()) + 1;
	mBlockPointers.resize(mBlockCount);
	for (unsigned int i = 0; i < mBlockPointers.getSize(); ++i)
		mBlockPointers[i] = this->initializeNewBlock();
}

template<class T>
T& BlockArray<T>::pushBack(T data) {
	this->resize(this->getSize() + 1);
	this->at(this->getSize() - 1) = data;
	return this->at(this->getSize() - 1);
}

template<class T>
void BlockArray<T>::resize(unsigned int size) {
	unsigned int newBlockCount = (size / this->getElementsPerBlock()) + 1;
	// Clear the data in blocks if data would be truncated by the resize
	if (newBlockCount < mBlockCount)
		for (unsigned int i = mBlockCount - 1; i < (newBlockCount - 1); ++i)
			this->clearBlock(mBlockPointers[i]);

	// If there are going to be more blocks, initialize them
	if (newBlockCount > mBlockCount) {
		// Only resize the number of pointers if block count is greater
		mBlockPointers.resize(newBlockCount);

		for (unsigned int i = mBlockCount; i < mBlockPointers.getSize(); ++i)
			mBlockPointers[i] = this->initializeNewBlock();
	}

	mBlockCount = newBlockCount;
	mElements = size;
}

template<class T>
unsigned int BlockArray<T>::getBlockIndex(unsigned int index) const {
	return index / this->getElementsPerBlock();
}

template<class T>
void BlockArray<T>::swapBlocks(unsigned int indexFrom, unsigned int indexTo) {
	T* temp = mBlockPointers[indexFrom];
	mBlockPointers[indexFrom] = mBlockPointers[indexTo];
	mBlockPointers[indexTo] = temp;
}

template<class T>
void BlockArray<T>::moveBlock(unsigned int indexFrom, unsigned int indexTo) {
	T* temp;
	if (indexFrom > indexTo) {
		temp = mBlockPointers[indexFrom];
		for (unsigned int i = indexTo; i <= indexFrom; ++i) {
			T* tempTwo = mBlockPointers[i];
			mBlockPointers[i] = temp;
			temp = tempTwo;
		}
	} else {
		temp = mBlockPointers[indexFrom];
		for (unsigned int i = indexFrom + 1; i <= indexTo; ++i)
			mBlockPointers[i - 1] = mBlockPointers[i];
		mBlockPointers[indexTo] = temp;
	}
}

template<class T>
void BlockArray<T>::deleteBlock(unsigned int index) {
	T* temp = mBlockPointers[index];
	this->clearBlock(temp);
	for (unsigned int i = index + 1; i < mBlockCount; ++i)
		mBlockPointers[i - 1] = mBlockPointers[i];
	--mBlockCount;
	mBlockPointers[mBlockCount] = temp;
}

template<class T>
unsigned int BlockArray<T>::getIndexOfAddress(const T* const address) const {
	const unsigned int elemsPerBlock = this->getElementsPerBlock();
	for (unsigned int i = 0; i < mBlockCount; ++i) {
		unsigned int offset = address - mBlockPointers.at(i);
		if (offset < elemsPerBlock)
			return offset + (i * elemsPerBlock);
	}
	return mElements + 1;
}

template<class T>
unsigned int BlockArray<T>::getElementsPerBlock() const {
	return mBlockSize / sizeof(T);
}

template<class T>
unsigned int BlockArray<T>::getMemoryUsage() const {
	return mBlockSize * mBlockPointers.getSize();
}

template<class T>
T& BlockArray<T>::at(unsigned int index) {
	return mBlockPointers.at(this->getBlockIndex(index))[this->getBlockOffset(
			index)];
}

template<class T>
const T& BlockArray<T>::at(unsigned int index) const {
	return mBlockPointers.at(this->getBlockIndex(index))[this->getBlockOffset(
			index)];
}

template<class T>
T* BlockArray<T>::initializeNewBlock() const {
	return new T[this->getElementsPerBlock()];
}

template<class T>
void BlockArray<T>::clearBlock(T* block) {
	for (unsigned int i = 0; i < this->getElementsPerBlock(); ++i)
		block[i] = T();
}

template<class T>
unsigned int BlockArray<T>::getBlockOffset(unsigned int index) const {
	return index - this->getBlockIndex(index) * this->getElementsPerBlock();
}

#endif /* BLOCKARRAY_H_ */
