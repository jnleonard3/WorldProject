#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/PositionAttitudeTransform>
#include <osgGA/TrackballManipulator>

#include "math.h"
#include "IcosahedronGraph.h"
#include "IcosahedronDrawer.h"
#include <iostream>

int main() {
	osgViewer::Viewer viewer;
	osg::Group* root = new osg::Group();

	IcosahedronGraph ico(1700.0);
	osg::Group* icosahedronRoot = IcosahedronDrawer::drawIcosahedron(ico);
	root->addChild(icosahedronRoot);

	// switch off lighting as we haven't assigned any normals.
	root->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	root->getOrCreateStateSet()->setMode( GL_BLEND, osg::StateAttribute::ON );
	root->getOrCreateStateSet()->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );

	//The final step is to set up and enter a simulation loop.

	viewer.setSceneData(root);
	//viewer.run();

	viewer.setCameraManipulator(new osgGA::TrackballManipulator());
	viewer.realize();

	while (!viewer.done()) {
		viewer.frame();
	}

	return 0;
}
