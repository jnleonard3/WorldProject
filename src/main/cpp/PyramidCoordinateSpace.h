/*
 * PyramidCoordinateSpace.h
 *
 *  Created on: Jul 18, 2011
 *      Author: Jon
 */

#ifndef PYRAMIDCOORDINATESPACE_H_
#define PYRAMIDCOORDINATESPACE_H_

#include "CoordinateSystem.h"

class PyramidCoordinateSpace: public CoordinateSystem {
public:
	PyramidCoordinateSpace(double sideLength);
	PyramidCoordinateSpace(Point a, Point b, Point c);
	PyramidCoordinateSpace(const PyramidCoordinateSpace& a);
	virtual ~PyramidCoordinateSpace(){};

	virtual const char * getName() const { return name; };

	virtual bool isValid(const Point& pt) const;

private:
	const char * name;
	double sideLength, originHeight;
};

#endif /* PYRAMIDCOORDINATESPACE_H_ */
