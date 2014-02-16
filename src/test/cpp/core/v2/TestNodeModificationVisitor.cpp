#include "core/v2/NodeModificationVisitor.h"

#include "core/v2/Node.h"
#include "core/v2/ImmutableNode.h"
#include "core/v2/NodeVisitorSession.h"

#include "gtest/gtest.h"

class NodeModificationVisitorTest : public ::testing::Test {
public:
	Node *one;
	Node *two;
protected:
	NodeModificationVisitorTest() {
	}

	virtual ~NodeModificationVisitorTest() {
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

class TestModificationVisitor : public SimpleNodeVisitor {
public:
	int nodesVisited;
	TestModificationVisitor():nodesVisited(0){}
	virtual void visit(ImmutableNode* node) {
		nodesVisited += 1;
		if(nodesVisited == 1) {
			setNextNode(node->getSiblingNodes()[0]);
		}
	}
};

TEST_F(NodeModificationVisitorTest, TestVisiting) {
	TestModificationVisitor *testVisitor = new TestModificationVisitor();
	NodeVisitorSession session(1);
	session.traverse(one, testVisitor, testVisitor);
	ASSERT_EQ(2, testVisitor->nodesVisited);
}

TEST_F(NodeModificationVisitorTest, TestModificationVisiting) {
	TestModificationVisitor *testVisitor = new TestModificationVisitor();
	NodeVisitorSession session(1);
	session.traverse(one, testVisitor, testVisitor);
	ASSERT_EQ(2, testVisitor->nodesVisited);
}
