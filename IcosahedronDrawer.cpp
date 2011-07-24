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
#include <iostream>

IcosahedronDrawer::IcosahedronDrawer() {
}

IcosahedronDrawer::~IcosahedronDrawer() {
}

struct PointVertex {
	PointVertex(unsigned int r, unsigned int c, unsigned int i)
	:row(r),col(c),index(i){};
	unsigned int row, col, index;
};

osg::Group* IcosahedronDrawer::drawIcosahedron(IcosahedronGraph &shape) {

	MessageLogger::print("Building Icosahedron.");
	osg::Group* root = new osg::Group();

	osg::Vec4Array* colors = new osg::Vec4Array;
	for(unsigned int i = 0; i <= 1000; i++) {
		colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
		colors->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
		colors->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	}

	unsigned int trianglesRendered = 0;

	for (int i = 0; i < 20; ++i) {
		osg::Geode* icosahedronGeode = new osg::Geode();
		osg::Geometry* icosahedronGeometry = new osg::Geometry();

		icosahedronGeode->addDrawable(icosahedronGeometry);
		root->addChild(icosahedronGeode);

		osg::Vec3Array* vertices = new osg::Vec3Array;
		TriangleTerrainSkin skin = shape.getFaceNode(i).getTriangle().skin;

		std::vector<unsigned int> offsetCountSum;
		for (unsigned int y = 0; y < skin.getYOffsetCount(); ++y) {
			std::cout << skin.getCoordinatePoint(0, y).getPoint().y() << ": ";
			for (unsigned int x = 0; x < skin.getXOffsetCount(y); ++x) {
				CoordinatePoint pt = skin.getCoordinatePoint(x, y);
				Point pt2 = shape.getCoordinateSystem().convertTo(shape.getCoordinateSystem(), pt).getPoint();
				vertices->push_back(osg::Vec3(pt2.x(), pt2.y(), pt2.z()));
				std::cout << pt2.x() << ", ";
			}
			std::cout << "\n";
			if(offsetCountSum.size() == 0) {
				offsetCountSum.push_back(0);
			} else {
				offsetCountSum.push_back(offsetCountSum.at(y-1)+skin.getXOffsetCount(y-1));
			}
		}
		icosahedronGeometry->setVertexArray(vertices);

		for(unsigned int y = 0; y < (skin.getYOffsetCount()-1); ++y) {
			for(unsigned int x = 0; x < skin.getXOffsetCount(y); ++x) {
				Point pt = skin.getVertex(x,y);
				bool triangleFound = false;
				for(unsigned int v = y+1; v < skin.getYOffsetCount(); ++v) {
					for(unsigned int u = 0; u < skin.getXOffsetCount(y)-1; ++u) {
						Point pt2 = skin.getVertex(u,v);
						if(pt.x() < pt2.x()) {
							Point pt3 = skin.getVertex(u+1,v);
							if(pt.x() > pt3.x()) {
								osg::DrawElementsUInt* vert = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
								vert->push_back(offsetCountSum.at(y)+x);
								vert->push_back(offsetCountSum.at(v)+u);
								vert->push_back(offsetCountSum.at(v)+u+1);
								icosahedronGeometry->addPrimitiveSet(vert);
								trianglesRendered++;
								triangleFound = true;
								break;
							}
						}
					}
					if(triangleFound) {
						triangleFound = false;
						break;
					}
				}

				if(x < (skin.getXOffsetCount(y)-1)) {
					Point pt2 = skin.getVertex(x+1,y);
					for(unsigned int v = y+1; v < skin.getYOffsetCount(); ++v) {
						for(unsigned int u = 0; u < skin.getXOffsetCount(y); ++u) {
							Point pt3 = skin.getVertex(u,v);
							if(pt3.x() < pt.x() && pt3.x() > pt2.x()) {
									osg::DrawElementsUInt* vert = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
									vert->push_back(offsetCountSum.at(y)+x);
									vert->push_back(offsetCountSum.at(y)+x+1);
									vert->push_back(offsetCountSum.at(v)+u);
									icosahedronGeometry->addPrimitiveSet(vert);
									triangleFound = true;
									break;
							}
						}
						if(triangleFound) {
							triangleFound = false;
							break;
						}
					}
				}
			}
		}
/*
		osg::DrawElementsUInt* vert = new osg::DrawElementsUInt(
				osg::PrimitiveSet::LINE_STRIP, 0);
		for(unsigned int j = 0; j < vertices->size();++j) {
			vert->push_back(j);
		}
		//icosahedronGeometry->addPrimitiveSet(vert);
*/
		icosahedronGeometry->setColorArray(colors);
		icosahedronGeometry->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE);
	}
	MessageLogger::getInstance() << "Rendered " << trianglesRendered << " triangles.\n";
	MessageLogger::print("Building Icosahedron Complete.");
	return root;
}
