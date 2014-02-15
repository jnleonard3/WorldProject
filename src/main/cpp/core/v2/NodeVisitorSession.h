/**
 * \file NodeVisitorSession.h
 * \author Jon Leonard
 * \date 2014/02/10
 * \copyright The BSD 2-Clause License
 */
#ifndef NODE_VISITOR_SESSION_H_
#define NODE_VISITOR_SESSION_H_

#include "ImmutableNode.h"

class Node;
class NodeVisitor;

/**
 * \class AbstractVisitorSession
 */
class AbstractVisitorSession {
public:
	AbstractVisitorSession(Node *startNode, unsigned long maxRevision):currentNode(startNode),maxRevision(maxRevision){};
	virtual ~AbstractVisitorSession(){};
	virtual void traverse() = 0;
	unsigned long getMaxRevision(){return maxRevision;}
protected:
	virtual void visitNode(ImmutableNode* node) = 0;
	Node *currentNode;
private:
	const unsigned long maxRevision;
};

/**
 * \class AbstractVisitorSession
 */
class AbstractSimpleVisitorSession : public AbstractVisitorSession {
public:
	AbstractSimpleVisitorSession(Node *startNode, unsigned long maxRevision):AbstractVisitorSession(startNode,maxRevision),nextNode(0){};
	virtual ~AbstractSimpleVisitorSession(){};
	virtual void traverse();
	void setNextNode(unsigned long nextNodeId);
protected:
	virtual void visitNode(ImmutableNode* node) = 0;
	Node* getNextNode(){return nextNode;}
private:
	Node *nextNode;
};

/**
 * \class NodeVisitorSession
 */
class NodeVisitorSession : public AbstractSimpleVisitorSession {
public:
	NodeVisitorSession(Node *startNode, NodeVisitor *visitor, unsigned long maxRevision):AbstractSimpleVisitorSession(startNode,maxRevision),visitor(visitor){};
protected:
	virtual void visitNode(ImmutableNode* node);
private:
	NodeVisitor *visitor;
};

#endif
