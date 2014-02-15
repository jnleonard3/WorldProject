/**
 * \file NodeVisitor.h
 * \author Jon Leonard
 * \date 2014/02/10
 * \copyright The BSD 2-Clause License
 */
#ifndef NODE_VISITOR_H_
#define NODE_VISITOR_H_

#include "ImmutableNode.h"
#include "NodeVisitorSession.h"

/**
 * \class NodeVisitor
 */
class NodeVisitor {
public:
	virtual ~NodeVisitor(){};
	virtual void visit(NodeVisitorSession *session, ImmutableNode* node){this->session = session;visit(node);};
	virtual void visit(ImmutableNode *node) = 0;
protected:
	NodeVisitorSession *session;
};

#endif
