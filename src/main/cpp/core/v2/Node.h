/**
 * \file Node.h
 * \author Jon Leonard
 * \date 2014/02/10
 * \copyright The BSD 2-Clause License
 */
#ifndef NODE_H_
#define NODE_H_

#include <boost/ptr_container/ptr_list.hpp>
#include "NodeConnectivityData.h"

class NodeAccessor;

/**
 * \class Node
 */
class Node {
public:
	Node():id(0){};
	Node(unsigned long id):id(id){};
	Node(const Node& node):id(node.getId()){};
	
	unsigned long getId() const {return id;}
	
	Node* copy();
	
	void addConnectivity(NodeConnectivityData *connectivity);
	NodeConnectivityData* getHeadConnectivity();
	NodeConnectivityData* getConnectivity(unsigned long revision);
	
	struct CreateChildNodeResult {
		Node *cNode;
		Node *p1, *p2;
		Node *s1, *s2, *s3, *s4;
		NodeConnectivityData *cc;
		NodeConnectivityData *p1c, *p2c;
		NodeConnectivityData *s1c, *s2c, *s3c, *s4c;
		void apply(unsigned long revision, NodeAccessor *accessor);
	};
	
	static CreateChildNodeResult* createChildNode(unsigned long id, NodeAccessor *accessor, Node* p1, Node* p2);
private:
	unsigned long id;
	boost::ptr_list<NodeConnectivityData> connectivityData;
};

#endif
