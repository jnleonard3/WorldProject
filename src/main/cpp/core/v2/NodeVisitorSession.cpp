#include "NodeVisitorSession.h"

#include "Node.h"
#include "NodeVisitor.h"

void AbstractVisitorSession::traverse() {
	while(currentNode != NULL) {
		ImmutableNode *node = ImmutableNodeFactory::createImmutableNode(maxRevision, currentNode);
		visitNode(node);
		delete node;
		currentNode = nextNode;
		nextNode = 0;
	}
}

void AbstractVisitorSession::setNextNode(unsigned long nextNodeId) {
	NodeConnectivityData *connectivity = currentNode->getConnectivity(maxRevision);
	for(int i = 0; i < connectivity->getParentNodeCount(); i += 1) {
		if(connectivity->getParentNodes()[i] != 0 && connectivity->getParentNodes()[i]->getId() == nextNodeId) {
			nextNode = connectivity->getParentNodes()[i];
			return;
		}
	}
	for(int i = 0; i < connectivity->getSiblingNodeCount(); i += 1) {
		if(connectivity->getSiblingNodes()[i] != 0 && connectivity->getSiblingNodes()[i]->getId() == nextNodeId) {
			nextNode = connectivity->getSiblingNodes()[i];
			return;
		}
	}
	for(int i = 0; i < connectivity->getChildNodeCount(); i += 1) {
		if(connectivity->getChildNodes()[i] != 0 && connectivity->getChildNodes()[i]->getId() == nextNodeId) {
			nextNode = connectivity->getChildNodes()[i];
			return;
		}
	}
}

void NodeVisitorSession::visitNode(ImmutableNode* node) {
	visitor->visit(this, node);
}
