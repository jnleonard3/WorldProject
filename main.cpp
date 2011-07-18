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
#include <iostream>

int main() {
	osgViewer::Viewer viewer;
	osg::Group* root = new osg::Group();

    osg::Camera* camera = new osg::Camera;
    camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    camera->setProjectionMatrixAsOrtho2D(0,1920,0,1080);
    camera->setViewMatrix(osg::Matrix::identity());
    camera->setClearMask(GL_DEPTH_BUFFER_BIT);

    camera->addChild(MessageLogger::getGroup());

	camera->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
	root->addChild(camera);

	IcosahedronGraph ico(1700.0);
	osg::Group* icosahedronRoot = IcosahedronDrawer::drawIcosahedron(ico);
	root->addChild(icosahedronRoot);

	// switch off lighting as we haven't assigned any normals.
	root->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	//root->getOrCreateStateSet()->setMode( GL_BLEND, osg::StateAttribute::ON );
	//root->getOrCreateStateSet()->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );

	viewer.setSceneData(root);
	//viewer.run();

	viewer.setCameraManipulator(new osgGA::TrackballManipulator());
	viewer.realize();

	while (!viewer.done()) {
		viewer.frame();
	}

	return 0;
}
