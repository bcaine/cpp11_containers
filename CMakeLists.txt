cmake_minimum_required(VERSION 3.8)
project(cpp11_containers CXX)
include_directories(containers)

set(CMAKE_CXX_STANDARD 11)
option(CONTAINERS_BUILD_TESTS "Whether to build the tests" ON)

file(GLOB tree_sources containers/trees/*.h)
add_library(trees ${tree_sources})
set_target_properties(trees PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(trees PUBLIC containers/trees)


if (CONTAINERS_BUILD_TESTS)
    find_package(Boost COMPONENTS unit_test_framework)

    if (Boost_FOUND)
        add_executable(binary_tree_test tests/BinaryTreeTests.cpp)
        target_link_libraries(binary_tree_test ${Boost_LIBRARIES} trees)
        add_test(NAME binary_tree_test WORKING_DIRECTORY ${CMAKE_BINARY_DIR} COMMAND binary_tree_test)
    endif()
endif()