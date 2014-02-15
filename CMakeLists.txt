cmake_minimum_required (VERSION 2.6)
project (world_project)

set(SRC_PREFIX src/main/cpp)
set(TEST_PREFIX src/test/cpp)

set(SOURCE_FILES
	${SRC_PREFIX}/core/v2/NodeVisitorSession.cpp
	${SRC_PREFIX}/core/v2/NodeConnectivityData.cpp
	${SRC_PREFIX}/core/v2/ImmutableNode.cpp
	${SRC_PREFIX}/core/v2/Node.cpp
	${SRC_PREFIX}/core/v2/GraphManager.cpp
)

set(HEADER_FILES
	${SRC_PREFIX}/core/v2/ImmutableNode.h
	${SRC_PREFIX}/core/v2/ModificationVisitorAction.h
	${SRC_PREFIX}/core/v2/Node.h
	${SRC_PREFIX}/core/v2/NodeConnectivityData.h
	${SRC_PREFIX}/core/v2/NodeData.h
	${SRC_PREFIX}/core/v2/NodeModificationSession.h
	${SRC_PREFIX}/core/v2/NodeModificationVisitor.h
	${SRC_PREFIX}/core/v2/NodeVisitor.h
	${SRC_PREFIX}/core/v2/NodeVisitorSession.h
)

set(UNIT_TEST_FILES
	${TEST_PREFIX}/core/v2/TestGraphManager.cpp
	${TEST_PREFIX}/core/v2/TestImmutableNodeFactory.cpp
	${TEST_PREFIX}/core/v2/TestNodeVisitorSession.cpp
)

set(CORE_DEP_LIBS
)

set(CORE_DEP_INCLUDES
	../WorldProject_Deps/boost_1_55_0
)

include_directories("${CORE_DEP_INCLUDES}")
add_library(world_project STATIC ${SOURCE_FILES})

install(TARGETS world_project DESTINATION lib)
install(FILES ${HEADER_FILES} DESTINATION include)

set(TEST_DEP_LIBS
	world_project
	/cygdrive/d/Projects/WorldProject_Deps/gtest-1.7.0/lib/.libs/libgtest.a
	/cygdrive/d/Projects/WorldProject_Deps/gtest-1.7.0/lib/.libs/libgtest_main.a
)

set(TEST_DEP_INCLUDES
	${SRC_PREFIX}
	${CORE_DEP_INCLUDES}
	../WorldProject_Deps/gtest-1.7.0/include
)

include_directories(${TEST_DEP_INCLUDES})
add_executable(world_project_tests ${UNIT_TEST_FILES})
target_link_libraries(world_project_tests ${TEST_DEP_LIBS})

install(TARGETS world_project_tests DESTINATION bin)