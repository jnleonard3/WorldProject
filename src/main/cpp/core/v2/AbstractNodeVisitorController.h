#ifndef ABSTRACT_NODE_VISITOR_CONTROLLER_H_
#define ABSTRACT_NODE_VISITOR_CONTROLLER_H_

class Node;
class NodeConnectivityData;

class AbstractNodeVisitorController {
public:
	virtual ~AbstractNodeVisitorController(){};
	virtual Node* getNextNode(unsigned long id, NodeConnectivityData* connectivity) = 0;
};

#endif
