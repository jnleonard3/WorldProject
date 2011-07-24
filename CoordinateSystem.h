/*
 * CoordinateSystem.h
 *
 *  Created on: Jul 18, 2011
 *      Author: Jon
 */

#ifndef COORDINATESYSTEM_H_
#define COORDINATESYSTEM_H_

#include "CommonGeometry.h"

enum CoordinateSystemType {
	COORDINATE_SYSTEM_XYZ = 1,
};

class CoordinatePoint;

class CoordinateSystem {
public:
	CoordinateSystem():id(globalNextId){ ++globalNextId; };
	CoordinateSystem(const CoordinateSystem& a):id(a.getId()){};
	virtual ~CoordinateSystem(){};

	unsigned int getId() const { return id; };

	virtual const char * getName() const = 0;

	CoordinatePoint convertTo(const CoordinateSystem& toSystem, const CoordinatePoint& thisPoint) const;

	virtual bool isValid(const Point& pt) const = 0;

protected:
	virtual CoordinatePoint actualConvertTo(const CoordinateSystem& toSystem, const CoordinatePoint& thisPoint) const;

private:
	static unsigned int globalNextId;

	unsigned int id;
};

#endif /* COORDINATESYSTEM_H_ */
