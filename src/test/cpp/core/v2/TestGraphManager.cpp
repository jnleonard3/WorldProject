#include "core/v2/GraphManager.h"

#include "core/v2/Node.h"
#include "core/v2/ImmutableNode.h"
#include "core/v2/BreadthFirstNodeVisitorController.h"
#include "core/v2/AbstractNodeVisitor.h"

#include "gtest/gtest.h"

class GraphManagerTest : public ::testing::Test {
public:
	GraphManager *graphManager;
protected:
	GraphManagerTest() {
		graphManager = new GraphManager();
	}

	virtual ~GraphManagerTest() {
	}

	virtual void SetUp() {
	}

	virtual void TearDown() {
	}
};

class TestManagerVisitor : public AbstractNodeVisitor {
public:
	int nodesVisited;
	TestManagerVisitor():nodesVisited(0){}
	virtual void visit(ImmutableNode* node) {
		nodesVisited += 1;
	}
};

TEST_F(GraphManagerTest, TestGraphManager) {
	TestManagerVisitor *testVisitor = new TestManagerVisitor();
	graphManager->traverse(new BreadthFirstNodeVisitorController(), testVisitor);
	ASSERT_EQ(12, testVisitor->nodesVisited);
}
