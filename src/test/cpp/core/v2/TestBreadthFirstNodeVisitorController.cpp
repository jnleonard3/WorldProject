#include "core/v2/BreadthFirstNodeVisitorController.h"

#include "core/v2/Node.h"
#include "core/v2/AbstractNodeVisitor.h"
#include "core/v2/BreadthFirstNodeVisitorController.h"
#include "core/v2/NodeVisitorSession.h"

#include "gtest/gtest.h"

class BreadthFirstNodeVisitorControllerTest : public ::testing::Test {
public:
	Node *one;
	Node *two;
protected:
	BreadthFirstNodeVisitorControllerTest() {
	}

	virtual ~BreadthFirstNodeVisitorControllerTest() {
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

class TestBreadthVisitor : public AbstractNodeVisitor {
public:
	int nodesVisited;
	TestBreadthVisitor():nodesVisited(0){}
	virtual void visit(ImmutableNode* node) {
		nodesVisited += 1;
	}
};

TEST_F(BreadthFirstNodeVisitorControllerTest, TestBreadthFirstNodeVisitorController) {
	TestBreadthVisitor *testVisitor = new TestBreadthVisitor();
	NodeVisitorSession session(1);
	session.traverse(one, new BreadthFirstNodeVisitorController(), testVisitor);
	ASSERT_EQ(2, testVisitor->nodesVisited);
}
