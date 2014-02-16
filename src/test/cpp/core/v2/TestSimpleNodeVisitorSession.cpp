#include "core/v2/SimpleNodeVisitor.h"

#include "core/v2/Node.h"
#include "core/v2/ImmutableNode.h"
#include "core/v2/NodeVisitorSession.h"

#include "gtest/gtest.h"
#include <iostream>

class SimpleNodeVisitorSessionTest : public ::testing::Test {
public:
	Node *one;
	Node *two;
protected:
	SimpleNodeVisitorSessionTest() {
	}

	virtual ~SimpleNodeVisitorSessionTest() {
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

class TestVisitor : public SimpleNodeVisitor {
public:
	int nodesVisited;
	TestVisitor():nodesVisited(0){}
	virtual void visit(ImmutableNode* node) {
		nodesVisited += 1;
		if(nodesVisited == 1) {
			setNextNode(node->getSiblingNodes()[0]);
		}
	}
};

TEST_F(SimpleNodeVisitorSessionTest, TestVisiting) {
	TestVisitor *testVisitor = new TestVisitor();
	NodeVisitorSession session(1);
	session.traverse(one, testVisitor, testVisitor);
	ASSERT_EQ(2, testVisitor->nodesVisited);
}
