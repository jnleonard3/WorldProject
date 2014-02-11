/**
 * \file NodeConnectivityChildData.h
 * \author Jon Leonard
 * \date 2014/02/10
 * \copyright The BSD 2-Clause License
 */
#ifndef NODE_CONNECTIVITY_CHILD_DATA_H_
#define NODE_CONNECTIVITY_CHILD_DATA_H_

/**
 * \class NodeConnectivityChildData
 */
class NodeConnectivityChildData : public NodeConnectivityData {
public:
	NodeConnectivityChildData(unsigned long revisionId):NodeConnectivityData(revisionId){}
private:
	Node*[] parentNodes = Node*[2];
	Node*[] siblingNodes = Node*[4];
	Node*[] childNodes = Node*[6];
};

#endif