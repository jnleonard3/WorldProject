#include "NodeConnectivityData.h"

#include "Node.h"

int NodeConnectivityData::getParentNodeIndex(unsigned long id) {
	for(int i = 0; i < getParentNodeCount(); i += 1) {
		if(getParentNodes()[i] != 0 && getParentNodes()[i]->getId() == id) {
			return i;
		}
	}
	return -1;
}

int NodeConnectivityData::getSiblingNodeIndex(unsigned long id) {
	for(int i = 0; i < getSiblingNodeCount(); i += 1) {
		if(getSiblingNodes()[i] != 0 && getSiblingNodes()[i]->getId() == id) {
			return i;
		}
	}
	return -1;
}

int NodeConnectivityData::getChildNodeIndex(unsigned long id) {
	for(int i = 0; i < getChildNodeCount(); i += 1) {
		if(getChildNodes()[i] != 0 && getChildNodes()[i]->getId() == id) {
			return i;
		}
	}
	return -1;
}

void NodeConnectivityRootData::setChildNode(bool isParentIndex, int index, Node *node) {
	if(!isParentIndex) {
		int actualIndex = index % 5;
		getChildNodes()[actualIndex] = node;
	}
}

void NodeConnectivityChildData::setChildNode(bool isParentIndex, int index, Node *node) {
	if(isParentIndex) {
		int actualIndex = index % 2;
		getChildNodes()[actualIndex * 3] = node;
	} else {
		int actualIndex = index % 4;
		getChildNodes()[actualIndex + 1 + (actualIndex > 1 ? 1 : 0)] = node;
	}
}

Node* NodeConnectivityData::getEffectiveSiblingNode(int index) {
	int totalSiblings = getParentNodeCount() + getSiblingNodeCount();
	int modSiblings = index % totalSiblings;
	int divSiblings = index / totalSiblings;
	if(modSiblings == 0) {
		return getParentNodes()[divSiblings];
	} else {
		return getSiblingNodes()[divSiblings + modSiblings];
	}
}

NodeConnectivityChildData::NodeConnectivityChildData(unsigned long revisionId):NodeConnectivityData(revisionId) {
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

NodeConnectivityChildData* NodeConnectivityChildData::copy(unsigned long revision) {
	NodeConnectivityChildData *newNode = new NodeConnectivityChildData(revision);
	for(int i = 0; i < getParentNodeCount(); i += 1) {
		newNode->getParentNodes()[i] = getParentNodes()[i];
	}
	for(int i = 0; i < getSiblingNodeCount(); i += 1) {
		newNode->getSiblingNodes()[i] = getSiblingNodes()[i];
	}
	for(int i = 0; i < getChildNodeCount(); i += 1) {
		newNode->getChildNodes()[i] = getChildNodes()[i];
	}
	return newNode;
}

NodeConnectivityRootData::NodeConnectivityRootData(unsigned long revisionId):NodeConnectivityData(revisionId) {
	for(int i = 0; i < getSiblingNodeCount(); i += 1) {
		getSiblingNodes()[i] = 0;
	}
	for(int i = 0; i < getChildNodeCount(); i += 1) {
		getChildNodes()[i] = 0;
	}
}

NodeConnectivityRootData* NodeConnectivityRootData::copy(unsigned long revision) {
	NodeConnectivityRootData *newNode = new NodeConnectivityRootData(revision);
	for(int i = 0; i < getSiblingNodeCount(); i += 1) {
		newNode->getSiblingNodes()[i] = getSiblingNodes()[i];
	}
	for(int i = 0; i < getChildNodeCount(); i += 1) {
		newNode->getChildNodes()[i] = getChildNodes()[i];
	}
	return newNode;
}
