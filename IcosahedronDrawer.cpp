/*
 * IcosahedronDrawer.cpp
 *
 *  Created on: Jul 17, 2011
 *      Author: Jon
 */

#include "IcosahedronDrawer.h"

#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Texture2D>

IcosahedronDrawer::IcosahedronDrawer() {
}

IcosahedronDrawer::~IcosahedronDrawer() {
}

osg::Group* IcosahedronDrawer::drawIcosahedron(IcosahedronGraph &shape) {

	osg::Group* root = new osg::Group();
	osg::Geode* icosahedronGeode = new osg::Geode();
	osg::Geometry* icosahedronGeometry = new osg::Geometry();

	icosahedronGeode->addDrawable(icosahedronGeometry);
	root->addChild(icosahedronGeode);

	osg::Vec3Array* vertices = new osg::Vec3Array;
	for(int i = 0; i < 12; ++i) {
		Point pt = shape.getVertexNode(i).getPoint();
		vertices->push_back(osg::Vec3(pt.x(), pt.y(), pt.z()));
	}
	icosahedronGeometry->setVertexArray(vertices);

	for(int i = 0; i < 20; ++i) {
		TriangleElement elem = shape.getFaceNode(i).getTriangle();
		osg::DrawElementsUInt* tri = new osg::DrawElementsUInt(
				osg::PrimitiveSet::TRIANGLES, 0);
		tri->push_back(shape.getVertexNodeIndex(elem.relatedNodes[0]));
		tri->push_back(shape.getVertexNodeIndex(elem.relatedNodes[1]));
		tri->push_back(shape.getVertexNodeIndex(elem.relatedNodes[2]));
		icosahedronGeometry->addPrimitiveSet(tri);
	}

    osg::Vec4Array* colors = new osg::Vec4Array;
    colors->push_back(osg::Vec4(0.0f, 1.0f, 1.0f, 0.5f) );
    colors->push_back(osg::Vec4(1.0f, 1.0f, 0.0f, 0.5f) );
    colors->push_back(osg::Vec4(1.0f, 0.0f, 1.0f, 0.5f) );
    colors->push_back(osg::Vec4(0.0f, 0.5f, 0.5f, 0.5f) );
    colors->push_back(osg::Vec4(0.5f, 0.5f, 0.0f, 0.5f) );
    colors->push_back(osg::Vec4(0.5f, 0.0f, 0.5f, 0.5f) );
    colors->push_back(osg::Vec4(0.0f, 1.0f, 0.5f, 0.5f) );
    colors->push_back(osg::Vec4(1.0f, 0.5f, 0.0f, 0.5f) );
    colors->push_back(osg::Vec4(1.0f, 0.0f, 0.5f, 0.5f) );
    colors->push_back(osg::Vec4(0.0f, 0.5f, 1.0f, 0.5f) );
    colors->push_back(osg::Vec4(0.5f, 1.0f, 0.0f, 0.5f) );
    colors->push_back(osg::Vec4(0.5f, 0.0f, 1.0f, 0.5f) );
    colors->push_back(osg::Vec4(0.0f, 0.25f, 0.25f, 0.5f) );
    colors->push_back(osg::Vec4(0.25f, 0.25f, 0.0f, 0.5f) );
    colors->push_back(osg::Vec4(0.25f, 0.0f, 0.25f, 0.5f) );
    colors->push_back(osg::Vec4(0.0f, 1.0f, 0.25f, 0.5f) );
    colors->push_back(osg::Vec4(1.0f, 0.25f, 0.0f, 0.5f) );
    colors->push_back(osg::Vec4(1.0f, 0.0f, 0.25f, 0.5f) );
    colors->push_back(osg::Vec4(0.0f, 0.25f, 1.0f, 0.5f) );
    colors->push_back(osg::Vec4(0.25f, 1.0f, 0.0f, 0.5f) );
    colors->push_back(osg::Vec4(0.25f, 0.0f, 1.0f, 0.5f) );

    icosahedronGeometry->setColorArray(colors);
    icosahedronGeometry->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE);

    return root;
}
