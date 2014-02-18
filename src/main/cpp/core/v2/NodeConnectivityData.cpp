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
		getChildNodes()[actualIndex - 1 - (actualIndex > 3 ? 1 : 0)] = node;
	}
}

Node* NodeConnectivityChildData::getEffectiveSiblingNode(int index) {
	int actualIndex = index % getChildNodeCount();
	if(actualIndex % 3 == 0) {
		return getParentNodes()[actualIndex / 3];
	} else {
		return getSiblingNodes()[actualIndex - 1 - (actualIndex > 3 ? 1 : 0)];
	}
}

void NodeConnectivityData::merge(NodeConnectivityData *other) {
	for(int i = 0; i < getParentNodeCount(); i += 1) {
		if(getParentNodes()[i] != 0 && other->getParentNodes()[i] != 0) {
			if(getParentNodes()[i]->getId() != other->getParentNodes()[i]->getId()) {
				getParentNodes()[i] = other->getParentNodes()[i];
			}
		} else {
			getParentNodes()[i] = other->getParentNodes()[i];
		}
	}
	
	for(int i = 0; i < getSiblingNodeCount(); i += 1) {
		if(getSiblingNodes()[i] != 0 && other->getSiblingNodes()[i] != 0) {
			if(getSiblingNodes()[i]->getId() != other->getSiblingNodes()[i]->getId()) {
				getSiblingNodes()[i] = other->getSiblingNodes()[i];
			}
		} else {
			getSiblingNodes()[i] = other->getSiblingNodes()[i];
		}
	}
	
	for(int i = 0; i < getChildNodeCount(); i += 1) {
		if(getChildNodes()[i] != 0 && other->getChildNodes()[i] != 0) {
			if(getChildNodes()[i]->getId() != other->getChildNodes()[i]->getId()) {
				getChildNodes()[i] = other->getChildNodes()[i];
			}
		} else {
			getChildNodes()[i] = other->getChildNodes()[i];
		}
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
