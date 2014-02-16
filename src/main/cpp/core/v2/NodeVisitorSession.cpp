#include "NodeVisitorSession.h"

#include "Node.h"
#include "ImmutableNode.h"
#include "AbstractNodeVisitorController.h"
#include "AbstractNodeVisitor.h"

void NodeVisitorSession::traverse(Node *startNode, AbstractNodeVisitorController *controller, AbstractNodeVisitor *visitor) {
	Node *currentNode = startNode;
	while(currentNode != 0) {
		ImmutableNode *immutableNode = ImmutableNodeFactory::createImmutableNode(getMaxRevision(), currentNode);
		visitor->visit(immutableNode);
		delete immutableNode;
		NodeConnectivityData *connectivity = currentNode->getConnectivity(getMaxRevision());
		currentNode = controller->getNextNode(connectivity);
	}
}
