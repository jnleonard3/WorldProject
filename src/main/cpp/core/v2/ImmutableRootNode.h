/**
 * \file ImmutableRootNode.h
 * \author Jon Leonard
 * \date 2014/02/10
 * \copyright The BSD 2-Clause License
 */
#ifndef IMMUTABLE_ROOT_NODE_H_
#define IMMUTABLE_ROOT_NODE_H_

/**
 * \class ImmutableRootNode
 */
class ImmutableRootNode : public ImmutableNode {
public:
	ImmutableRootNode(){};
private:
	unsigned long[] siblingNodes = unsigned long[5];
	unsigned long[] childNodes = unsigned long[5];
};

#endif