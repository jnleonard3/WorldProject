/**
 * \file ImmutableNode.h
 * \author Jon Leonard
 * \date 2014/02/10
 * \copyright The BSD 2-Clause License
 */
#ifndef IMMUTABLE_NODE_H_
#define IMMUTABLE_NODE_H_

class Node;

/**
 * \class ImmutableNode
 */
class ImmutableNode {
public:
	ImmutableNode(unsigned long id):id(id){}
	virtual ~ImmutableNode(){}
	unsigned long getId() {return id;}
	virtual bool isChild() = 0;
	virtual unsigned long* getParentNodes() = 0;
	virtual int getParentNodeCount() = 0;
	virtual unsigned long* getSiblingNodes() = 0;
	virtual int getSiblingNodeCount() = 0;
	virtual unsigned long* getChildNodes() = 0;
	virtual int getChildNodeCount() = 0;
private:
	unsigned long id;
};

/**
 * \class ImmutableChildNode
 */
class ImmutableChildNode : public ImmutableNode {
public:
	ImmutableChildNode(unsigned long id):ImmutableNode(id){}
	virtual bool isChild() {return true;}
	virtual unsigned long* getParentNodes() {return parentNodes;}
	virtual int getParentNodeCount() {return 2;}
	virtual unsigned long* getSiblingNodes() {return siblingNodes;}
	virtual int getSiblingNodeCount() {return 4;};
	virtual unsigned long* getChildNodes() {return childNodes;}
	virtual int getChildNodeCount() {return 6;}
private:
	unsigned long parentNodes[2];
	unsigned long siblingNodes[4];
	unsigned long childNodes[6];
};

/**
 * \class ImmutableRootNode
 */
class ImmutableRootNode : public ImmutableNode {
public:
	ImmutableRootNode(unsigned long id):ImmutableNode(id){}
	virtual bool isChild() {return false;}
	virtual unsigned long* getParentNodes() {return 0;}
	virtual int getParentNodeCount() {return 0;}
	virtual unsigned long* getSiblingNodes() {return siblingNodes;}
	virtual int getSiblingNodeCount() {return 5;}
	virtual unsigned long* getChildNodes() {return childNodes;}
	virtual int getChildNodeCount() {return 5;}
private:
	unsigned long siblingNodes[5];
	unsigned long childNodes[5];
};

class ImmutableNodeFactory {
public:
	static ImmutableNode* createImmutableNode(unsigned long revision, Node *node);
private:
	ImmutableNodeFactory(){};
};

#endif
