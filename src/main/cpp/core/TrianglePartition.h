/*
 * TrianglePartition.h
 *
 *  Created on: Jul 29, 2011
 *      Author: Jon
 */

#ifndef TRIANGLEPARTITION_H_
#define TRIANGLEPARTITION_H_

struct TrianglePartition {
	const unsigned int nodeHeight;
	TrianglePartition *topNode, *leftNode, *middleNode, *rightNode;
};


#endif /* TRIANGLEPARTITION_H_ */
