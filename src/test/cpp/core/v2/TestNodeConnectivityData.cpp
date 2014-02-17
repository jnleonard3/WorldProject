#include "core/v2/Node.h"
#include "core/v2/NodeConnectivityData.h"

#include "gtest/gtest.h"

class NodeConnectivityDataTest : public ::testing::Test {
public:
	Node *one, *two, *three;
protected:
	NodeConnectivityDataTest() {
	}

	virtual ~NodeConnectivityDataTest() {
	}

	virtual void SetUp() {
		one = new Node(1);
		two = new Node(2);
		three = new Node(3);
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

