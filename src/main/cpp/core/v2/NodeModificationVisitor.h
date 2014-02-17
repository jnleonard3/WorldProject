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
#include <list>
#include <boost/lockfree/queue.hpp>

struct ModificationAction {
	ModificationAction():isNodeAdded(true),index(-1){}
	ModificationAction(bool isNodeAdded, int index):isNodeAdded(isNodeAdded),index(index){}
	bool isNodeAdded;
	int index;
};

/**
 * \class NodeModificationVisitor
 */
class NodeModificationVisitor : public SimpleNodeVisitor {
public:
	NodeModificationVisitor(unsigned long nextNodeId):nextNodeId(nextNodeId),modifiedNodes(),newNodes(),actionsTaken(6){}
	virtual ~NodeModificationVisitor(){};
	virtual void visit(ImmutableNode *node) = 0;
	virtual Node* getNextNode(Node *currentNode, NodeConnectivityData *connectivity);
	std::list<Node*> getModifiedNodes();
protected:
	void addChildNode(int index);
	void removeChildNode(int index);
private:
	unsigned long nextNodeId;
	std::map<unsigned long, Node*> modifiedNodes;
	std::list<Node*> newNodes;
	boost::lockfree::queue<ModificationAction> actionsTaken;
};

#endif
