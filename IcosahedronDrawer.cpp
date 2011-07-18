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
#include <osg/Material>
#include <osg/StateSet>
#include <osg/Texture2D>
#include <osgDB/ReadFile>

#include "MessageLogger.h"

IcosahedronDrawer::IcosahedronDrawer() {
}

IcosahedronDrawer::~IcosahedronDrawer() {
}

osg::Group* IcosahedronDrawer::drawIcosahedron(IcosahedronGraph &shape) {

	MessageLogger::print("Building Icosahedron.");
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

    osg::Material *material = new osg::Material();
    material->setEmission(osg::Material::FRONT, osg::Vec4(0.8, 0.8, 0.8, 1.0));

    osg::Image *image = osgDB::readImageFile("Dirttexture.jpg");
    if (!image) {
    	std::cout << "Couldn't load texture." << std::endl;
    	return NULL;
    }

    osg::Texture2D *texture = new osg::Texture2D;
    texture->setDataVariance(osg::Object::DYNAMIC);
    texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
    texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
    texture->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP);
    texture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP);
    texture->setImage(image);

    osg::StateSet *stateSet = icosahedronGeode->getOrCreateStateSet();
    stateSet->ref();
    stateSet->setAttribute(material);
    stateSet->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);
    MessageLogger::print("Building Icosahedron Complete.");
    return root;
}
