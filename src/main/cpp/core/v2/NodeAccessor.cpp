#include "NodeAccessor.h"

#include "Node.h"

unsigned long NodeAccessor::getId(Node *node) {
	return getNode(node)->getId();
}

NodeConnectivityData* NodeAccessor::getConnectivity(Node *node) {
	return getNode(node)->getConnectivity(revision);
}

void NodeAccessor::addConnectivity(Node *node, NodeConnectivityData* connectivity) {
	getNode(node)->addConnectivity(connectivity);
}
