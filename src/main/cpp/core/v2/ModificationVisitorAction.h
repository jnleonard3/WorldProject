/**
 * \file ModificationVisitorAction.h
 * \author Jon Leonard
 * \date 2014/02/10
 * \copyright The BSD 2-Clause License
 */
#ifndef MODIFICATION_VISITOR_ACTION_H_
#define MODIFICATION_VISITOR_ACTION_H_

/**
 * \class ModificationVisitorAction
 */
class ModificationVisitorAction {
public:
	ModificationVisitorAction(){};
	virtual ~ModificationVisitorAction(){};
	virtual Node* apply(Node* node) = 0;
};

class VisitorMoveAction : public ModificationVisitorAction {
public:
	VisitorMoveAction(Node *moveTo):moveTo(moveTo){};
	virtual Node* apply(Node* node);
private:
	Node* moveTo;
};

class VisitorAddChildAction : public ModificationVisitorAction {
public:
	VisitorAddChildAction(unsigned int index, Node* childAdded):index(index),childAdded(childAdded){};
	virtual Node* apply(Node* node);
private:
	unsigned int index;
	Node* childAdded;
};

class VisitorRemoveChildAction : public ModificationVisitorAction {
public:
	VisitorRemoveChildAction(unsigned int index):index(index){};
	virtual Node* apply(Node* node);
private:
	unsigned int index;
};

class VisitorModifyAction : public ModificationVisitorAction {
public:
	VisitorModifyAction(Node* updatedNode):updatedNode(updatedNode){};
	virtual Node* apply(Node* node);
private:
	Node* updatedNode;
};

#endif