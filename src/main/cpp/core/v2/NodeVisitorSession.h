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
	AbstractVisitorSession(Node *startNode, unsigned long maxRevision):currentNode(startNode),nextNode(0),maxRevision(maxRevision){};
	virtual ~AbstractVisitorSession(){};
	virtual void traverse();
	void setNextNode(unsigned long nextNodeId);
protected:
	virtual void visitNode(ImmutableNode* node) = 0;
	Node *currentNode;
	Node *nextNode;
	unsigned long maxRevision;
};

/**
 * \class NodeVisitorSession
 */
class NodeVisitorSession : public AbstractVisitorSession {
public:
	NodeVisitorSession(Node *startNode, NodeVisitor *visitor, unsigned long maxRevision):AbstractVisitorSession(startNode,maxRevision),visitor(visitor){};
protected:
	virtual void visitNode(ImmutableNode* node);
private:
	NodeVisitor *visitor;
};

#endif
