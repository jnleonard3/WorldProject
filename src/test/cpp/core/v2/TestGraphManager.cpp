#include "core/v2/GraphManager.h"
#include "core/v2/Node.h"

#include "gtest/gtest.h"
#include <iostream>

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

TEST_F(GraphManagerTest, TestGraphManager) {
}
