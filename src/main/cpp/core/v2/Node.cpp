#include "Node.h"

#include "NodeAccessor.h"

Node* Node::copy() {
	Node *newNode = new Node(this->getId());
	for (boost::ptr_list<NodeConnectivityData>::reverse_iterator iter = connectivityData.rbegin(); iter != connectivityData.rend(); iter++) {
		NodeConnectivityData *newConnectivity = iter->copy();
		newNode->addConnectivity(newConnectivity);
	}
	return newNode;
}

void Node::addConnectivity(NodeConnectivityData *connectivity) {
	connectivityData.push_front(connectivity);
}

NodeConnectivityData* Node::getHeadConnectivity() {
	NodeConnectivityData* connectivity = 0;
	for (boost::ptr_list<NodeConnectivityData>::iterator iter = connectivityData.begin(); iter != connectivityData.end(); iter++) {
		if(connectivity == 0 || iter->getRevision() > connectivity->getRevision()) {
			connectivity = &(*iter);
		}
	}
	return connectivity;
}

NodeConnectivityData* Node::getConnectivity(unsigned long revision) {
	for (boost::ptr_list<NodeConnectivityData>::iterator iter = connectivityData.begin(); iter != connectivityData.end(); iter++) {
		if(!is_null(iter) && iter->getRevision() <= revision) {
			return &(*iter);
		}
	}
	return 0;
}

void updateOrCreateConnectivity(Node *node, NodeAccessor *accessor, unsigned long revision, NodeConnectivityData *newConnectivity) {
	if(node != 0) {
		NodeConnectivityData *connectivity = accessor->getConnectivity(node);
		if(connectivity->getRevision() == revision) {
			connectivity->merge(newConnectivity);
		} else {
			accessor->addConnectivity(node, newConnectivity->copy(revision));
		}
	}
}

void Node::CreateChildNodeResult::apply(unsigned long revision, NodeAccessor *accessor) {
	accessor->addConnectivity(cNode, cc->copy(revision));
	updateOrCreateConnectivity(p1, accessor, revision, p1c);
	updateOrCreateConnectivity(p2, accessor, revision, p2c);
	updateOrCreateConnectivity(s1, accessor, revision, s1c);
	updateOrCreateConnectivity(s2, accessor, revision, s2c);
	updateOrCreateConnectivity(s3, accessor, revision, s3c);
	updateOrCreateConnectivity(s4, accessor, revision, s4c);
}

Node::CreateChildNodeResult* Node::createChildNode(unsigned long id, NodeAccessor *accessor, Node* p1, Node* p2) {
	NodeConnectivityData *pc1 = accessor->getConnectivity(p1)->copy();
	NodeConnectivityData *pc2 = accessor->getConnectivity(p2)->copy();
	
	int p1Index = pc1->getParentNodeIndex(p2->getId());
	int s1Index = pc1->getSiblingNodeIndex(p2->getId());
	
	int p2Index = pc2->getParentNodeIndex(p1->getId());
	int s2Index = pc2->getSiblingNodeIndex(p1->getId());		
	
	NodeConnectivityData *connectivity = new NodeConnectivityChildData(0);
	connectivity->getParentNodes()[0] = p1;
	connectivity->getParentNodes()[1] = p2;
	
	Node *newNode = new Node(id);
	
	Node::CreateChildNodeResult *createResult = new Node::CreateChildNodeResult();
	createResult->cNode = newNode;
	createResult->cc = connectivity;
	
	if (s1Index >= 0 && s2Index >= 0) {
		// p1 and p2 are siblings of each other
		pc1->setChildNode(false, s1Index, newNode);
		pc2->setChildNode(false, s2Index, newNode);
		
		createResult->p1 = p1;
		createResult->p2 = p2;
		createResult->p1c = pc1;
		createResult->p2c = pc2;
	} else if (p1Index >= 0) {
		// p1 has p2 as a parent
		pc1->setChildNode(true, p1Index, newNode);
		createResult->p1 = p1;
		createResult->p1c = pc1;
	} else if (p2Index >= 0) {
		// p2 has p1 as a parent
		pc2->setChildNode(true, p2Index, newNode);
		createResult->p2 = p2;
		createResult->p2c = pc2;
	} else {
		delete connectivity;
		delete newNode;
		delete createResult;
		createResult = 0;
	}
	return createResult;
}
