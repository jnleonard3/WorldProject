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
	IcosahedronDrawer(IcosahedronGraph &shape);
	virtual ~IcosahedronDrawer();

	osg::Group& getGroup() { return *group; };

	static osg::Group* drawIcosahedron(IcosahedronGraph &shape);
private:
	IcosahedronGraph &icosahedron;
	osg::Group *group;
	osg::Vec3Array **vertices;

	class TriangleSkinPrimitiveNode;
	TriangleSkinPrimitiveNode **primitiveNode;
};

#endif /* ICOSAHEDRONDRAWER_H_ */
