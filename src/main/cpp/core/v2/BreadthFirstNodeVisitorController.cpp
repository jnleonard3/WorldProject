#include "BreadthFirstNodeVisitorController.h"

#include "Node.h"
#include "NodeConnectivityData.h"

Node* BreadthFirstNodeVisitorController::getNextNode(FixedNodeAccessor accessor) {
	visitedNodes.insert(accessor.getId());
	NodeConnectivityData* connectivity = accessor.getConnectivity();
	for(int i = 0; i < connectivity->getSiblingNodeCount(); i += 1) {
		if(connectivity->getSiblingNodes()[i] != 0 && visitedNodes.count(connectivity->getSiblingNodes()[i]->getId()) == 0) {
			siblingNodeQueue.push(connectivity->getSiblingNodes()[i]);
		}
	}
	for(int i = 0; i < connectivity->getChildNodeCount(); i += 1) {
		if(connectivity->getChildNodes()[i] != 0 && visitedNodes.count(connectivity->getChildNodes()[i]->getId()) == 0) {
			childNodeQueue.push(connectivity->getChildNodes()[i]);
		}
	}
	Node* nextNode;
	while(siblingNodeQueue.pop(nextNode)) {
		if(visitedNodes.count(nextNode->getId()) == 0) {
			return nextNode;
		}
	}
	while(childNodeQueue.pop(nextNode)) {
		siblingNodeQueue.push(nextNode);
	}
	if(siblingNodeQueue.pop(nextNode)) {
		return nextNode;
	}
	return 0;
}

