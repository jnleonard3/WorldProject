/**
 * \file ImmutableChildNode.h
 * \author Jon Leonard
 * \date 2014/02/10
 * \copyright The BSD 2-Clause License
 */
#ifndef IMMUTABLE_CHILD_NODE_H_
#define IMMUTABLE_CHILD_NODE_H_

/**
 * \class ImmutableChildNode
 */
class ImmutableChildNode : public ImmutableNode {
public:
	ImmutableChildNode(){};
private:
	unsigned long[] parentNodes = unsigned long[2];
	unsigned long[] siblingNodes = unsigned long[4];
	unsigned long[] childNodes = unsigned long[6];
};

#endif