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
	virtual NodeConnectivityData* copy(unsigned long revision) = 0;
	virtual NodeConnectivityData* copy(){return copy(getRevision());}
	virtual bool isChild() = 0;
	
	virtual Node** getParentNodes() = 0;
	virtual int getParentNodeCount() = 0;
	
	int getParentNodeIndex(unsigned long id);
	
	virtual Node** getSiblingNodes() = 0;
	virtual int getSiblingNodeCount() = 0;
	
	int getSiblingNodeIndex(unsigned long id);
	
	virtual Node* getEffectiveSiblingNode(int index) = 0;
	
	virtual Node** getChildNodes() = 0;
	int getChildNodeCount() {return getParentNodeCount() + getSiblingNodeCount();}
	virtual void setChildNode(bool isParentIndex, int index, Node *node) = 0;
	
	int getChildNodeIndex(unsigned long id);
	
	void merge(NodeConnectivityData *other);
private:
};

/**
 * \class NodeConnectivityChildData
 */
class NodeConnectivityChildData : public NodeConnectivityData {
public:
	NodeConnectivityChildData(unsigned long revisionId);
	virtual NodeConnectivityChildData* copy(unsigned long revision);
	virtual NodeConnectivityChildData* copy(){return copy(getRevision());}
	virtual bool isChild() {return true;}
	virtual Node** getParentNodes() {return parentNodes;}
	virtual int getParentNodeCount() {return 2;}
	virtual Node** getSiblingNodes() {return siblingNodes;}
	virtual int getSiblingNodeCount() {return 4;}
	virtual Node* getEffectiveSiblingNode(int index);
	virtual Node** getChildNodes() {return childNodes;}
	virtual void setChildNode(bool isParentIndex, int index, Node *node);
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
	virtual NodeConnectivityRootData* copy(unsigned long revision);
	virtual NodeConnectivityRootData* copy(){return copy(getRevision());}
	virtual bool isChild() {return false;}
	virtual Node** getParentNodes() {return 0;}
	virtual int getParentNodeCount() {return 0;}
	virtual Node** getSiblingNodes() {return siblingNodes;}
	virtual int getSiblingNodeCount() {return 5;}
	virtual Node* getEffectiveSiblingNode(int index){return getSiblingNodes()[index%5];}	
	virtual Node** getChildNodes() {return childNodes;}
	virtual void setChildNode(bool isParentIndex, int index, Node *node);
private:
	Node* siblingNodes[5];
	Node* childNodes[5];
};

#endif
