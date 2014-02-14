#include "NodeConnectivityData.h"

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

NodeConnectivityRootData::NodeConnectivityRootData(unsigned long revisionId):NodeConnectivityData(revisionId) {
	for(int i = 0; i < getSiblingNodeCount(); i += 1) {
		getSiblingNodes()[i] = 0;
	}
	for(int i = 0; i < getChildNodeCount(); i += 1) {
		getChildNodes()[i] = 0;
	}
}
