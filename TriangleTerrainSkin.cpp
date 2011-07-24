/*
 * TriangleTerrainSkin.cpp
 *
 *  Created on: Jul 19, 2011
 *      Author: Jon
 */

#include "TriangleTerrainSkin.h"
#include "MessageLogger.h"

#include <iostream>

struct TriangleTerrainSkin::TriangleTerrainSkinNode {
	
	TriangleTerrainSkinNode(TriangleTerrainSkin& skin, Point& topPt, Point& leftPt, Point& rightPt):
		terrainSkin(skin),
		top(topPt),left(leftPt),right(rightPt),
		topNode(0),leftNode(0),middleNode(0),rightNode(0)
	{
		Vector v1(top,left), v2(top,right), v3(left,right);
		v1 = v1.scale(0.5);
		v2 = v2.scale(0.5);
		v3 = v3.scale(0.5);
		leftMid = v1.translate(top);
		rightMid = v2.translate(top);
		bottom = v3.translate(left);
		skin.addPointToHeightMap(leftMid);
		skin.addPointToHeightMap(rightMid);
		skin.addPointToHeightMap(bottom);
	}

	void generateNextLevel() {
		if(topNode == 0) {
			topNode = new TriangleTerrainSkinNode(terrainSkin,top,leftMid,rightMid);
		} else {
			topNode->generateNextLevel();
		}

		if(leftNode == 0) {
			leftNode = new TriangleTerrainSkinNode(terrainSkin,leftMid,left,bottom);
		} else {
			leftNode->generateNextLevel();
		}

		if(middleNode == 0) {
			middleNode = new TriangleTerrainSkinNode(terrainSkin,bottom,rightMid,leftMid);
		} else {
			middleNode->generateNextLevel();
		}

		if(rightNode == 0) {
			rightNode = new TriangleTerrainSkinNode(terrainSkin,rightMid,bottom,right);
		} else {
			rightNode->generateNextLevel();
		}
	}

	TriangleTerrainSkin& terrainSkin;
	Point &top, &left, &right;
	Point bottom, leftMid, rightMid;
	TriangleTerrainSkinNode *topNode, *leftNode, *middleNode, *rightNode;
};

TriangleTerrainSkin::TriangleTerrainSkin(Point top, Point left, Point right):
topPoint(top),leftPoint(left),rightPoint(right),rootNode(0),
coordSystem(top,left,right){
	addPointToHeightMap(topPoint);
	addPointToHeightMap(leftPoint);
	addPointToHeightMap(rightPoint);
}

TriangleTerrainSkin::TriangleTerrainSkin(unsigned int lod, Point top, Point left, Point right):
topPoint(top),leftPoint(left),rightPoint(right),rootNode(0),
coordSystem(top,left,right){
	addPointToHeightMap(topPoint);
	addPointToHeightMap(leftPoint);
	addPointToHeightMap(rightPoint);
	for(unsigned int i = 0; i < lod; ++i) {
		if(rootNode == 0) {
			rootNode = new TriangleTerrainSkinNode(*this,topPoint,leftPoint,rightPoint);
		} else {
			rootNode->generateNextLevel();
		}
	}
}

TriangleTerrainSkin::TriangleTerrainSkin(unsigned int lod, Triangle tri):
topPoint(tri.firstPoint()),leftPoint(tri.secondPoint()),rightPoint(tri.thirdPoint()),rootNode(0),
coordSystem(topPoint,leftPoint,rightPoint){
	addPointToHeightMap(topPoint);
	addPointToHeightMap(leftPoint);
	addPointToHeightMap(rightPoint);
	for(unsigned int i = 0; i < lod; ++i) {
		if(rootNode == 0) {
			rootNode = new TriangleTerrainSkinNode(*this,topPoint,leftPoint,rightPoint);
		} else {
			rootNode->generateNextLevel();
		}
	}
}

TriangleTerrainSkin::~TriangleTerrainSkin() {

}

unsigned int TriangleTerrainSkin::getYOffsetCount() {
	return heightOffsets.size();
}

unsigned int TriangleTerrainSkin::getXOffsetCount(unsigned int yIndex) {
	return heightMap.at(yIndex).size();
}

Point TriangleTerrainSkin::getVertex(unsigned int xIndex, unsigned int yIndex) {
	double x = heightMap.at(yIndex).at(xIndex).xOffset;
	double y = heightOffsets.at(yIndex);
	double z = heightMap.at(yIndex).at(xIndex).height;
	return Point(x,y,z);
}

CoordinatePoint TriangleTerrainSkin::getCoordinatePoint(unsigned x, unsigned y) {
	Point pt = getVertex(x,y);
	return CoordinatePoint(pt,coordSystem,coordSystem.isValid(pt));
}

unsigned int TriangleTerrainSkin::addYOffset(double val) {
	std::vector<double>::iterator itr = heightOffsets.begin();
	std::vector<std::vector<TerrainVertex> >::iterator itr2 = heightMap.begin();
	unsigned int i = 0;
	while(itr != heightOffsets.end()) {
		if(fabs(*itr - val) < 0.01) {
			return i;
		} else if(*itr < val) {
			break;
		}
		itr++;
		itr2++;
		i++;
	}
	heightOffsets.insert(itr,val);
	heightMap.insert(itr2,std::vector<TerrainVertex>());
	return i;
}

void TriangleTerrainSkin::addHeightEntry(unsigned int index, double xOffset, double height) {
	std::vector<TerrainVertex>::iterator itr = heightMap.at(index).begin();
	while(itr != heightMap.at(index).end()) {
		if(itr->xOffset == xOffset) {
			return;
		} else if(itr->xOffset < xOffset) {
			break;
		}
		itr++;
	}
	heightMap.at(index).insert(itr,TerrainVertex(xOffset,height));
}

void TriangleTerrainSkin::addPointToHeightMap(Point pt) {
	unsigned int index = addYOffset(pt.y());
	addHeightEntry(index,pt.x(),pt.z());
}
