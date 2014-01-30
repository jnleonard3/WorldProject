/*
 * PyramidCoordinateSpace.cpp
 *
 *  Created on: Jul 18, 2011
 *      Author: Jon
 */

#include "PyramidCoordinateSpace.h"

#include "math.h"

PyramidCoordinateSpace::PyramidCoordinateSpace(double length):
name("PyramidCoordinateSpace"),sideLength(length){
	originHeight = (sqrt(6)/3.0)*sideLength;
}

PyramidCoordinateSpace::PyramidCoordinateSpace(Point a, Point b, Point c):
name("PyramidCoordinateSpace"),sideLength(a.distance(b)){
	originHeight = (sqrt(6)/3.0)*sideLength;
}

PyramidCoordinateSpace::PyramidCoordinateSpace(const PyramidCoordinateSpace& a):
CoordinateSystem(a),name("PyramidCoordinateSpace"),sideLength(a.sideLength){
	originHeight = (sqrt(6)/3.0)*sideLength;
}

bool PyramidCoordinateSpace::isValid(const Point& pt) const
{
	double modifiedHeight = originHeight + pt.z();
	double newSideLength = (3.0/sqrt(6))*modifiedHeight;
	double ptCoord = (sqrt(3)/4.0)*newSideLength;
	Point a(0.0,ptCoord,0.0), b(-ptCoord,-ptCoord,0.0), c(ptCoord,-ptCoord,0.0);

	Vector v0(c,a), v1(b,a), v2(pt,a);
	double dot00 = v0.dotProduct(v0), dot01 = v0.dotProduct(v1), dot02 = v0.dotProduct(v2);
	double dot11 = v1.dotProduct(v1), dot12 = v1.dotProduct(v2);
	double invDenom = 1.0/(dot00 * dot11 - dot01 * dot01);
	double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	double v = (dot00 * dot12 - dot01 * dot02) * invDenom;

	return (u > 0) && (v > 0) && (u + v < 1);
}

