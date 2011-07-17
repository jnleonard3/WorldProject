/*
 * IcosahedronGraph.h
 *
 *  Created on: Jul 16, 2011
 *      Author: Jon
 */

#ifndef ICOSAHEDRONGRAPH_H_
#define ICOSAHEDRONGRAPH_H_

#include "Graph.h"

class IcosahedronGraph {
public:
	IcosahedronGraph(double radius);
	~IcosahedronGraph();

	VertexNode& getVertexNode(unsigned int node);
	FaceNode& getFaceNode(unsigned int node);

	unsigned int getVertexNodeIndex(const VertexNode* node);

private:
	VertexNode rootVertexNode;
	VertexNode *vertexNodes;

	FaceNode rootFaceNode;
	FaceNode *faceNodes;
};


#endif /* ICOSAHEDRONGRAPH_H_ */
