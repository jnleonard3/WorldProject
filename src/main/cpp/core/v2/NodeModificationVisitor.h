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
	NodeModificationVisitor(unsigned long revision, unsigned long nextNodeId);
	virtual ~NodeModificationVisitor(){};
	virtual void visit(ImmutableNode *node) = 0;
	virtual Node* getNextNode(FixedNodeAccessor accessor);
	std::list<Node*> getModifiedNodes();
protected:
	void addChildNode(int index);
	void removeChildNode(int index);
private:
	class ModifiedNodeAccessor : public NodeAccessor {
	public:
		ModifiedNodeAccessor(unsigned long revision, std::map<unsigned long, Node*> &modifiedNodes, bool createIfMissing);
	protected:
		virtual Node* getNode(Node *node);
	private:
		std::map<unsigned long, Node*> &modifiedNodes;
		bool createIfMissing;
	};

	unsigned long revision, nextNodeId;
	std::map<unsigned long, Node*> modifiedNodes;
	std::list<Node*> newNodes;
	boost::lockfree::queue<ModificationAction> actionsTaken;
	ModifiedNodeAccessor modifiedAccessor, createModifiedAccessor;
};

#endif
