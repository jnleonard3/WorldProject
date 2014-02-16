/**
 * \file NodeVisitor.h
 * \author Jon Leonard
 * \date 2014/02/10
 * \copyright The BSD 2-Clause License
 */
#ifndef ABSTRACT_NODE_VISITOR_H_
#define ABSTRACT_NODE_VISITOR_H_

class ImmutableNode;

/**
 * \class NodeVisitor
 */
class AbstractNodeVisitor {
public:
	virtual ~AbstractNodeVisitor(){};
	virtual void visit(ImmutableNode *node) = 0;
};

#endif
