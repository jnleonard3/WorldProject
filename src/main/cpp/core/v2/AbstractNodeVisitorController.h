#ifndef ABSTRACT_NODE_VISITOR_CONTROLLER_H_
#define ABSTRACT_NODE_VISITOR_CONTROLLER_H_

#include "NodeAccessor.h"

class Node;
class NodeConnectivityData;

class AbstractNodeVisitorController {
public:
	virtual ~AbstractNodeVisitorController(){};
	virtual Node* getNextNode(FixedNodeAccessor accessor) = 0;
};

#endif
