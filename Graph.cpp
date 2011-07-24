/*
 * Graph.cpp
 *
 *  Created on: Jul 16, 2011
 *      Author: Jon
 */

#include "Graph.h"
#include <iostream>

VertexNode::VertexNode(unsigned int numConnected, Point vertex):numberConnected(0) {
	this->vertex = vertex;
	connectedNodes = new VertexNode*[numConnected];
}

void VertexNode::setConnected(VertexNode* node) {
	connectedNodes[numberConnected] = node;
	numberConnected++;
}

VertexNode* VertexNode::getConnected(int index) {
	return connectedNodes[index];
}

TriangleElement::TriangleElement(unsigned int levelOfDetail, VertexNode* first, VertexNode* second, VertexNode* third)
:triangle(first->getPoint(), second->getPoint(), third->getPoint()),skin(levelOfDetail, Triangle(triangle.firstPoint().distance(triangle.secondPoint()))) {
	relatedNodes[0] = first;
	relatedNodes[1] = second;
	relatedNodes[2] = third;
}

FaceNode::FaceNode(unsigned int numConnected, TriangleElement triangle):numberConnected(0){
	this->element = triangle;
	connectedNodes = new FaceNode*[numConnected];
}

void FaceNode::setConnected(FaceNode* node) {
	connectedNodes[numberConnected] = node;
	numberConnected++;
}

FaceNode* FaceNode::getConnected(int index) {
	return connectedNodes[index];
}
