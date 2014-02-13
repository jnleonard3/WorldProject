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
	AbstractVisitorSession(Node *startNode):currentNode(startNode){};
	virtual ~AbstractVisitorSession(){};
	virtual void traverse(unsigned long maxRevision);
protected:
	virtual void visitNode(ImmutableNode* node) = 0;
	Node *currentNode;
	Node *nextNode;
};

/**
 * \class NodeVisitorSession
 */
class NodeVisitorSession : public AbstractVisitorSession {
public:
	NodeVisitorSession(Node *startNode, NodeVisitor *visitor):AbstractVisitorSession(startNode),visitor(visitor){};
protected:
	virtual void visitNode(ImmutableNode* node);
private:
	NodeVisitor *visitor;
};

#endif
