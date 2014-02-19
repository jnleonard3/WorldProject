#ifndef NODE_ACCESSOR_H_
#define NODE_ACCESSOR_H_

class Node;
class NodeConnectivityData;

/**
 * \class NodeAccessor
 */
class NodeAccessor {
public:
	NodeAccessor(unsigned long revision):revision(revision){};
	unsigned long getId(Node *node);
	NodeConnectivityData* getConnectivity(Node *node);
	void addConnectivity(Node *node, NodeConnectivityData* connectivity);
protected:
	virtual Node* getNode(Node *node){return node;}
private:
	unsigned long revision;
};

class FixedNodeAccessor {
public:
	FixedNodeAccessor(NodeAccessor nodeAccessor, Node *node):nodeAccessor(nodeAccessor),node(node){};
	FixedNodeAccessor(unsigned long revision, Node *node):nodeAccessor(revision),node(node){};
	Node* getNode(){return node;}
	NodeAccessor getAccessor(){return nodeAccessor;}
	unsigned long getId(){nodeAccessor.getId(node);}
	NodeConnectivityData* getConnectivity(){nodeAccessor.getConnectivity(node);}
private:
	NodeAccessor nodeAccessor;
	Node *node;
};

#endif
