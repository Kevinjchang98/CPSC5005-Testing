#define CATCH_CONFIG_MAIN

#include <sstream>
#include <string>

#define private public
#include "BST.h"
#undef private

#include "catch.hpp"

// NOTE: Root node needs to be named root

template <class T>
int getSizeHelper(const T* root) {
    // NOTE: Requires left and right pointers to be named left and right
    if (!root)
        return 0;
    else
        return 1 + getSizeHelper(root->left) + getSizeHelper(root->right);
}

template <class T>
bool containsHelper(const T* root, int target) {
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
TEST_CASE("Int BST") {
    BST<int> test = BST<int>();

    // Insert
    SECTION("Insert function") {
        SECTION("Insert int works correctly") {
            REQUIRE(getSizeHelper<BST<int>::Node>(test.root) == 0);

            test.insert(5);

            REQUIRE(getSizeHelper<BST<int>::Node>(test.root) == 1);

            test.insert(2);

            REQUIRE(getSizeHelper<BST<int>::Node>(test.root) == 2);

            test.insert(20);

            REQUIRE(getSizeHelper<BST<int>::Node>(test.root) == 3);
        }
    }

    // Contains
    SECTION("Contains function") {
        SECTION("Contains root") {
            test.insert(5);

            REQUIRE(test.contains(5) == true);

            test.insert(0);

            REQUIRE(test.contains(5) == true);

            test.insert(10);

            REQUIRE(test.contains(5) == true);
        }

        SECTION("Contains leaves") {
            test.insert(5);

            REQUIRE(test.contains(5) == true);

            test.insert(0);

            REQUIRE(test.contains(0) == true);

            test.insert(10);

            REQUIRE(test.contains(10) == true);
        }

        SECTION("Contains interior nodes") {
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
    }

    // Remove
    // NOTE: Checks for existence of Node in tree as well as uses student's
    // .contains() method
    SECTION("Remove function") {
        SECTION("Removes leaf node") {
            test.insert(5);
            test.insert(1);
            test.insert(8);

            REQUIRE(containsHelper<BST<int>::Node>(test.root, 1) == true);
            REQUIRE(test.contains(1) == true);

            test.remove(1);

            REQUIRE(containsHelper<BST<int>::Node>(test.root, 1) == false);
            REQUIRE(test.contains(1) == false);

            test.remove(8);

            REQUIRE(containsHelper<BST<int>::Node>(test.root, 8) == false);
            REQUIRE(test.contains(8) == false);
        }

        SECTION("Remove root in empty tree") {
            test.insert(5);

            test.remove(5);

            REQUIRE(test.contains(5) == false);
            REQUIRE(test.size() == 0);
            REQUIRE(test.root == nullptr);
        }

        SECTION("Remove root in filled tree") {
            test.insert(5);
            test.insert(1);
            test.insert(8);

            test.remove(5);

            REQUIRE(test.contains(5) == false);
            REQUIRE(test.size() == 2);
            REQUIRE(test.root != nullptr);
        }

        SECTION("Remove interior node") {
            test.insert(5);
            test.insert(1);
            test.insert(2);
            test.insert(0);
            test.insert(8);

            REQUIRE(test.contains(1) == true);

            test.remove(1);

            REQUIRE(test.contains(1) == false);
            REQUIRE(test.size() == 4);
            REQUIRE(test.root != nullptr);
        }
    }

    // Empty
    SECTION("Is empty function") {
        SECTION("Empty on new tree") { REQUIRE(test.empty() == true); }

        SECTION("Empty on old tree") {
            test.insert(5);
            test.insert(3);
            test.insert(7);

            test.remove(5);
            test.remove(3);
            test.remove(7);

            REQUIRE(test.empty() == true);
            REQUIRE(test.root == nullptr);
        }

        SECTION("Empty on filled tree") {
            test.insert(5);
            test.insert(3);
            test.insert(7);

            REQUIRE(test.empty() == false);
            REQUIRE(test.root != nullptr);

            test.remove(5);
            test.remove(7);

            REQUIRE(test.empty() == false);
            REQUIRE(test.root != nullptr);
        }
    }

    // Size
    SECTION("Size function") {
        SECTION("Get size method works correctly on empty tree") {
            REQUIRE(test.size() == 0);
        }

        SECTION("Get size method works correctly on tree after insertions") {
            int oldSize = test.size();

            test.insert(5);
            test.insert(2);
            test.insert(20);

            int newSize = test.size();

            REQUIRE(newSize - oldSize == 3);
            REQUIRE(newSize == 3);
        }
    }

    // Leaf count
    SECTION("Leaf count function") {
        SECTION("Get leaf count on empty tree") {
            REQUIRE(test.getLeafCount() == 0);
        }

        SECTION("Get leaf count on root-only tree") {
            test.insert(5);

            REQUIRE(test.getLeafCount() == 1);
        }

        SECTION("Get leaf count on filled tree") {
            test.insert(5);
            test.insert(3);
            test.insert(7);

            REQUIRE(test.getLeafCount() == 2);
        }
    }

    // Height function
    SECTION("Get height function") {
        SECTION("Get height on empty tree") { REQUIRE(test.getHeight() == 0); }

        SECTION("Get height on tree with one node") {
            test.insert(5);

            REQUIRE(test.getHeight() == 1);
        }

        SECTION("Get height on tree filled to left") {
            test.insert(5);
            test.insert(4);
            test.insert(3);
            test.insert(2);

            REQUIRE(test.getHeight() == 4);
        }

        SECTION("Get height on tree filled to right") {
            test.insert(2);
            test.insert(3);
            test.insert(4);
            test.insert(5);

            REQUIRE(test.getHeight() == 4);
        }

        SECTION("Get height on tree filled evenly") {
            test.insert(5);
            test.insert(6);
            test.insert(4);
            test.insert(3);
            test.insert(7);

            REQUIRE(test.getHeight() == 3);
        }
    }
}
