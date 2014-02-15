/**
 * \file NodeVisitorModificationSession.h
 * \author Jon Leonard
 * \date 2014/02/10
 * \copyright The BSD 2-Clause License
 */
#ifndef NODE_VISITOR_MODIFICATION_SESSION_H_
#define NODE_VISITOR_MODIFICATION_SESSION_H_

/**
 * \class NodeVisitorModificationSession
 */
class NodeVisitorModificationSession : public AbstractSimpleVisitorSession {
public:
	NodeVisitorModificationSession(Node *startNode, NodeModificationVisitor *visitor, unsigned long maxRevision):AbstractSimpleVisitorSession(startNode, maxRevision),visitor(visitor){};
	virtual void visitCurrentNode(ImmutableNode node);
	void addChildNode(int index);
	void removeChildNode(int index);	
private:
	boost::ptr_list<ModificationVisitorAction> actions;
	NodeModificationVisitor *visitor;
};

#endif
