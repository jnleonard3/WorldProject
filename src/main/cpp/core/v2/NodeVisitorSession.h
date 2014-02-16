#ifndef NODE_VISITOR_SESSION_H_
#define NODE_VISITOR_SESSION_H_

class Node;
class ImmutableNode;
class AbstractNodeVisitorController;
class AbstractNodeVisitor;

/**
 * \class NodeVisitorSession
 */
class NodeVisitorSession {
public:
	NodeVisitorSession(unsigned long maxRevision):maxRevision(maxRevision){};
	virtual ~NodeVisitorSession(){};
	virtual void traverse(Node *startNode, AbstractNodeVisitorController *controller, AbstractNodeVisitor *visitor);
	unsigned long getMaxRevision(){return maxRevision;}
private:
	const unsigned long maxRevision;
};

#endif
