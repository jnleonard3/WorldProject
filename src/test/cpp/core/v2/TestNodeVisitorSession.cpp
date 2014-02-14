#include "core/v2/NodeVisitorSession.h"
#include "core/v2/Node.h"
#include "core/v2/NodeVisitor.h"

#include "gtest/gtest.h"
#include <iostream>

class NodeVisitorSessionTest : public ::testing::Test {
public:
	Node *one;
	Node *two;
protected:
	NodeVisitorSessionTest() {
	}

	virtual ~NodeVisitorSessionTest() {
	}

	virtual void SetUp() {
		one = new Node(1);
		two = new Node(2);
		
		NodeConnectivityRootData *oneConnectivity = new NodeConnectivityRootData(1);
		oneConnectivity->getSiblingNodes()[0] = two;
		one->addConnectivity(oneConnectivity);
		
		NodeConnectivityRootData *twoConnectivity = new NodeConnectivityRootData(1);
		twoConnectivity->getSiblingNodes()[0] = one;
		two->addConnectivity(twoConnectivity);
	}

	virtual void TearDown() {
	}
};

class TestVisitor : public NodeVisitor {
public:
	int nodesVisited;
	TestVisitor():nodesVisited(0){}
	virtual void visit(NodeVisitorSession *session, ImmutableNode* node) {
		nodesVisited += 1;
		if(nodesVisited == 1) {
			session->setNextNode(node->getSiblingNodes()[0]);
		}
	}
};

TEST_F(NodeVisitorSessionTest, TestVisiting) {
	TestVisitor *testVisitor = new TestVisitor();
	NodeVisitorSession session(one, testVisitor, 1);
	session.traverse();
	ASSERT_EQ(2, testVisitor->nodesVisited);
}
