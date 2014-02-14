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
	virtual ~NodeConnectivityData(){};
	virtual bool isChild() = 0;
	virtual Node** getParentNodes() = 0;
	virtual int getParentNodeCount() = 0;
	virtual Node** getSiblingNodes() = 0;
	virtual int getSiblingNodeCount() = 0;
	virtual Node** getChildNodes() = 0;
	virtual int getChildNodeCount() = 0;
private:
};

/**
 * \class NodeConnectivityChildData
 */
class NodeConnectivityChildData : public NodeConnectivityData {
public:
	NodeConnectivityChildData(unsigned long revisionId);
	virtual bool isChild() {return true;}
	virtual Node** getParentNodes() {return parentNodes;}
	virtual int getParentNodeCount() {return 2;}
	virtual Node** getSiblingNodes() {return siblingNodes;}
	virtual int getSiblingNodeCount() {return 4;}
	virtual Node** getChildNodes() {return childNodes;}
	virtual int getChildNodeCount() {return 6;}
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
	NodeConnectivityRootData(unsigned long revisionId);
	virtual bool isChild() {return false;}
	virtual Node** getParentNodes() {return 0;}
	virtual int getParentNodeCount() {return 0;}
	virtual Node** getSiblingNodes() {return siblingNodes;}
	virtual int getSiblingNodeCount() {return 5;}
	virtual Node** getChildNodes() {return childNodes;}
	virtual int getChildNodeCount() {return 5;}
private:
	Node* siblingNodes[5];
	Node* childNodes[5];
};

#endif
