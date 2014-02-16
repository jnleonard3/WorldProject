/**
 * \file NodeModificationVisitor.h
 * \author Jon Leonard
 * \date 2014/02/10
 * \copyright The BSD 2-Clause License
 */
#ifndef NODE_VISITOR_H_
#define NODE_VISITOR_H_

#include "SimpleNodeVisitor.h"

#include <map>

/**
 * \class NodeModificationVisitor
 */
class NodeModificationVisitor : public SimpleNodeVisitor {
public:
	virtual ~NodeModificationVisitor(){};
	virtual void visit(ImmutableNode *node) = 0;
	virtual Node* getNextNode(unsigned long id, NodeConnectivityData *connectivity);
protected:
	void addChildNode(int index);
	void removeChildNode(int index);
private:
	Node* currentNode;
	std::map<unsigned long, Node*> modifiedNodes;
};

#endif
