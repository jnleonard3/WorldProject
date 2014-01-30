/*
 * PointIndex.h
 *
 *  Created on: Jul 30, 2011
 *      Author: Jon
 */

#ifndef POINTINDEX_H_
#define POINTINDEX_H_

struct PointIndex {
	PointIndex(unsigned int i, Point &pt) :
			index(i), point(pt) {
	}

	unsigned int index;
	Point& point;
};

#endif /* POINTINDEX_H_ */
