#ifndef GRAPH_MANAGER_H_
#define GRAPH_MANAGER_H_

#include "Node.h"

class GraphManager {
public:
	GraphManager();
private:
	unsigned long currentRevision;
	Node* rootNodes[12];
};

#endif
