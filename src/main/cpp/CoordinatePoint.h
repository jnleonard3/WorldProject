/*
 * CoordinatePoint.h
 *
 *  Created on: Jul 18, 2011
 *      Author: Jon
 */

#ifndef COORDINATEPOINT_H_
#define COORDINATEPOINT_H_

#include "CommonGeometry.h"

class CoordinateSystem;

class CoordinatePoint {
public:
	CoordinatePoint(Point pt, const CoordinateSystem& sys);
	CoordinatePoint(Point pt, const CoordinateSystem& sys, bool valid);
	CoordinatePoint(const CoordinatePoint& pt);
	virtual ~CoordinatePoint() {};

	bool getIsValid() const { return isValid; };

	Point getPoint() const { return point; };

	const CoordinateSystem& getCoordinateSystem() const { return system; };

private:
	const bool isValid;
	const Point point;
	const CoordinateSystem& system;
};

#endif /* COORDINATEPOINT_H_ */
