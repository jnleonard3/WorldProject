#include "SimpleNodeVisitor.h"

#include "Node.h"
#include "NodeConnectivityData.h"

Node* SimpleNodeVisitor::getNextNode(FixedNodeAccessor accessor) {
	unsigned long nextNodeId = this->nextNodeId;
	this->nextNodeId = 0;
	if(nextNodeId == accessor.getId()) {
		return accessor.getNode();
	}
	NodeConnectivityData *connectivity = accessor.getConnectivity();
	for(int i = 0; i < connectivity->getParentNodeCount(); i += 1) {
		if(connectivity->getParentNodes()[i] != 0 && connectivity->getParentNodes()[i]->getId() == nextNodeId) {
			return connectivity->getParentNodes()[i];
		}
	}
	for(int i = 0; i < connectivity->getSiblingNodeCount(); i += 1) {
		if(connectivity->getSiblingNodes()[i] != 0 && connectivity->getSiblingNodes()[i]->getId() == nextNodeId) {
			return connectivity->getSiblingNodes()[i];
		}
	}
	for(int i = 0; i < connectivity->getChildNodeCount(); i += 1) {
		if(connectivity->getChildNodes()[i] != 0 && connectivity->getChildNodes()[i]->getId() == nextNodeId) {
			return connectivity->getChildNodes()[i];
		}
	}
}
