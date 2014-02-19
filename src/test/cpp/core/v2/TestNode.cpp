#include "core/v2/Node.h"
#include "core/v2/NodeConnectivityData.h"
#include "core/v2/NodeAccessor.h"

#include "gtest/gtest.h"

class NodeTest : public ::testing::Test {
public:
	Node *one;
	Node *two;
protected:
	NodeTest() {
	}

	virtual ~NodeTest() {
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

TEST_F(NodeTest, TestConnectChildNode) {
	Node::CreateChildNodeResult* result = Node::createChildNode(3,new NodeAccessor(1),one,two);
	ASSERT_EQ(3, result->cNode->getId());
	ASSERT_EQ(one, result->cc->getParentNodes()[0]);
	ASSERT_EQ(two, result->cc->getParentNodes()[1]);
	ASSERT_EQ(result->cNode, result->p1c->getChildNodes()[0]);
	ASSERT_EQ(result->cNode, result->p2c->getChildNodes()[0]);
}

TEST_F(NodeTest, TestChildNodeApply) {
	Node::CreateChildNodeResult* result = Node::createChildNode(3,new NodeAccessor(1),one,two);
	result->apply(2, new NodeAccessor(2));
	NodeConnectivityData *pc1 = one->getHeadConnectivity();
	NodeConnectivityData *pc2 = two->getHeadConnectivity();
	ASSERT_EQ(2, pc1->getRevision());
	ASSERT_EQ(2, pc2->getRevision());
	Node *p1c = pc1->getChildNodes()[0];
	Node *p2c = pc2->getChildNodes()[0];
	ASSERT_EQ(3, p1c->getId());
	ASSERT_EQ(3, p2c->getId());
	ASSERT_EQ(p1c, p2c);
	NodeConnectivityData *cc = p1c->getHeadConnectivity();
	ASSERT_EQ(2, cc->getRevision());
	ASSERT_EQ(1, cc->getParentNodes()[0]->getId());
	ASSERT_EQ(2, cc->getParentNodes()[1]->getId());
}

TEST_F(NodeTest, TestConnectChildNodeTwice) {
	Node::CreateChildNodeResult* result = Node::createChildNode(3,new NodeAccessor(1),one,two);
	result->apply(2, new NodeAccessor(2));
	Node *three = one->getHeadConnectivity()->getChildNodes()[0];
	Node::CreateChildNodeResult* secondResult = Node::createChildNode(4,new NodeAccessor(2),one,three);
	ASSERT_EQ(4, secondResult->cNode->getId());
	ASSERT_EQ(one, secondResult->cc->getParentNodes()[0]);
	ASSERT_EQ(three, secondResult->cc->getParentNodes()[1]);
	ASSERT_EQ(secondResult->cNode, secondResult->p2c->getChildNodes()[0]);
}

TEST_F(NodeTest, TestChildNodeApplyTwice) {
	Node::CreateChildNodeResult* result = Node::createChildNode(3, new NodeAccessor(1),one,two);
	result->apply(2, new NodeAccessor(2));
	Node *three = one->getHeadConnectivity()->getChildNodes()[0];
	Node::CreateChildNodeResult* secondResult = Node::createChildNode(4, new NodeAccessor(2),one,three);
	secondResult->apply(2, new NodeAccessor(2));
}


