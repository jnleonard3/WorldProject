#include "Node.h"

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

void Node::CreateChildNodeResult::apply(unsigned long revision) {
	cNode->addConnectivity(cc->copy(revision));
	if(p1 != 0) {
		p1->addConnectivity(p1c->copy(revision));
	}
	if(p2 != 0) {
		p2->addConnectivity(p2c->copy(revision));
	}
	if(s1 != 0) {
		s1->addConnectivity(s1c->copy(revision));
	}
	if(s2 != 0) {
		s2->addConnectivity(s2c->copy(revision));
	}
	if(s3 != 0) {
		s3->addConnectivity(s3c->copy(revision));
	}
	if(s4 != 0) {
		s4->addConnectivity(s4c->copy(revision));
	}
}

Node::CreateChildNodeResult* Node::createChildNode(unsigned long id, unsigned long revision, Node* p1, Node* p2) {
	NodeConnectivityData *pc1, *pc2;
	if (revision == 0) {
		pc1 = p1->getHeadConnectivity()->copy(0);
		pc2 = p2->getHeadConnectivity()->copy(0);
	} else {
		pc1 = p1->getConnectivity(revision)->copy(0);
		pc2 = p2->getConnectivity(revision)->copy(0);
	}
	
	int p1Index = pc1->getParentNodeIndex(p2->getId());
	int s1Index = pc1->getSiblingNodeIndex(p2->getId());
	
	int p2Index = pc2->getParentNodeIndex(p1->getId());
	int s2Index = pc2->getSiblingNodeIndex(p1->getId());		
	
	NodeConnectivityData *connectivity = new NodeConnectivityChildData(revision);
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
