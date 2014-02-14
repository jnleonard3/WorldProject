#include "Node.h"

void Node::addConnectivity(NodeConnectivityData *connectivity) {
	connectivityData.push_front(connectivity);
}

NodeConnectivityData* Node::getConnectivity(unsigned long revision) {
	for (boost::ptr_list<NodeConnectivityData>::iterator iter = connectivityData.begin(); iter != connectivityData.end(); iter++) {
		if(!is_null(iter) && iter->getRevision() <= revision) {
			return &(*iter);
		}
	}
	return 0;
}
