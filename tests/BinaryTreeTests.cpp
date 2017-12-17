/**
 * @file BinaryTreeTests.cpp
 *
 * @breif Tests for the BinaryTree implementation
 *
 * @date 12/17/17
 * @author Ben Caine
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE BinaryTreeTests

#include <boost/test/unit_test.hpp>
#include "trees/BinaryTree.h"
#include <random>
#include <chrono>
#include <iostream>

BOOST_AUTO_TEST_CASE(create_tree) {
    trees::BinaryTree<int, int> tree;
    tree.insert(2, 222);
    tree.insert(1, 111);
    tree.insert(3, 333);

    BOOST_REQUIRE_MESSAGE(tree.getMaxDepth() == 2, "Max depth is not correct");

    int searchKey = 3;
    auto result = tree.search(searchKey);
    std::cout << "Result: " << result->key << ", " << result->value << std::endl;
    // Tree search returns a shared_ptr, which has a bool operator
    // This will evaluate to false if the shared_ptr is empty
    BOOST_REQUIRE_MESSAGE(result, "Result not found");
    BOOST_REQUIRE_MESSAGE(result->key == searchKey, "Returned key did not match query key: " + std::to_string(searchKey));
    BOOST_REQUIRE_MESSAGE(result->value == 333, "Returned data did not match '333'");
}

BOOST_AUTO_TEST_CASE(create_tree_strings) {
    trees::BinaryTree<int, std::string> tree;
    tree.insert(2, "Two");
    tree.insert(1, "One");
    tree.insert(3, "Three");

    BOOST_REQUIRE_MESSAGE(tree.getMaxDepth() == 2, "Max depth is not correct");

    int searchKey = 3;
    auto result = tree.search(searchKey);
    // Tree search returns a shared_ptr, which has a bool operator
    // This will evaluate to false if the shared_ptr is empty
    BOOST_REQUIRE_MESSAGE(result, "Result not found");
    BOOST_REQUIRE_MESSAGE(result->key == searchKey, "Returned key did not match query key: " + std::to_string(searchKey));
    BOOST_REQUIRE_MESSAGE(result->value == "Three", "Returned data did not match 'Three'");
}

BOOST_AUTO_TEST_CASE(alternating_insert_time) {
    trees::BinaryTree<int, bool> tree;

    int numNodes = 10000;

    auto startTime = std::chrono::system_clock::now();

    int leftVals = 0;
    int rightVals = 0;
    for (int ii = 0; ii < numNodes; ++ii) {
        if (ii % 2 == 0) {
            tree.insert(leftVals, true);
            leftVals -= 1;
        } else {
            tree.insert(rightVals, false);
            rightVals += 1;
        }
    }
    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = endTime - startTime;
    std::cout << "Inserting " << numNodes << " alternating value nodes took: " << duration.count() << "s" << std::endl;
}

BOOST_AUTO_TEST_CASE(unbalanced_insert_time) {
    trees::BinaryTree<int, bool> tree;

    int numNodes = 10000;
    auto startTime = std::chrono::system_clock::now();
    for (unsigned int ii = 0; ii < numNodes; ++ii) {
        tree.insert(ii, true);
    }
    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = endTime - startTime;
    std::cout << "Inserting " << numNodes << " in order took: " << duration.count() << "s" << std::endl;
}

BOOST_AUTO_TEST_CASE(random_insert_time) {
    trees::BinaryTree<int, bool> tree;

    int min = -10000;
    int max = 10000;
    int numNodes = 10000;

    // Set up a random number generator
    std::random_device randomDevice;
    std::mt19937 randomNumberGen(randomDevice());
    std::uniform_int_distribution<int> distribution(min, max);

    auto startTime = std::chrono::system_clock::now();
    for (unsigned int ii = 0; ii < numNodes; ++ii) {
        int randomNumber = distribution(randomNumberGen);
        tree.insert(randomNumber, true);
    }
    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = endTime - startTime;
    std::cout << "Inserting " << numNodes << " random nodes took: " << duration.count() << "s" << std::endl;
}

BOOST_AUTO_TEST_CASE(test_query) {
    trees::BinaryTree<int, std::string> tree;

    int min = -10000;
    int max = 10000;
    int numNodes = 1000;

    // Set up a random number generator
    std::random_device randomDevice;
    std::mt19937 randomNumberGen(randomDevice());
    std::uniform_int_distribution<int> distribution(min, max);

    // Insert random nodes
    for (unsigned int ii = 0; ii < numNodes; ++ii) {
        int randomNumber = distribution(randomNumberGen);
        tree.insert(randomNumber, "foo");
    }

    int queryKey = 500;
    std::string queryValue = "Five Hundred!";
    tree.insert(queryKey, queryValue);

    auto result = tree.search(500);
    BOOST_REQUIRE_MESSAGE(result, "Could not find queried key");
    BOOST_REQUIRE_MESSAGE(result->key == queryKey, "Returned key does not match queried key");
    BOOST_REQUIRE_MESSAGE(result->value == queryValue, "Returned value does not match inserted value for key");
}


