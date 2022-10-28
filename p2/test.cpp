#define CATCH_CONFIG_MAIN

#include <sstream>
#include <string>

#define private public
#include "BST.h"
#undef private

#include "catch.hpp"

template <class T>
int getSizeHelper(const T* root) {
    // NOTE: Requires root node to be named root
    // NOTE: Requires left and right pointers to be named left and right
    if (!root)
        return 0;
    else
        return 1 + getSizeHelper(root->left) + getSizeHelper(root->right);
}

template <class T>
bool containsHelper(const T* root, int target) {
    // NOTE: Requires root node to be named root
    // NOTE: Requires left and right pointers to be named left and right
    // NOTE: Requires data to be named data
    if (!root)
        return false;
    else if (root->data == target)
        return true;
    else
        return containsHelper(root->left, target) ||
               containsHelper(root->right, target);
}

// Int
//
// Insert
TEST_CASE("Insert int works correctly") {
    BST<int> test = BST<int>();

    REQUIRE(getSizeHelper<BST<int>::Node>(test.root) == 0);

    test.insert(5);

    REQUIRE(getSizeHelper<BST<int>::Node>(test.root) == 1);

    test.insert(2);

    REQUIRE(getSizeHelper<BST<int>::Node>(test.root) == 2);

    test.insert(20);

    REQUIRE(getSizeHelper<BST<int>::Node>(test.root) == 3);
}

// Contains
TEST_CASE("Contains root") {
    BST<int> test = BST<int>();

    test.insert(5);

    REQUIRE(test.contains(5) == true);

    test.insert(0);

    REQUIRE(test.contains(5) == true);

    test.insert(10);

    REQUIRE(test.contains(5) == true);
}

TEST_CASE("Contains leaves") {
    BST<int> test = BST<int>();

    test.insert(5);

    REQUIRE(test.contains(5) == true);

    test.insert(0);

    REQUIRE(test.contains(0) == true);

    test.insert(10);

    REQUIRE(test.contains(10) == true);
}

TEST_CASE("Contains interior nodes") {
    BST<int> test = BST<int>();

    test.insert(5);

    // Left of root
    test.insert(3);
    test.insert(1);

    REQUIRE(test.contains(3) == true);

    test.insert(4);

    REQUIRE(test.contains(3) == true);

    // Right of root
    test.insert(13);
    test.insert(11);

    REQUIRE(test.contains(13) == true);

    test.insert(14);

    REQUIRE(test.contains(13) == true);
}

// Remove
// NOTE: Checks for existence of Node in tree as well as uses student's
// .contains() method
TEST_CASE("Removes leaf node") {
    BST<int> test = BST<int>();

    test.insert(5);
    test.insert(1);
    test.insert(8);

    REQUIRE(containsHelper<BST<int>::Node>(test.root, 1) == true);
    REQUIRE(test.contains(1) == true);

    test.remove(1);

    REQUIRE(containsHelper<BST<int>::Node>(test.root, 1) == false);
    REQUIRE(test.contains(1) == false);

    test.remove(8);

    REQUIRE(containsHelper<BST<int>::Node>(test.root, 8) == true);
    REQUIRE(test.contains(8) == true);
}

// Size
TEST_CASE("Get size method works correctly on empty tree") {
    // NOTE: Assumes insert works correctly
    BST<int> test = BST<int>();

    REQUIRE(test.size() == 0);
}

TEST_CASE("Get size method works correctly on tree after insertions") {
    // NOTE: Assumes insert works correctly
    BST<int> test = BST<int>();

    int oldSize = test.size();

    test.insert(5);
    test.insert(2);
    test.insert(20);

    int newSize = test.size();

    REQUIRE(newSize - oldSize == 3);
    REQUIRE(newSize == 3);
}
