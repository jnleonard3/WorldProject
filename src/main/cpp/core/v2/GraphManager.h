#ifndef GRAPH_MANAGER_H_
#define GRAPH_MANAGER_H_

class Node;
class AbstractNodeVisitorController;
class AbstractNodeVisitor;

class GraphManager {
public:
	GraphManager();
	void traverse(AbstractNodeVisitorController *controller, AbstractNodeVisitor *visitor);
private:
	unsigned long currentRevision;
	Node* rootNodes[12];
};

#endif
