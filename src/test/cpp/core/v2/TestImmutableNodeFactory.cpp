#include "core/v2/ImmutableNode.h"
#include "core/v2/Node.h"

#include "gtest/gtest.h"
#include <iostream>

class ImmutableNodeFactoryTest : public ::testing::Test {
public:
	Node *one;
	Node *two;
protected:
	ImmutableNodeFactoryTest() {
	}

	virtual ~ImmutableNodeFactoryTest() {
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

TEST_F(ImmutableNodeFactoryTest, TestFactory) {
	ImmutableNode* immutable = ImmutableNodeFactory::createImmutableNode(1, one);
}
