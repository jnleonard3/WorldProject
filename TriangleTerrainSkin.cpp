/*
 * TriangleTerrainSkin.cpp
 *
 *  Created on: Jul 19, 2011
 *      Author: Jon
 */

#include "TriangleTerrainSkin.h"
#include "MessageLogger.h"

struct TriangleTerrainSkin::TriangleTerrainSkinNode {
	
	TriangleTerrainSkinNode(unsigned int height, Point& topPt, Point& leftPt, Point& rightPt):
		nodeHeight(height),
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
	}

	void generateNextLevel() {
		if(topNode == 0) {
			topNode = new TriangleTerrainSkinNode(nodeHeight+1,top,leftMid,rightMid);
		} else {
			topNode->generateNextLevel();
		}

		if(leftNode == 0) {
			leftNode = new TriangleTerrainSkinNode(nodeHeight+1,leftMid,left,bottom);
		} else {
			leftNode->generateNextLevel();
		}

		if(middleNode == 0) {
			middleNode = new TriangleTerrainSkinNode(nodeHeight+1,bottom,rightMid,leftMid);
		} else {
			middleNode->generateNextLevel();
		}

		if(rightNode == 0) {
			rightNode = new TriangleTerrainSkinNode(nodeHeight+1,rightMid,bottom,right);
		} else {
			rightNode->generateNextLevel();
		}
	}
	const unsigned int nodeHeight;
	Point &top, &left, &right;
	Point bottom, leftMid, rightMid;
	TriangleTerrainSkinNode *topNode, *leftNode, *middleNode, *rightNode;
};

TriangleTerrainSkin::TriangleTerrainSkin(unsigned int lod, Triangle tri):
topPoint(tri.firstPoint()),leftPoint(tri.secondPoint()),rightPoint(tri.thirdPoint()),rootNode(0),
coordSystem(topPoint,leftPoint,rightPoint){
	for(unsigned int i = 0; i < lod; ++i) {
		if(rootNode == 0) {
			rootNode = new TriangleTerrainSkinNode(0,topPoint,leftPoint,rightPoint);
		} else {
			rootNode->generateNextLevel();
		}
	}
}

TriangleTerrainSkin::~TriangleTerrainSkin() {

}

struct TriangleTerrainSkin::FreeSpaceNode {

	FreeSpaceNode(unsigned int frm, unsigned int to, FreeSpaceNode* nxt)
	:from(frm),toExclusive(to),next(nxt){};
	unsigned int from, toExclusive;
	FreeSpaceNode* next;
};

PointIndex TriangleTerrainSkin::addPointElement(Point pt) {
	if(freeSpaceRoot == 0) {
		IndexedPoint &pt = pointArray.pushBack(IndexedPoint(pt));
		return PointIndex(pointArray.getSize()-1, pt.point);
	} else {
		unsigned int index = freeSpaceRoot->from;
		freeSpaceRoot->from++;
		if(freeSpaceRoot->from == freeSpaceRoot->toExclusive) {
			FreeSpaceNode *oldNode = freeSpaceRoot;
			freeSpaceRoot = freeSpaceRoot->next;
			delete oldNode;
		}

		pointArray.at(index) = IndexedPoint(pt);
		IndexedPoint &pt = pointArray.at(index);
		return PointIndex(index, pt.point);
	}
}

void TriangleTerrainSkin::freePointElement(unsigned int index) {
	pointArray.at(index).available = true;
	if(freeSpaceRoot == 0) {
		freeSpaceRoot = new FreeSpaceNode(index, index+1, 0);
	} else if(freeSpaceRoot->from > index + 1) {
		FreeSpaceNode *node = new FreeSpaceNode(index, index+1, freeSpaceRoot);
		freeSpaceRoot = node;
	} else {
		FreeSpaceNode *node = freeSpaceRoot;
		while(true) {
			if(node->from == index + 1) {
				node->from--;
				return;
			} else if(node->toExclusive == index) {
				node->toExclusive++;
				return;
			} else if(node->next == 0 || node->next->from > index) {
				node->next = new FreeSpaceNode(index, index+1, node->next);
				return;
			} else {
				node = node->next;
			}
		}
	}
}
