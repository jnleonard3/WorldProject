#include "NodeModificationVisitor.h"

#include "Node.h"

Node* NodeModificationVisitor::getOrCreateModifiedNode(Node* node) {
	Node* modifiedNode = modifiedNodes[node->getId()];
	if(modifiedNode == 0) {
		modifiedNode = node->copy();
		modifiedNodes[node->getId()] = modifiedNode;
	}
	return modifiedNode;
}

Node* NodeModificationVisitor::getNextNode(FixedNodeAccessor accessor) {
	if(!actionsTaken.empty()) {
		Node* modifiedNode = getOrCreateModifiedNode(accessor.getNode());
		NodeConnectivityData *modifiedConnectivity = modifiedNode->getHeadConnectivity();
		
		ModificationAction action;
		while(actionsTaken.pop(action)) {
			if(action.isNodeAdded) {
				
			}
		}
	}
	
	Node* nextNode = modifiedNodes[getNextNodeId()];
	if(nextNode == 0) {
		nextNode = SimpleNodeVisitor::getNextNode(accessor);
	}
	return nextNode;
}

void NodeModificationVisitor::addChildNode(int index) {
	actionsTaken.push(ModificationAction(true,index));
}

void NodeModificationVisitor::removeChildNode(int index) {
	actionsTaken.push(ModificationAction(false,index));
}

std::list<Node*> NodeModificationVisitor::getModifiedNodes() {
	std::list<Node*> modifiedNodesList;
	for (std::map<unsigned long, Node*>::iterator iter = modifiedNodes.begin(); iter != modifiedNodes.end(); iter++) {
		if(iter->second != 0) {
			modifiedNodesList.push_front(iter->second);
		}
	}
	return modifiedNodesList;
}
