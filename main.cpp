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

int main() {
	osgViewer::Viewer viewer;
	osg::Group* root = new osg::Group();
	osg::Geode* pyramidGeode = new osg::Geode();
	osg::Geometry* icosahedronGeometry = new osg::Geometry();

	//Associate the pyramid geometry with the pyramid geode
	//   Add the pyramid geode to the root node of the scene graph.

	pyramidGeode->addDrawable(icosahedronGeometry);
	root->addChild(pyramidGeode);

	//Declare an array of vertices. Each vertex will be represented by
	//a triple -- an instances of the vec3 class. An instance of
	//osg::Vec3Array can be used to store these triples. Since
	//osg::Vec3Array is derived from the STL vector class, we can use the
	//push_back method to add array elements. Push back adds elements to
	//the end of the vector, thus the index of first element entered is
	//zero, the second entries index is 1, etc.
	//Using a right-handed coordinate system with 'z' up, array
	//elements zero..four below represent the 5 points required to create
	//a simple pyramid.

	double radius = 1700.0;
	double sideLength = (4.0/sqrt(10.0+2.0*sqrt(5.0))) * radius;
	double sideLengthHalf = sideLength/2.0;
	double goldenRatio = (1.0+sqrt(5))/2.0;
	double secondPoint = sideLengthHalf * goldenRatio;

	osg::Vec3Array* pyramidVertices = new osg::Vec3Array;
	pyramidVertices->push_back(osg::Vec3(0, sideLengthHalf, secondPoint));
	pyramidVertices->push_back(osg::Vec3(0, -sideLengthHalf, secondPoint));
	pyramidVertices->push_back(osg::Vec3(0, sideLengthHalf, -secondPoint));
	pyramidVertices->push_back(osg::Vec3(0, -sideLengthHalf, -secondPoint));
	pyramidVertices->push_back(osg::Vec3(sideLengthHalf, secondPoint, 0));
	pyramidVertices->push_back(osg::Vec3(-sideLengthHalf, secondPoint, 0));
	pyramidVertices->push_back(osg::Vec3(sideLengthHalf, -secondPoint, 0));
	pyramidVertices->push_back(osg::Vec3(-sideLengthHalf, -secondPoint, 0));
	pyramidVertices->push_back(osg::Vec3(secondPoint, 0, sideLengthHalf));
	pyramidVertices->push_back(osg::Vec3(secondPoint, 0, -sideLengthHalf));
	pyramidVertices->push_back(osg::Vec3(-secondPoint, 0, sideLengthHalf));
	pyramidVertices->push_back(osg::Vec3(-secondPoint, 0, -sideLengthHalf));

	icosahedronGeometry->setVertexArray(pyramidVertices);

	// Triangles

	osg::DrawElementsUInt* tri = new osg::DrawElementsUInt(
			osg::PrimitiveSet::TRIANGLES, 0);
	tri->push_back(0);
	tri->push_back(1);
	tri->push_back(8);
	icosahedronGeometry->addPrimitiveSet(tri);

	tri = new osg::DrawElementsUInt(
			osg::PrimitiveSet::TRIANGLES, 0);
	tri->push_back(0);
	tri->push_back(1);
	tri->push_back(10);
	icosahedronGeometry->addPrimitiveSet(tri);

	tri = new osg::DrawElementsUInt(
			osg::PrimitiveSet::TRIANGLES, 0);
	tri->push_back(2);
	tri->push_back(3);
	tri->push_back(9);
	icosahedronGeometry->addPrimitiveSet(tri);

	tri = new osg::DrawElementsUInt(
			osg::PrimitiveSet::TRIANGLES, 0);
	tri->push_back(2);
	tri->push_back(3);
	tri->push_back(11);
	icosahedronGeometry->addPrimitiveSet(tri);

	tri = new osg::DrawElementsUInt(
			osg::PrimitiveSet::TRIANGLES, 0);
	tri->push_back(4);
	tri->push_back(5);
	tri->push_back(0);
	icosahedronGeometry->addPrimitiveSet(tri);

	tri = new osg::DrawElementsUInt(
			osg::PrimitiveSet::TRIANGLES, 0);
	tri->push_back(4);
	tri->push_back(5);
	tri->push_back(2);
	icosahedronGeometry->addPrimitiveSet(tri);

	tri = new osg::DrawElementsUInt(
			osg::PrimitiveSet::TRIANGLES, 0);
	tri->push_back(6);
	tri->push_back(7);
	tri->push_back(1);
	icosahedronGeometry->addPrimitiveSet(tri);

	tri = new osg::DrawElementsUInt(
			osg::PrimitiveSet::TRIANGLES, 0);
	tri->push_back(6);
	tri->push_back(7);
	tri->push_back(3);
	icosahedronGeometry->addPrimitiveSet(tri);

	tri = new osg::DrawElementsUInt(
			osg::PrimitiveSet::TRIANGLES, 0);
	tri->push_back(8);
	tri->push_back(9);
	tri->push_back(4);
	icosahedronGeometry->addPrimitiveSet(tri);

	tri = new osg::DrawElementsUInt(
			osg::PrimitiveSet::TRIANGLES, 0);
	tri->push_back(8);
	tri->push_back(9);
	tri->push_back(6);
	icosahedronGeometry->addPrimitiveSet(tri);

	tri = new osg::DrawElementsUInt(
			osg::PrimitiveSet::TRIANGLES, 0);
	tri->push_back(10);
	tri->push_back(11);
	tri->push_back(5);
	icosahedronGeometry->addPrimitiveSet(tri);

	tri = new osg::DrawElementsUInt(
			osg::PrimitiveSet::TRIANGLES, 0);
	tri->push_back(10);
	tri->push_back(11);
	tri->push_back(7);
	icosahedronGeometry->addPrimitiveSet(tri);

	// Middle Pieces

	tri = new osg::DrawElementsUInt(
			osg::PrimitiveSet::TRIANGLES, 0);
	tri->push_back(0);
	tri->push_back(4);
	tri->push_back(8);
	icosahedronGeometry->addPrimitiveSet(tri);

	tri = new osg::DrawElementsUInt(
			osg::PrimitiveSet::TRIANGLES, 0);
	tri->push_back(0);
	tri->push_back(5);
	tri->push_back(10);
	icosahedronGeometry->addPrimitiveSet(tri);

	tri = new osg::DrawElementsUInt(
			osg::PrimitiveSet::TRIANGLES, 0);
	tri->push_back(1);
	tri->push_back(6);
	tri->push_back(8);
	icosahedronGeometry->addPrimitiveSet(tri);

	tri = new osg::DrawElementsUInt(
			osg::PrimitiveSet::TRIANGLES, 0);
	tri->push_back(1);
	tri->push_back(7);
	tri->push_back(10);
	icosahedronGeometry->addPrimitiveSet(tri);

	tri = new osg::DrawElementsUInt(
			osg::PrimitiveSet::TRIANGLES, 0);
	tri->push_back(2);
	tri->push_back(4);
	tri->push_back(9);
	icosahedronGeometry->addPrimitiveSet(tri);

	tri = new osg::DrawElementsUInt(
			osg::PrimitiveSet::TRIANGLES, 0);
	tri->push_back(2);
	tri->push_back(5);
	tri->push_back(11);
	icosahedronGeometry->addPrimitiveSet(tri);

	tri = new osg::DrawElementsUInt(
			osg::PrimitiveSet::TRIANGLES, 0);
	tri->push_back(3);
	tri->push_back(7);
	tri->push_back(11);
	icosahedronGeometry->addPrimitiveSet(tri);

	tri = new osg::DrawElementsUInt(
			osg::PrimitiveSet::TRIANGLES, 0);
	tri->push_back(3);
	tri->push_back(6);
	tri->push_back(9);
	icosahedronGeometry->addPrimitiveSet(tri);

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

    //The next step is to associate the array of colors with the geometry,
    //assign the color indices created above to the geometry and set the
    //binding mode to _PER_VERTEX.

    icosahedronGeometry->setColorArray(colors);
    icosahedronGeometry->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE);

	// switch off lighting as we haven't assigned any normals.
	root->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

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
