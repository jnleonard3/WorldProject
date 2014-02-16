#include "BreadthFirstNodeVisitorController.h"

#include "Node.h"
#include "NodeConnectivityData.h"

Node* BreadthFirstNodeVisitorController::getNextNode(unsigned long id, NodeConnectivityData* connectivity) {
	visitedNodes.insert(id);
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
	if(siblingNodeQueue.pop(nextNode)) {
		return nextNode;
	} else {
		while(childNodeQueue.pop(nextNode)) {
			siblingNodeQueue.push(nextNode);
		}
		nextNode = 0;
		if(siblingNodeQueue.pop(nextNode)) {
			return nextNode;
		}
	}
	return 0;
}

