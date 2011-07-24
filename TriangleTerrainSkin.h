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

#include <vector>

class TriangleTerrainSkin {
public:
	TriangleTerrainSkin(Point top, Point left, Point right);
	TriangleTerrainSkin(unsigned int lod, Point top, Point left, Point right);
	TriangleTerrainSkin(unsigned int lod, Triangle tri);
	virtual ~TriangleTerrainSkin();

	unsigned int getYOffsetCount();
	unsigned int getXOffsetCount(unsigned int yIndex);
	Point getVertex(unsigned int x, unsigned int y);
	CoordinatePoint getCoordinatePoint(unsigned x, unsigned y);

	PyramidCoordinateSpace& getCoordinateSpace() { return coordSystem; };


private:
	Point topPoint, leftPoint, rightPoint;

	class TriangleTerrainSkinNode;
	TriangleTerrainSkinNode *rootNode;

	PyramidCoordinateSpace coordSystem;

	struct TerrainVertex {
		TerrainVertex(double x, double ht)
		:xOffset(x),height(ht) {

		}
		double xOffset, height;
	};

	unsigned int addYOffset(double val);
	void addHeightEntry(unsigned int index, double xOffset, double height);
	void addPointToHeightMap(Point pt);

	std::vector<double> heightOffsets;
	std::vector<std::vector<TerrainVertex> > heightMap;
};

#endif /* TRIANGLETERRAINSKIN_H_ */
