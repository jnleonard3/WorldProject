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

/**
 * \class Node
 */
class Node {
public:
	Node():id(0){};
	Node(unsigned long id):id(id){};
	Node(const Node& node):id(node.getId()){};
	unsigned long getId() const {return id;}
	void addConnectivity(NodeConnectivityData *connectivity);
	NodeConnectivityData* getConnectivity(unsigned long revision);
private:
	unsigned long id;
	boost::ptr_list<NodeConnectivityData> connectivityData;
};

#endif
