#include "NodeAccessor.h"

#include "Node.h"

unsigned long NodeAccessor::getId(Node *node) {
	return node->getId();
}

NodeConnectivityData* NodeAccessor::getConnectivity(Node *node) {
	return node->getConnectivity(revision);
}
