/**
 * \file SimpleNodeVisitor.h
 * \author Jon Leonard
 * \date 2014/02/10
 * \copyright The BSD 2-Clause License
 */
#ifndef SIMPLE_NODE_VISITOR_H_
#define SIMPLE_NODE_VISITOR_H_

#include "AbstractNodeVisitor.h"
#include "AbstractNodeVisitorController.h"

/**
 * \class SimpleNodeVisitor
 */
class SimpleNodeVisitor : public AbstractNodeVisitor, public AbstractNodeVisitorController {
public:
	virtual ~SimpleNodeVisitor(){};
	virtual void visit(ImmutableNode *node) = 0;
	virtual Node* getNextNode(NodeConnectivityData *connectivity);
protected:
	void setNextNode(unsigned long nextNodeId){this->nextNodeId = nextNodeId;}
private:
	unsigned long nextNodeId;
};

#endif
