#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Camera>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/PositionAttitudeTransform>
#include <osgGA/TrackballManipulator>

#include "math.h"
#include "IcosahedronGraph.h"
#include "IcosahedronDrawer.h"
#include "MessageLogger.h"
#include "PyramidCoordinateSpace.h"
#include "TriangleTerrainSkin.h"
#include <iostream>

int main() {
	const unsigned int SCREEN_HEIGHT = 900;
	const unsigned int SCREEN_WIDTH = 1440;

	osgViewer::Viewer viewer;
	osg::Group* root = new osg::Group();

    osg::Camera* camera = new osg::Camera;
    camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    camera->setProjectionMatrixAsOrtho2D(0,SCREEN_WIDTH,0,SCREEN_HEIGHT);
    camera->setViewMatrix(osg::Matrix::identity());
    camera->setClearMask(GL_DEPTH_BUFFER_BIT);

    camera->addChild(MessageLogger::getGroup());

	camera->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
	root->addChild(camera);

	IcosahedronGraph ico(5, 1700.0);
	osg::Group* icosahedronRoot = IcosahedronDrawer::drawIcosahedron(ico);
	root->addChild(icosahedronRoot);

	// switch off lighting as we haven't assigned any normals.
	root->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	root->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON );
	root->getOrCreateStateSet()->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );

	viewer.setSceneData(root);

	viewer.setCameraManipulator(new osgGA::TrackballManipulator());
	viewer.realize();
/*
	TriangleTerrainSkin skin(5,Point(0,300,0),Point(-300,-300,0),Point(300,-300,0));
	MessageLogger::getInstance() << "Number of Y offsets: " << skin.getYOffsetCount() << "\n";
	for(unsigned int i = 0; i < skin.getYOffsetCount(); ++i) {
		MessageLogger::getInstance() << "Number of verticies at " << skin.getVertex(0,i).y() << ": " << skin.getXOffsetCount(i) << "\n";
	}
*/
	while (!viewer.done()) {
		viewer.frame();
	}

	return 0;
}
