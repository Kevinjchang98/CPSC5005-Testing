#define CATCH_CONFIG_MAIN

#include <sstream>
#include <string>

#define private public
#include "BST.h"
#undef private

#include "catch.hpp"

template <class T>
int getSizeHelper(T* root) {
    // NOTE: Requires root node to be named root
    // NOTE: Requires left and right pointers to be named left and right
    if (!root)
        return 0;
    else
        return 1 + getSizeHelper(root->left) + getSizeHelper(root->right);
}

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
