/*
 * Graph.h
 *
 *  Created on: Jul 16, 2011
 *      Author: Jon
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "CommonGeometry.h"
#include "TriangleTerrainSkin.h"

class VertexNode {
public:
	VertexNode(){};
	VertexNode(unsigned int numConnected, Point vertex);

	void setConnected(VertexNode* node);
	VertexNode* getConnected(int index);

	Point getPoint() const { return vertex; };

	const unsigned int getNumberConnected() const { return numberConnected; };

private:
	unsigned int numberConnected;
	Point vertex;
	VertexNode** connectedNodes;
};

struct TriangleElement {
	TriangleElement():skin(0,Triangle(Point(0,0,0),Point(0,0,0),Point(0,0,0))){};
	TriangleElement(unsigned int levelOfDetail, VertexNode* first, VertexNode* second, VertexNode* third);

	VertexNode* relatedNodes[3];
	Triangle triangle;
	TriangleTerrainSkin skin;
};

class FaceNode {
public:
	FaceNode(){};
	FaceNode(unsigned int numConnected, TriangleElement triangle);

	void setConnected(FaceNode* node);
	FaceNode* getConnected(int index);

	TriangleElement& getTriangle() { return element; };

	const unsigned int getNumberConnected() const { return numberConnected; };

private:
	unsigned int numberConnected;
	TriangleElement element;
	FaceNode** connectedNodes;
};


#endif /* GRAPH_H_ */
