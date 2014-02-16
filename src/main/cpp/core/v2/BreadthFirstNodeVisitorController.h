#ifndef BREADTH_FIRST_NODE_VISITOR_CONTROLLER_H
#define BREADTH_FIRST_NODE_VISITOR_CONTROLLER_H

#include "AbstractNodeVisitorController.h"

#include <boost/lockfree/queue.hpp>
#include <set>

class BreadthFirstNodeVisitorController : public AbstractNodeVisitorController
{
public:
	BreadthFirstNodeVisitorController():siblingNodeQueue(1),childNodeQueue(1){}
	virtual ~BreadthFirstNodeVisitorController(){}
	virtual Node* getNextNode(unsigned long id, NodeConnectivityData* connectivity);
private:
	boost::lockfree::queue<Node*> siblingNodeQueue;
	boost::lockfree::queue<Node*> childNodeQueue;
	std::set<long> visitedNodes;
};

#endif
