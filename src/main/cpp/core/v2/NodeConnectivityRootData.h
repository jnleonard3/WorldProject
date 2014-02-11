/**
 * \file NodeConnectivityRootData.h
 * \author Jon Leonard
 * \date 2014/02/10
 * \copyright The BSD 2-Clause License
 */
#ifndef NODE_CONNECTIVITY_ROOT_DATA_H_
#define NODE_CONNECTIVITY_ROOT_DATA_H_

/**
 * \class NodeConnectivityRootData
 */
class NodeConnectivityRootData : public NodeConnectivityData {
public:
	NodeConnectivityRootData(unsigned long revisionId):NodeConnectivityData(revisionId){}
private:
	Node*[] siblingNodes = Node*[5];
	Node*[] childNodes = Node*[5];
};

#endif