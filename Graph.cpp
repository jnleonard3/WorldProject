/*
 * Graph.cpp
 *
 *  Created on: Jul 16, 2011
 *      Author: Jon
 */

#include "Graph.h"

VertexNode::VertexNode(unsigned int numConnected, Point vertex):numberConnected(0) {
	this->vertex = vertex;
	connectedNodes = new VertexNode*[numberConnected];
}

void VertexNode::setConnected(VertexNode* node) {
	connectedNodes[numberConnected] = node;
}

VertexNode* VertexNode::getConnected(int index) {
	return connectedNodes[index];
}

TriangleElement::TriangleElement(VertexNode* first, VertexNode* second, VertexNode* third)
:triangle(first->getPoint(), second->getPoint(), third->getPoint()) {
	relatedNodes[0] = first;
	relatedNodes[1] = second;
	relatedNodes[2] = third;
}

FaceNode::FaceNode(unsigned int numConnected, TriangleElement triangle):numberConnected(0) {
	this->element = element;
	connectedNodes = new FaceNode*[numberConnected];
}

void FaceNode::setConnected(FaceNode* node) {
	connectedNodes[numberConnected] = node;
}

FaceNode* FaceNode::getConnected(int index) {
	return connectedNodes[index];
}
