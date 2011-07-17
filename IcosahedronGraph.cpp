/*
 * IcosahedronGraph.cpp
 *
 *  Created on: Jul 16, 2011
 *      Author: Jon
 */

#include "IcosahedronGraph.h"

#include "math.h"

IcosahedronGraph::IcosahedronGraph(double radius) {

	double sideLength = (4.0/sqrt(10.0+2.0*sqrt(5.0))) * radius;
	double sideLengthHalf = sideLength/2.0;
	double goldenRatio = (1.0+sqrt(5))/2.0;
	double secondPoint = sideLengthHalf * goldenRatio;

	rootVertexNode = VertexNode(5, Point(0,sideLengthHalf, secondPoint));

	vertexNodes = new VertexNode[11];
	vertexNodes[0] = VertexNode(5, Point(0, -sideLengthHalf, secondPoint));
	vertexNodes[1] = VertexNode(5, Point(0, sideLengthHalf, -secondPoint));
	vertexNodes[2] = VertexNode(5, Point(0, -sideLengthHalf, -secondPoint));
	vertexNodes[3] = VertexNode(5, Point(sideLengthHalf, secondPoint, 0));
	vertexNodes[4] = VertexNode(5, Point(-sideLengthHalf, secondPoint, 0));
	vertexNodes[5] = VertexNode(5, Point(sideLengthHalf, -secondPoint, 0));
	vertexNodes[6] = VertexNode(5, Point(-sideLengthHalf, -secondPoint, 0));
	vertexNodes[7] = VertexNode(5, Point(secondPoint, 0, sideLengthHalf));
	vertexNodes[8] = VertexNode(5, Point(secondPoint, 0, -sideLengthHalf));
	vertexNodes[9] = VertexNode(5, Point(-secondPoint, 0, sideLengthHalf));
	vertexNodes[10] = VertexNode(5, Point(-secondPoint, 0, -sideLengthHalf));

	getVertexNode(0).setConnected(&getVertexNode(1));
	getVertexNode(0).setConnected(&getVertexNode(4));
	getVertexNode(0).setConnected(&getVertexNode(5));
	getVertexNode(0).setConnected(&getVertexNode(8));
	getVertexNode(0).setConnected(&getVertexNode(10));

	getVertexNode(1).setConnected(&getVertexNode(0));
	getVertexNode(1).setConnected(&getVertexNode(6));
	getVertexNode(1).setConnected(&getVertexNode(7));
	getVertexNode(1).setConnected(&getVertexNode(8));
	getVertexNode(1).setConnected(&getVertexNode(10));

	getVertexNode(2).setConnected(&getVertexNode(3));
	getVertexNode(2).setConnected(&getVertexNode(4));
	getVertexNode(2).setConnected(&getVertexNode(5));
	getVertexNode(2).setConnected(&getVertexNode(9));
	getVertexNode(2).setConnected(&getVertexNode(11));

	getVertexNode(3).setConnected(&getVertexNode(2));
	getVertexNode(3).setConnected(&getVertexNode(6));
	getVertexNode(3).setConnected(&getVertexNode(7));
	getVertexNode(3).setConnected(&getVertexNode(9));
	getVertexNode(3).setConnected(&getVertexNode(11));

	getVertexNode(4).setConnected(&getVertexNode(0));
	getVertexNode(4).setConnected(&getVertexNode(2));
	getVertexNode(4).setConnected(&getVertexNode(5));
	getVertexNode(4).setConnected(&getVertexNode(8));
	getVertexNode(4).setConnected(&getVertexNode(9));

	getVertexNode(5).setConnected(&getVertexNode(0));
	getVertexNode(5).setConnected(&getVertexNode(2));
	getVertexNode(5).setConnected(&getVertexNode(4));
	getVertexNode(5).setConnected(&getVertexNode(10));
	getVertexNode(5).setConnected(&getVertexNode(11));

	getVertexNode(6).setConnected(&getVertexNode(1));
	getVertexNode(6).setConnected(&getVertexNode(3));
	getVertexNode(6).setConnected(&getVertexNode(7));
	getVertexNode(6).setConnected(&getVertexNode(8));
	getVertexNode(6).setConnected(&getVertexNode(9));

	getVertexNode(7).setConnected(&getVertexNode(1));
	getVertexNode(7).setConnected(&getVertexNode(3));
	getVertexNode(7).setConnected(&getVertexNode(6));
	getVertexNode(7).setConnected(&getVertexNode(10));
	getVertexNode(7).setConnected(&getVertexNode(11));

	getVertexNode(8).setConnected(&getVertexNode(0));
	getVertexNode(8).setConnected(&getVertexNode(1));
	getVertexNode(8).setConnected(&getVertexNode(4));
	getVertexNode(8).setConnected(&getVertexNode(6));
	getVertexNode(8).setConnected(&getVertexNode(9));

	getVertexNode(9).setConnected(&getVertexNode(2));
	getVertexNode(9).setConnected(&getVertexNode(3));
	getVertexNode(9).setConnected(&getVertexNode(4));
	getVertexNode(9).setConnected(&getVertexNode(6));
	getVertexNode(9).setConnected(&getVertexNode(8));

	getVertexNode(10).setConnected(&getVertexNode(0));
	getVertexNode(10).setConnected(&getVertexNode(1));
	getVertexNode(10).setConnected(&getVertexNode(5));
	getVertexNode(10).setConnected(&getVertexNode(7));
	getVertexNode(10).setConnected(&getVertexNode(11));

	getVertexNode(11).setConnected(&getVertexNode(2));
	getVertexNode(11).setConnected(&getVertexNode(3));
	getVertexNode(11).setConnected(&getVertexNode(5));
	getVertexNode(11).setConnected(&getVertexNode(7));
	getVertexNode(11).setConnected(&getVertexNode(10));

	rootFaceNode = FaceNode(3, TriangleElement( &getVertexNode(0),
												&getVertexNode(1),
												&getVertexNode(8)));

	faceNodes = new FaceNode[19];
	faceNodes[0] = FaceNode(3, TriangleElement( &getVertexNode(0),
												&getVertexNode(1),
												&getVertexNode(10)));

	faceNodes[1] = FaceNode(3, TriangleElement( &getVertexNode(2),
												&getVertexNode(3),
												&getVertexNode(9)));

	faceNodes[2] = FaceNode(3, TriangleElement( &getVertexNode(2),
												&getVertexNode(3),
												&getVertexNode(11)));

	faceNodes[3] = FaceNode(3, TriangleElement( &getVertexNode(4),
												&getVertexNode(5),
												&getVertexNode(0)));

	faceNodes[4] = FaceNode(3, TriangleElement( &getVertexNode(4),
												&getVertexNode(5),
												&getVertexNode(2)));

	faceNodes[5] = FaceNode(3, TriangleElement( &getVertexNode(6),
												&getVertexNode(7),
												&getVertexNode(1)));

	faceNodes[6] = FaceNode(3, TriangleElement( &getVertexNode(6),
												&getVertexNode(7),
												&getVertexNode(3)));

	faceNodes[7] = FaceNode(3, TriangleElement( &getVertexNode(8),
												&getVertexNode(9),
												&getVertexNode(4)));

	faceNodes[8] = FaceNode(3, TriangleElement( &getVertexNode(8),
												&getVertexNode(9),
												&getVertexNode(6)));

	faceNodes[9] = FaceNode(3, TriangleElement( &getVertexNode(10),
												&getVertexNode(11),
												&getVertexNode(5)));

	faceNodes[10] = FaceNode(3, TriangleElement( &getVertexNode(10),
												 &getVertexNode(11),
												 &getVertexNode(7)));

	faceNodes[11] = FaceNode(3, TriangleElement( &getVertexNode(0),
												 &getVertexNode(4),
												 &getVertexNode(8)));

	faceNodes[12] = FaceNode(3, TriangleElement( &getVertexNode(0),
												 &getVertexNode(5),
												 &getVertexNode(10)));

	faceNodes[13] = FaceNode(3, TriangleElement( &getVertexNode(1),
												 &getVertexNode(6),
												 &getVertexNode(8)));

	faceNodes[14] = FaceNode(3, TriangleElement( &getVertexNode(1),
												 &getVertexNode(7),
												 &getVertexNode(10)));

	faceNodes[15] = FaceNode(3, TriangleElement( &getVertexNode(2),
												 &getVertexNode(4),
												 &getVertexNode(9)));

	faceNodes[16] = FaceNode(3, TriangleElement( &getVertexNode(2),
												 &getVertexNode(5),
												 &getVertexNode(11)));

	faceNodes[17] = FaceNode(3, TriangleElement( &getVertexNode(3),
												 &getVertexNode(7),
												 &getVertexNode(11)));

	faceNodes[18] = FaceNode(3, TriangleElement( &getVertexNode(3),
												 &getVertexNode(6),
												 &getVertexNode(9)));

	getFaceNode(0).setConnected(&getFaceNode(1));
	getFaceNode(0).setConnected(&getFaceNode(12));
	getFaceNode(0).setConnected(&getFaceNode(14));

	getFaceNode(1).setConnected(&getFaceNode(0));
	getFaceNode(1).setConnected(&getFaceNode(13));
	getFaceNode(1).setConnected(&getFaceNode(15));

	getFaceNode(2).setConnected(&getFaceNode(3));
	getFaceNode(2).setConnected(&getFaceNode(16));
	getFaceNode(2).setConnected(&getFaceNode(19));

	getFaceNode(3).setConnected(&getFaceNode(2));
	getFaceNode(3).setConnected(&getFaceNode(17));
	getFaceNode(3).setConnected(&getFaceNode(18));

	getFaceNode(4).setConnected(&getFaceNode(5));
	getFaceNode(4).setConnected(&getFaceNode(12));
	getFaceNode(4).setConnected(&getFaceNode(13));

	getFaceNode(5).setConnected(&getFaceNode(4));
	getFaceNode(5).setConnected(&getFaceNode(16));
	getFaceNode(5).setConnected(&getFaceNode(17));

	getFaceNode(6).setConnected(&getFaceNode(7));
	getFaceNode(6).setConnected(&getFaceNode(14));
	getFaceNode(6).setConnected(&getFaceNode(15));

	getFaceNode(7).setConnected(&getFaceNode(6));
	getFaceNode(7).setConnected(&getFaceNode(18));
	getFaceNode(7).setConnected(&getFaceNode(19));

	getFaceNode(8).setConnected(&getFaceNode(9));
	getFaceNode(8).setConnected(&getFaceNode(12));
	getFaceNode(8).setConnected(&getFaceNode(16));

	getFaceNode(9).setConnected(&getFaceNode(8));
	getFaceNode(9).setConnected(&getFaceNode(14));
	getFaceNode(9).setConnected(&getFaceNode(19));

	getFaceNode(10).setConnected(&getFaceNode(11));
	getFaceNode(10).setConnected(&getFaceNode(13));
	getFaceNode(10).setConnected(&getFaceNode(17));

	getFaceNode(11).setConnected(&getFaceNode(10));
	getFaceNode(11).setConnected(&getFaceNode(15));
	getFaceNode(11).setConnected(&getFaceNode(18));

	getFaceNode(12).setConnected(&getFaceNode(0));
	getFaceNode(12).setConnected(&getFaceNode(4));
	getFaceNode(12).setConnected(&getFaceNode(8));

	getFaceNode(13).setConnected(&getFaceNode(1));
	getFaceNode(13).setConnected(&getFaceNode(4));
	getFaceNode(13).setConnected(&getFaceNode(10));

	getFaceNode(14).setConnected(&getFaceNode(0));
	getFaceNode(14).setConnected(&getFaceNode(6));
	getFaceNode(14).setConnected(&getFaceNode(9));

	getFaceNode(15).setConnected(&getFaceNode(1));
	getFaceNode(15).setConnected(&getFaceNode(6));
	getFaceNode(15).setConnected(&getFaceNode(11));

	getFaceNode(16).setConnected(&getFaceNode(2));
	getFaceNode(16).setConnected(&getFaceNode(5));
	getFaceNode(16).setConnected(&getFaceNode(8));

	getFaceNode(17).setConnected(&getFaceNode(3));
	getFaceNode(17).setConnected(&getFaceNode(5));
	getFaceNode(17).setConnected(&getFaceNode(10));

	getFaceNode(18).setConnected(&getFaceNode(3));
	getFaceNode(18).setConnected(&getFaceNode(7));
	getFaceNode(18).setConnected(&getFaceNode(11));

	getFaceNode(19).setConnected(&getFaceNode(2));
	getFaceNode(19).setConnected(&getFaceNode(7));
	getFaceNode(19).setConnected(&getFaceNode(9));

}

VertexNode& IcosahedronGraph::getVertexNode(int node) {
	if(node == 0) {
		return rootVertexNode;
	} else {
		return vertexNodes[node-1];
	}
}

FaceNode& IcosahedronGraph::getFaceNode(int node) {
	if(node == 0) {
		return rootFaceNode;
	} else {
		return faceNodes[node-1];
	}
}
