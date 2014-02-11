/**
 * \file NodeModificationVisitor.h
 * \author Jon Leonard
 * \date 2014/02/10
 * \copyright The BSD 2-Clause License
 */
#ifndef NODE_VISITOR_H_
#define NODE_VISITOR_H_

/**
 * \class NodeModificationVisitor
 */
class NodeModificationVisitor : public NodeVisitor {
public:
	virtual ~NodeModificationVisitor(){};
	virtual void visit(NodeVisitorModificationSession *session, ImmutableNode node) = 0;
};

#endif