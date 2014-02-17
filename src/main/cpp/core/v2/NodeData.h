/**
 * \file NodeData.h
 * \author Jon Leonard
 * \date 2014/02/09
 * \copyright The BSD 2-Clause License
 */
#ifndef NODE_DATA_H_
#define NODE_DATA_H_

/**
 * \class NodeData
 */
class NodeData {
public:
	NodeData(unsigned long revision):revision(revision){}
	unsigned long getRevision() {return revision;}
	virtual NodeData* copy(unsigned long revision) = 0;
	virtual NodeData* copy() {return copy(revision);}
private:
	const unsigned long revision;
};

#endif
