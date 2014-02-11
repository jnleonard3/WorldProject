/**
 * \file NodeVisitorSession.h
 * \author Jon Leonard
 * \date 2014/02/10
 * \copyright The BSD 2-Clause License
 */
#ifndef NODE_VISITOR_SESSION_H_
#define NODE_VISITOR_SESSION_H_

/**
 * \class NodeVisitorSession
 */
class NodeVisitorSession {
public:
	NodeVisitorSession(NodeVisitor *visitor, Node *startNode):visitor(visitor),currentNode(startNode){};
	void traverse(NodeVisitor *visitor);
private:
	NodeVisitor *visitor;
	Node *currentNode;
	Node *nextNode;
};

#endif