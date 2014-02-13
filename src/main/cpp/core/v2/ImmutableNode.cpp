#include "ImmutableNode.h"
#include "Node.h"

ImmutableNode* ImmutableNodeFactory::createImmutableNode(unsigned long revision, Node *node) {
	ImmutableNode *immutableNode;
	NodeConnectivityData *connectivity = node->getConnectivity(revision);
	if(connectivity->isChild()) {
		immutableNode = new ImmutableChildNode(node->getId());
	} else {
		immutableNode = new ImmutableRootNode(node->getId());
	}
	for(int i = 0; i < connectivity->getParentNodeCount(); i += 1) {
		immutableNode->getParentNodes()[i] = connectivity->getParentNodes()[i]->getId();
	}
	for(int i = 0; i < connectivity->getSiblingNodeCount(); i += 1) {
		immutableNode->getSiblingNodes()[i] = connectivity->getSiblingNodes()[i]->getId();
	}
	for(int i = 0; i < connectivity->getChildNodeCount(); i += 1) {
		immutableNode->getChildNodes()[i] = connectivity->getChildNodes()[i]->getId();
	}
	return immutableNode;
}
