/*
 * CoordinatePoint.cpp
 *
 *  Created on: Jul 18, 2011
 *      Author: Jon
 */

#include "CoordinatePoint.h"
#include "CoordinateSystem.h"

CoordinatePoint::CoordinatePoint(Point pt, const CoordinateSystem& sys):
isValid(true),point(pt),system(sys){

}
CoordinatePoint::CoordinatePoint(Point pt, const CoordinateSystem& sys, bool valid):
isValid(valid),point(pt),system(sys) {

}
CoordinatePoint::CoordinatePoint(const CoordinatePoint& pt):
isValid(pt.getIsValid()),point(pt.getPoint()),system(pt.getCoordinateSystem())	{

}

