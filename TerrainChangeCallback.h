/*
 * TerrainChangeCallback.h
 *
 *  Created on: Jul 30, 2011
 *      Author: Jon
 */

#ifndef TERRAINCHANGECALLBACK_H_
#define TERRAINCHANGECALLBACK_H_

#include "PointIndex.h"

class TerrainChangeCallback {
	void notifyChange(unsigned int notifierId, PointIndex pt);
};

class TerrainChangeNotifier {
public:
	TerrainChangeNotifier():id(nextId){
		nextId++;
	}

	unsigned int getNotifierId() const { return id; };

private:
	static unsigned int nextId;

	const unsigned int id;
};


#endif /* TERRAINCHANGECALLBACK_H_ */
