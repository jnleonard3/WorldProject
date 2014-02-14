#include "ImmutableNode.h"
#include "Node.h"

ImmutableChildNode::ImmutableChildNode(unsigned long id):ImmutableNode(id) {
	for(int i = 0; i < getParentNodeCount(); i += 1) {
		getParentNodes()[i] = 0;
	}
	for(int i = 0; i < getSiblingNodeCount(); i += 1) {
		getSiblingNodes()[i] = 0;
	}
	for(int i = 0; i < getChildNodeCount(); i += 1) {
		getChildNodes()[i] = 0;
	}
}

ImmutableRootNode::ImmutableRootNode(unsigned long id):ImmutableNode(id) {
	for(int i = 0; i < getSiblingNodeCount(); i += 1) {
		getSiblingNodes()[i] = 0;
	}
	for(int i = 0; i < getChildNodeCount(); i += 1) {
		getChildNodes()[i] = 0;
	}
}

ImmutableNode* ImmutableNodeFactory::createImmutableNode(unsigned long revision, Node *node) {
	ImmutableNode *immutableNode;
	NodeConnectivityData *connectivity = node->getConnectivity(revision);
	if(connectivity->isChild()) {
		immutableNode = new ImmutableChildNode(node->getId());
	} else {
		immutableNode = new ImmutableRootNode(node->getId());
	}
	for(int i = 0; i < connectivity->getParentNodeCount(); i += 1) {
		if(connectivity->getParentNodes()[i] != 0) {
			immutableNode->getParentNodes()[i] = connectivity->getParentNodes()[i]->getId();
		}
	}
	for(int i = 0; i < connectivity->getSiblingNodeCount(); i += 1) {
		if(connectivity->getSiblingNodes()[i] != 0) {
			immutableNode->getSiblingNodes()[i] = connectivity->getSiblingNodes()[i]->getId();
		}
	}
	for(int i = 0; i < connectivity->getChildNodeCount(); i += 1) {
		if(connectivity->getChildNodes()[i] != 0) {
			immutableNode->getChildNodes()[i] = connectivity->getChildNodes()[i]->getId();
		}
	}
	return immutableNode;
}
