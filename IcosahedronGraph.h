/*
 * IcosahedronGraph.h
 *
 *  Created on: Jul 16, 2011
 *      Author: Jon
 */

#ifndef ICOSAHEDRONGRAPH_H_
#define ICOSAHEDRONGRAPH_H_

#include "Graph.h"

class IcosahedronGraph {
public:
	IcosahedronGraph(unsigned int levelOfDetail, double radius);
	~IcosahedronGraph();

	VertexNode& getVertexNode(unsigned int node);
	FaceNode& getFaceNode(unsigned int node);

	unsigned int getVertexNodeIndex(const VertexNode* node);

	CoordinateSystem& getCoordinateSystem() { return space; };

private:
	class IcosahedronCoordinateSpace : public CoordinateSystem {
	public:
		IcosahedronCoordinateSpace(IcosahedronGraph& grph):graph(grph){};

		virtual const char * getName() const { return name; };

		virtual bool isValid(const Point& pt) const {
			return true;
		}
	protected:
		virtual CoordinatePoint actualConvertTo(const CoordinateSystem& toSystem, const CoordinatePoint& thisPoint) const;

	private:
		static const char * name;

		IcosahedronGraph& graph;
	};

	void verifyCounterwiseTriangle(FaceNode& node) const;

	unsigned int levelOfDetail;

	IcosahedronCoordinateSpace space;

	VertexNode rootVertexNode;
	VertexNode *vertexNodes;

	FaceNode rootFaceNode;
	FaceNode *faceNodes;
};


#endif /* ICOSAHEDRONGRAPH_H_ */
