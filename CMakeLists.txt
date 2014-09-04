cmake_minimum_required (VERSION 2.6)
project (world_project)

set(SRC_PREFIX src/main/cpp)
set(TEST_PREFIX src/test/cpp)

set(SOURCE_FILES
	${SRC_PREFIX}/core/v2/BreadthFirstNodeVisitorController.cpp
	${SRC_PREFIX}/core/v2/GraphManager.cpp
	${SRC_PREFIX}/core/v2/ImmutableNode.cpp
	${SRC_PREFIX}/core/v2/Node.cpp
	${SRC_PREFIX}/core/v2/NodeAccessor.cpp
	${SRC_PREFIX}/core/v2/NodeConnectivityData.cpp
	${SRC_PREFIX}/core/v2/NodeModificationVisitor.cpp
	${SRC_PREFIX}/core/v2/NodeVisitorSession.cpp
	${SRC_PREFIX}/core/v2/SimpleNodeVisitor.cpp
)

set(HEADER_FILES
	${SRC_PREFIX}/core/v2/AbstractNodeVisitor.h
	${SRC_PREFIX}/core/v2/AbstractNodeVisitorController.h
	${SRC_PREFIX}/core/v2/BreadthFirstNodeVisitorController.h
	${SRC_PREFIX}/core/v2/GraphManager.h
	${SRC_PREFIX}/core/v2/ImmutableNode.h
	${SRC_PREFIX}/core/v2/ModificationVisitorAction.h
	${SRC_PREFIX}/core/v2/Node.h
	${SRC_PREFIX}/core/v2/NodeAccessor.h
	${SRC_PREFIX}/core/v2/NodeConnectivityData.h
	${SRC_PREFIX}/core/v2/NodeData.h
	${SRC_PREFIX}/core/v2/NodeModificationVisitor.h
	${SRC_PREFIX}/core/v2/NodeVisitorSession.h
	${SRC_PREFIX}/core/v2/SimpleNodeVisitor.h
)

set(UNIT_TEST_FILES
	${TEST_PREFIX}/core/v2/TestBreadthFirstNodeVisitorController.cpp
	${TEST_PREFIX}/core/v2/TestGraphManager.cpp
	${TEST_PREFIX}/core/v2/TestImmutableNodeFactory.cpp
	${TEST_PREFIX}/core/v2/TestNode.cpp
	${TEST_PREFIX}/core/v2/TestNodeConnectivityData.cpp
	${TEST_PREFIX}/core/v2/TestNodeModificationVisitor.cpp
	${TEST_PREFIX}/core/v2/TestSimpleNodeVisitorSession.cpp
)

find_package(Boost 1.45 REQUIRED)

set(CORE_DEP_LIBS
    ${Boost_LIBRARIES}
)

set(CORE_DEP_INCLUDES
	${Boost_INCLUDE_DIR}
)

include_directories("${CORE_DEP_INCLUDES}")
add_library(world_project STATIC ${SOURCE_FILES})

install(TARGETS world_project DESTINATION lib)
install(FILES ${HEADER_FILES} DESTINATION include)

project (world_project_tests)

set(TEST_DEP_LIBS
	world_project
	/usr/lib64/libgtest.so
	/usr/lib64/libgtest_main.so
)

set(TEST_DEP_INCLUDES
	${SRC_PREFIX}
	${CORE_DEP_INCLUDES}
	/usr/include/gtest/
)

include_directories(${TEST_DEP_INCLUDES})
add_executable(world_project_tests ${UNIT_TEST_FILES})
target_link_libraries(world_project_tests ${TEST_DEP_LIBS})
add_dependencies(world_project_tests world_project)

install(TARGETS world_project_tests DESTINATION bin)

project (sdl_test)

INCLUDE(FindPkgConfig)
find_package(OpenGL REQUIRED)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

set (OSG_DEP_LIBS
	${SDL2_LIBRARIES}
	${OPENGL_LIBRARIES}
	world_project
)

set(OSG_DEP_INCLUDES
	${SRC_PREFIX}
	${CORE_DEP_INCLUDES}
	${OPENGL_INCLUDE_DIRS}
	${SDL2_INCLUDE_DIRS}
)

include_directories(${OSG_DEP_INCLUDES})
add_executable(sdl_test ${SRC_PREFIX}/osg/SDLTest.cpp)
target_link_libraries(sdl_test ${OSG_DEP_LIBS})
add_dependencies(sdl_test world_project)

install(TARGETS sdl_test DESTINATION bin)
