/*
 * IcosahedronDrawer.h
 *
 *  Created on: Jul 17, 2011
 *      Author: Jon
 */

#ifndef ICOSAHEDRONDRAWER_H_
#define ICOSAHEDRONDRAWER_H_

#include <osg/Group>

#include "IcosahedronGraph.h"

class IcosahedronDrawer {
public:
	static osg::Group* drawIcosahedron(IcosahedronGraph &shape);

	virtual ~IcosahedronDrawer();
private:
	IcosahedronDrawer();
};

#endif /* ICOSAHEDRONDRAWER_H_ */
