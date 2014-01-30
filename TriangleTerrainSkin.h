/*
 * TriangleTerrainSkin.h
 *
 *  Created on: Jul 19, 2011
 *      Author: Jon
 */

#ifndef TRIANGLETERRAINSKIN_H_
#define TRIANGLETERRAINSKIN_H_

#include "CommonGeometry.h"

#include "PyramidCoordinateSpace.h"
#include "CoordinatePoint.h"
#include "PointIndex.h"
#include "BlockArray.h"

class TriangleTerrainSkin {
public:
	TriangleTerrainSkin(unsigned int lod, Triangle tri);
	virtual ~TriangleTerrainSkin();

	PyramidCoordinateSpace& getCoordinateSpace() { return coordSystem; };

	struct IndexTriangle {
		unsigned int first, second, third;
	};

private:
	Point topPoint, leftPoint, rightPoint;

	class TriangleTerrainSkinNode;
	TriangleTerrainSkinNode *rootNode;

	PyramidCoordinateSpace coordSystem;

	struct IndexedPoint {
		IndexedPoint():available(true){}
		IndexedPoint(Point& pt):available(false),point(pt){}

		bool available;
		Point point;
	};

	struct FreeSpaceNode;
	FreeSpaceNode *freeSpaceRoot;

	PointIndex addPointElement(Point pt);
	void freePointElement(unsigned int index);

	BlockArray<IndexedPoint> pointArray;

	friend class IcosahedronDrawer;
};

#endif /* TRIANGLETERRAINSKIN_H_ */
