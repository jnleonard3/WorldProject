#include "core/v2/Node.h"
#include "core/v2/NodeConnectivityData.h"

#include "gtest/gtest.h"

class NodeConnectivityDataTest : public ::testing::Test {
public:
	Node *one, *two, *three, *four, *five, *six;
protected:
	NodeConnectivityDataTest() {
	}

	virtual ~NodeConnectivityDataTest() {
	}

	virtual void SetUp() {
		one = new Node(1);
		two = new Node(2);
		three = new Node(3);
		four = new Node(4);
		five = new Node(5);
		six = new Node(6);
	}

	virtual void TearDown() {
	}
};

TEST_F(NodeConnectivityDataTest, TestMerge) {
	NodeConnectivityRootData *oneConnectivity = new NodeConnectivityRootData(1);
	oneConnectivity->getSiblingNodes()[0] = two;
	
	NodeConnectivityRootData *newOneConnectivity = oneConnectivity->copy();
	newOneConnectivity->getSiblingNodes()[1] = three;
	
	oneConnectivity->merge(newOneConnectivity);

	ASSERT_EQ(1, oneConnectivity->getRevision());
	ASSERT_EQ(2, oneConnectivity->getSiblingNodes()[0]->getId());
	ASSERT_EQ(3, oneConnectivity->getSiblingNodes()[1]->getId());
}

TEST_F(NodeConnectivityDataTest, TestChildEffectiveSibling) {
	NodeConnectivityChildData *connect = new NodeConnectivityChildData(1);
	connect->getParentNodes()[0] = two;
	connect->getParentNodes()[1] = three;
	connect->getSiblingNodes()[0] = four;
	connect->getSiblingNodes()[1] = five;
	connect->getSiblingNodes()[2] = six;
	ASSERT_EQ(2, connect->getEffectiveSiblingNode(0)->getId());
	ASSERT_EQ(4, connect->getEffectiveSiblingNode(1)->getId());
	ASSERT_EQ(5, connect->getEffectiveSiblingNode(2)->getId());
	ASSERT_EQ(3, connect->getEffectiveSiblingNode(3)->getId());
	ASSERT_EQ(6, connect->getEffectiveSiblingNode(4)->getId());
	ASSERT_EQ(2, connect->getEffectiveSiblingNode(6)->getId());
}

