#include "GraphManager.h"
#include "NodeConnectivityData.h"

NodeConnectivityRootData* connectRootNode(Node** rootNodes, int a, int b, int c, int d, int e) {
	NodeConnectivityRootData *connectivity = new NodeConnectivityRootData(1);
	connectivity->getSiblingNodes()[0] = rootNodes[a];
	connectivity->getSiblingNodes()[1] = rootNodes[b];
	connectivity->getSiblingNodes()[2] = rootNodes[c];
	connectivity->getSiblingNodes()[3] = rootNodes[d];
	connectivity->getSiblingNodes()[4] = rootNodes[e];
	return connectivity;
}

GraphManager::GraphManager():currentRevision(1) {
	for(int i = 0; i < 12; i += 1) {
		rootNodes[i] = new Node(i + 1);
	}
	rootNodes[0]->addConnectivity(connectRootNode(rootNodes, 1, 4, 5, 8, 10));
	rootNodes[1]->addConnectivity(connectRootNode(rootNodes, 0, 6, 7, 8, 10));
	rootNodes[2]->addConnectivity(connectRootNode(rootNodes, 3, 4, 5, 9, 11));
	rootNodes[3]->addConnectivity(connectRootNode(rootNodes, 2, 6, 7, 9, 11));
	rootNodes[4]->addConnectivity(connectRootNode(rootNodes, 0, 2, 5, 8, 9));
	rootNodes[5]->addConnectivity(connectRootNode(rootNodes, 0, 2, 4, 10, 11));
	rootNodes[6]->addConnectivity(connectRootNode(rootNodes, 1, 3, 7, 8, 9));
	rootNodes[7]->addConnectivity(connectRootNode(rootNodes, 1, 3, 6, 10, 11));
	rootNodes[8]->addConnectivity(connectRootNode(rootNodes, 0, 1, 4, 6, 9));
	rootNodes[9]->addConnectivity(connectRootNode(rootNodes, 2, 3, 4, 6, 8));
	rootNodes[10]->addConnectivity(connectRootNode(rootNodes, 0, 1, 5, 7, 11));
	rootNodes[11]->addConnectivity(connectRootNode(rootNodes, 2, 3, 5, 7, 10));	
}
