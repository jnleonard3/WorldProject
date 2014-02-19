#include "NodeModificationVisitor.h"

#include "Node.h"

NodeModificationVisitor::ModifiedNodeAccessor::ModifiedNodeAccessor(unsigned long revision, std::map<unsigned long, Node*> &modifiedNodes, bool createIfMissing)
:NodeAccessor(revision),modifiedNodes(modifiedNodes),createIfMissing(createIfMissing){}

Node* NodeModificationVisitor::ModifiedNodeAccessor::getNode(Node *node){
	Node* newNode = modifiedNodes[node->getId()];
	if(newNode == 0) {
		if(createIfMissing) {
			newNode = node->copy();
			modifiedNodes[node->getId()] = newNode;
		} else {
			newNode = node;
		}
	}
	return newNode;
}

NodeModificationVisitor::NodeModificationVisitor(unsigned long revision, unsigned long nextNodeId)
:revision(revision),nextNodeId(nextNodeId),modifiedNodes(),newNodes(),actionsTaken(6),
modifiedAccessor(revision, modifiedNodes,false),
createModifiedAccessor(revision, modifiedNodes,true) {}

Node* NodeModificationVisitor::getNextNode(FixedNodeAccessor accessor) {
	if(!actionsTaken.empty()) {
		NodeConnectivityData* connectivity = modifiedAccessor.getConnectivity(accessor.getNode());
		
		ModificationAction action;
		while(actionsTaken.pop(action)) {
			if(action.isNodeAdded) {
				Node *sibling = connectivity->getEffectiveSiblingNode(action.index);
				if(sibling != 0) {
					Node::CreateChildNodeResult* result = Node::createChildNode(nextNodeId, &createModifiedAccessor, accessor.getNode(), sibling);
					if(result != 0) {
						result->apply(revision, &createModifiedAccessor);
					}
				}
			}
		}
	}
	
	return SimpleNodeVisitor::getNextNode(FixedNodeAccessor(modifiedAccessor, accessor.getNode()));
}

void NodeModificationVisitor::addChildNode(int index) {
	actionsTaken.push(ModificationAction(true,index));
}

void NodeModificationVisitor::removeChildNode(int index) {
	actionsTaken.push(ModificationAction(false,index));
}

std::list<Node*> NodeModificationVisitor::getModifiedNodes() {
	std::list<Node*> modifiedNodesList;
	for (std::map<unsigned long, Node*>::iterator iter = modifiedNodes.begin(); iter != modifiedNodes.end(); iter++) {
		if(iter->second != 0) {
			modifiedNodesList.push_front(iter->second);
		}
	}
	return modifiedNodesList;
}
