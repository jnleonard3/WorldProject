/*
 * CoordinateSystem.cpp
 *
 *  Created on: Jul 18, 2011
 *      Author: Jon
 */

#include "CoordinateSystem.h"

#include "CoordinatePoint.h"

unsigned int CoordinateSystem::globalNextId = 1;

CoordinatePoint CoordinateSystem::convertTo(const CoordinateSystem& toSystem, const CoordinatePoint& thisPoint) const {
	CoordinatePoint localConversion = this->actualConvertTo(toSystem,thisPoint);
	if(localConversion.getIsValid()) {
		return localConversion;
	} else {
		return toSystem.actualConvertTo(toSystem,thisPoint);
	}
}

CoordinatePoint CoordinateSystem::actualConvertTo(const CoordinateSystem& toSystem, const CoordinatePoint& thisPoint) const {
	return CoordinatePoint(Point(0,0,0),toSystem,false);
}
