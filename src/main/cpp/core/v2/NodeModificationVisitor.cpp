#include "NodeModificationVisitor.h"

#include "Node.h"

Node* NodeModificationVisitor::getNextNode(Node *currentNode, NodeConnectivityData *connectivity) {
	if(!actionsTaken.empty()) {
		Node* modifiedNode = modifiedNodes[currentNode->getId()];
		if(modifiedNode == 0) {
			modifiedNode = currentNode->copy();
			modifiedNodes[currentNode->getId()] = modifiedNode;
		}
		NodeConnectivityData *modifiedConnectivity = modifiedNode->getHeadConnectivity();
		
		ModificationAction action;
		while(actionsTaken.pop(action)) {
			if(action.isNodeAdded) {
				
			} else {
				
			}
		}
	}
	
	Node* nextNode = modifiedNodes[getNextNodeId()];
	if(nextNode == 0) {
		nextNode = SimpleNodeVisitor::getNextNode(currentNode, connectivity);
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
