#include "NodeVisitorSession.h"

#include "Node.h"
#include "NodeVisitor.h"

void AbstractVisitorSession::traverse(unsigned long maxRevision) {
	while(currentNode != NULL) {
		ImmutableNode *node = ImmutableNodeFactory::createImmutableNode(maxRevision, currentNode);
		visitNode(node);
		delete node;
		currentNode = nextNode;
	}
}

void NodeVisitorSession::visitNode(ImmutableNode* node) {
	visitor->visit(this, node);
}
