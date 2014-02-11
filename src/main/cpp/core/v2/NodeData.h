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
	NodeData(unsigned long revisionId):revisionId(revisionId){}
	unsigned long getRevisionId();
private:
	const unsigned long revisionId;
};

#endif