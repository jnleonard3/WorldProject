#include "NodeVisitorSession.h"

#include "Node.h"
#include "NodeVisitor.h"

ImmutableNode immuteNode(Node *node) {
	
}

void AbstractVisitorSession::traverse() {
	while(currentNode != NULL) {
		visitCurrentNode(immuteNode(currentNode));
		currentNode = nextNode;
	}
}

void NodeVisitorSession::visitCurrentNode(ImmutableNode node) {
	visitor->visit(this,node);
}