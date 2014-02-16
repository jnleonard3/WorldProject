#include "NodeModificationVisitor.h"

Node* NodeModificationVisitor::getNextNode(unsigned long id, NodeConnectivityData *connectivity) {
	return SimpleNodeVisitor::getNextNode(id, connectivity);
}

void NodeModificationVisitor::addChildNode(int index) {
	
}

void NodeModificationVisitor::removeChildNode(int index) {
	
}
