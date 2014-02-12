/**
 * \file NodeConnectivityData.h
 * \author Jon Leonard
 * \date 2014/02/10
 * \copyright The BSD 2-Clause License
 */
#ifndef NODE_CONNECTIVITY_DATA_H_
#define NODE_CONNECTIVITY_DATA_H_

#include "NodeData.h"

class Node;

/**
 * \class NodeConnectivityData
 */
class NodeConnectivityData : public NodeData {
public:
	NodeConnectivityData(unsigned long revisionId):NodeData(revisionId){}
private:
};

/**
 * \class NodeConnectivityChildData
 */
class NodeConnectivityChildData : public NodeConnectivityData {
public:
	NodeConnectivityChildData(unsigned long revisionId):NodeConnectivityData(revisionId){}
private:
	Node* parentNodes[2];
	Node* siblingNodes[4];
	Node* childNodes[6];
};

/**
 * \class NodeConnectivityRootData
 */
class NodeConnectivityRootData : public NodeConnectivityData {
public:
	NodeConnectivityRootData(unsigned long revisionId):NodeConnectivityData(revisionId){}
private:
	Node* siblingNodes[5];
	Node* childNodes[5];
};

#endif