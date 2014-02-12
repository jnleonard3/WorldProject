/**
 * \file ImmutableNode.h
 * \author Jon Leonard
 * \date 2014/02/10
 * \copyright The BSD 2-Clause License
 */
#ifndef IMMUTABLE_NODE_H_
#define IMMUTABLE_NODE_H_

/**
 * \class ImmutableNode
 */
class ImmutableNode {
public:
	ImmutableNode(unsigned long id):id(id){};
private:
	unsigned long id;
};

/**
 * \class ImmutableChildNode
 */
class ImmutableChildNode : public ImmutableNode {
public:
	ImmutableChildNode(unsigned long id):ImmutableNode(id){};
private:
	unsigned long parentNodes[2];
	unsigned long siblingNodes[4];
	unsigned long childNodes[6];
};

/**
 * \class ImmutableRootNode
 */
class ImmutableRootNode : public ImmutableNode {
public:
	ImmutableRootNode(unsigned long id):ImmutableNode(id){};
private:
	unsigned long siblingNodes[5];
	unsigned long childNodes[5];
};

#endif