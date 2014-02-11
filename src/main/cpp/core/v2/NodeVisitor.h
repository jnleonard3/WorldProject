/**
 * \file NodeVisitor.h
 * \author Jon Leonard
 * \date 2014/02/10
 * \copyright The BSD 2-Clause License
 */
#ifndef NODE_VISITOR_H_
#define NODE_VISITOR_H_

/**
 * \class NodeVisitor
 */
class NodeVisitor {
public:
	virtual ~NodeVisitor(){};
	virtual void visit(NodeVisitorSession *session, ImmutableNode node) = 0;
};

#endif