/**
 * \file Node.h
 * \author Jon Leonard
 * \date 2014/02/10
 * \copyright The BSD 2-Clause License
 */
#ifndef NODE_H_
#define NODE_H_

#include <boost/ptr_container/ptr_list.hpp>

/**
 * \class Node
 */
class Node {
public:
	Node(unsigned long id):id(id){};
private:
	const unsigned long id;
	boost::ptr_list<NodeConnectivityData> connectivityData;
};

#endif