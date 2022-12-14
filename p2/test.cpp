#include <vector>
#define CATCH_CONFIG_MAIN

#include <sstream>
#include <string>

#define private public
#include "BST.h"
#undef private

#include "catch.hpp"

// NOTE: Root node needs to be named root

// template <class T>
// int getSizeHelper(const T* root) {
//     // NOTE: Requires left and right pointers to be named left and right
//     if (!root)
//         return 0;
//     else
//         return 1 + getSizeHelper(root->left) + getSizeHelper(root->right);
// }

// template <class T>
// bool containsHelper(const T* root, int target) {
//     // NOTE: Requires left and right pointers to be named left and right
//     // NOTE: Requires data to be named data
//     if (!root)
//         return false;
//     else if (root->data == target)
//         return true;
//     else
//         return containsHelper(root->left, target) ||
//                containsHelper(root->right, target);
// }

// Int
TEST_CASE("Int BST") {
    BST<int> test = BST<int>();

    // Insert
    SECTION("Insert function") {
        SECTION("Insert int works correctly") {
            // REQUIRE(getSizeHelper<BST<int>::Node>(test.root) == 0);

            test.insert(5);

            // REQUIRE(getSizeHelper<BST<int>::Node>(test.root) == 1);

            test.insert(2);

            // REQUIRE(getSizeHelper<BST<int>::Node>(test.root) == 2);

            test.insert(20);

            // REQUIRE(getSizeHelper<BST<int>::Node>(test.root) == 3);
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

            // REQUIRE(containsHelper<BST<int>::Node>(test.root, 1) == true);
            REQUIRE(test.contains(1) == true);

            test.remove(1);

            // REQUIRE(containsHelper<BST<int>::Node>(test.root, 1) == false);
            REQUIRE(test.contains(1) == false);

            test.remove(8);

            // REQUIRE(containsHelper<BST<int>::Node>(test.root, 8) == false);
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
        // Assumptions
        const int HEIGHT_OF_EMPTY_TREE = -1;

        SECTION("Get height on empty tree") {
            REQUIRE(test.getHeight() == HEIGHT_OF_EMPTY_TREE);
        }

        SECTION("Get height on tree with one node") {
            test.insert(5);

            REQUIRE(test.getHeight() == 0);
        }

        SECTION("Get height on tree filled to left") {
            test.insert(5);
            test.insert(4);
            test.insert(3);
            test.insert(2);

            REQUIRE(test.getHeight() == 3);
        }

        SECTION("Get height on tree filled to right") {
            test.insert(2);
            test.insert(3);
            test.insert(4);
            test.insert(5);

            REQUIRE(test.getHeight() == 3);
        }

        SECTION("Get height on tree filled evenly") {
            test.insert(5);
            test.insert(6);
            test.insert(4);
            test.insert(3);
            test.insert(7);

            REQUIRE(test.getHeight() == 2);
        }
    }

    // Level function
    SECTION("Get level function") {
        // Assumptions
        const int LEVEL_EMPTY_TREE = 0;
        const int HEIGHT_OF_TREE_DOESNT_CONTAIN_TARGET = 0;

        SECTION("Get level on empty tree") {
            REQUIRE(test.getLevel(0) == LEVEL_EMPTY_TREE);
        }

        SECTION("Get height on tree with one node that contains target") {
            test.insert(5);

            REQUIRE(test.getLevel(5) == 0);
        }

        SECTION(
            "Get height on tree with one node that doesn't contain target") {
            test.insert(5);

            REQUIRE(test.getLevel(1) == HEIGHT_OF_TREE_DOESNT_CONTAIN_TARGET);
        }

        SECTION("Get level on tree filled to left") {
            test.insert(5);
            test.insert(4);
            test.insert(3);
            test.insert(2);

            REQUIRE(test.getLevel(5) == 0);
            REQUIRE(test.getLevel(4) == 1);
            REQUIRE(test.getLevel(3) == 2);
            REQUIRE(test.getLevel(2) == 3);
        }

        SECTION("Get level on tree filled to right") {
            test.insert(2);
            test.insert(3);
            test.insert(4);
            test.insert(5);

            REQUIRE(test.getLevel(2) == 0);
            REQUIRE(test.getLevel(3) == 1);
            REQUIRE(test.getLevel(4) == 2);
            REQUIRE(test.getLevel(5) == 3);
        }

        SECTION("Get level on tree filled evenly") {
            test.insert(5);
            test.insert(6);
            test.insert(4);
            test.insert(3);
            test.insert(7);

            REQUIRE(test.getLevel(5) == 0);
            REQUIRE(test.getLevel(6) == 1);
            REQUIRE(test.getLevel(4) == 1);
            REQUIRE(test.getLevel(3) == 2);
            REQUIRE(test.getLevel(7) == 2);
        }
    }

    {
        // These sections give string outputs, and we can change the expected
        // delimiter here
        const std::string DELIMITER = " ";

        /**
         * @brief Helper to remove instances of DELIMITER from an input string,
         * and saves elements split by delimiter as elements of the returned
         * vector
         *
         * e.g. Input of "10 20 30" becomes vector<int> {"10", "20", "30"}
         */
        auto parseOutput = [&DELIMITER](const std::string& in) {
            std::vector<std::string> ans;

            size_t start, end = 0;

            while ((start = in.find_first_not_of(DELIMITER, end)) !=
                   std::string::npos) {
                end = in.find(DELIMITER, start);
                ans.push_back(in.substr(start, end - start));
            }

            return ans;
        };

        // Inorder traversal function
        SECTION("Inorder traversal function") {
            SECTION("Traversal of empty tree") {
                REQUIRE(test.getInOrderTraversal().size() == 0);
            }

            SECTION("Traversal of filled tree") {
                for (int i : {4, 2, 1, 3, 6, 5, 7}) test.insert(i);

                std::vector<std::string> expectedAns = {"1", "2", "3", "4",
                                                        "5", "6", "7"};

                REQUIRE(parseOutput(test.getInOrderTraversal()) == expectedAns);
            }
        }

        // Preorder traversal function
        SECTION("Preorder traversal function") {
            SECTION("Traversal of empty tree") {
                REQUIRE(test.getPreOrderTraversal().size() == 0);
            }

            SECTION("Traversal of filled tree") {
                for (int i : {4, 2, 1, 3, 6, 5, 7}) test.insert(i);

                std::vector<std::string> expectedAns = {"4", "2", "1", "3",
                                                        "6", "5", "7"};

                REQUIRE(parseOutput(test.getPreOrderTraversal()) ==
                        expectedAns);
            }
        }

        // Postorder traversal function
        SECTION("Postorder traversal function") {
            SECTION("Traversal of empty tree") {
                REQUIRE(test.getPostOrderTraversal().size() == 0);
            }

            SECTION("Traversal of filled tree") {
                for (int i : {4, 2, 1, 3, 6, 5, 7}) test.insert(i);

                std::vector<std::string> expectedAns = {"1", "3", "2", "5",
                                                        "7", "6", "4"};

                REQUIRE(parseOutput(test.getPostOrderTraversal()) ==
                        expectedAns);
            }
        }

        // Ancestors function
        SECTION("Ancestors function") {
            SECTION("Ancestors of empty tree") {
                REQUIRE(test.getAncestors(0).size() == 0);
            }

            SECTION("Ancestors of tree with only node") {
                test.insert(5);

                REQUIRE(test.getAncestors(5).size() == 0);
            }

            SECTION("Ancestors of 3-node tree") {
                test.insert(5);
                test.insert(3);
                test.insert(7);

                REQUIRE(parseOutput(test.getAncestors(3))[0] == "5");
                REQUIRE(parseOutput(test.getAncestors(7))[0] == "5");
                REQUIRE(test.getAncestors(5).size() == 0);
            }

            SECTION("Ancestors of filled tree") {
                std::vector<int> insertOrder = {4, 2, 1, 3, 6, 5, 7};

                for (int i : insertOrder) test.insert(i);

                std::vector<std::vector<std::string>> expectedAns = {
                    {},    {"4"},      {"2", "4"}, {"2", "4"},
                    {"4"}, {"6", "4"}, {"6", "4"}};

                for (int i = 0; i < insertOrder.size(); i++) {
                    REQUIRE(parseOutput(test.getAncestors(insertOrder[i])) ==
                            expectedAns[i]);
                }
            }
        }
    }
}

// String
TEST_CASE("String BST") {
    BST<std::string> test = BST<std::string>();

    // Insert
    SECTION("Insert function") {
        SECTION("Insert string works correctly") {
            // REQUIRE(getSizeHelper<BST<int>::Node>(test.root) == 0);

            test.insert("alice");

            // REQUIRE(getSizeHelper<BST<int>::Node>(test.root) == 1);

            test.insert("bob");

            // REQUIRE(getSizeHelper<BST<int>::Node>(test.root) == 2);

            test.insert("charlie");

            // REQUIRE(getSizeHelper<BST<int>::Node>(test.root) == 3);
        }
    }

    // Contains
    SECTION("Contains function") {
        SECTION("Contains root") {
            test.insert("alice");

            REQUIRE(test.contains("alice") == true);

            test.insert("bob");

            REQUIRE(test.contains("alice") == true);

            test.insert("charlie");

            REQUIRE(test.contains("alice") == true);
        }

        SECTION("Contains leaves") {
            test.insert("alice");

            REQUIRE(test.contains("alice") == true);

            test.insert("bob");

            REQUIRE(test.contains("bob") == true);

            test.insert("charlie");

            REQUIRE(test.contains("charlie") == true);
        }

        SECTION("Contains interior nodes") {
            test.insert("ddd");

            // Left of root
            test.insert("bbb");
            test.insert("aaa");

            REQUIRE(test.contains("bbb") == true);

            test.insert("eee");

            REQUIRE(test.contains("bbb") == true);

            // Right of root
            test.insert("yyy");
            test.insert("www");

            REQUIRE(test.contains("yyy") == true);

            test.insert("zzz");

            REQUIRE(test.contains("yyy") == true);
        }
    }

    // Remove
    // NOTE: Checks for existence of Node in tree as well as uses student's
    // .contains() method
    SECTION("Remove function") {
        SECTION("Removes leaf node") {
            test.insert("eee");
            test.insert("aaa");
            test.insert("fff");

            // REQUIRE(containsHelper<BST<int>::Node>(test.root, 1) == true);
            REQUIRE(test.contains("aaa") == true);

            test.remove("aaa");

            // REQUIRE(containsHelper<BST<int>::Node>(test.root, 1) == false);
            REQUIRE(test.contains("aaa") == false);

            test.remove("fff");

            // REQUIRE(containsHelper<BST<int>::Node>(test.root, 8) == false);
            REQUIRE(test.contains("fff") == false);
        }

        SECTION("Remove root in empty tree") {
            test.insert("eee");

            test.remove("eee");

            REQUIRE(test.contains("eee") == false);
            REQUIRE(test.size() == 0);
            REQUIRE(test.root == nullptr);
        }

        SECTION("Remove root in filled tree") {
            test.insert("eee");
            test.insert("aaa");
            test.insert("fff");

            test.remove("eee");

            REQUIRE(test.contains("eee") == false);
            REQUIRE(test.size() == 2);
            REQUIRE(test.root != nullptr);
        }

        SECTION("Remove interior node") {
            test.insert("5");
            test.insert("1");
            test.insert("2");
            test.insert("0");
            test.insert("8");

            REQUIRE(test.contains("1") == true);

            test.remove("1");

            REQUIRE(test.contains("1") == false);
            REQUIRE(test.size() == 4);
            REQUIRE(test.root != nullptr);
        }
    }

    // Empty
    SECTION("Is empty function") {
        SECTION("Empty on new tree") { REQUIRE(test.empty() == true); }

        SECTION("Empty on old tree") {
            test.insert("5");
            test.insert("3");
            test.insert("7");

            test.remove("5");
            test.remove("3");
            test.remove("7");

            REQUIRE(test.empty() == true);
            REQUIRE(test.root == nullptr);
        }

        SECTION("Empty on filled tree") {
            test.insert("5");
            test.insert("3");
            test.insert("7");

            REQUIRE(test.empty() == false);
            REQUIRE(test.root != nullptr);

            test.remove("5");
            test.remove("7");

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

            test.insert("5");
            test.insert("2");
            test.insert("20");

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
            test.insert("5");

            REQUIRE(test.getLeafCount() == 1);
        }

        SECTION("Get leaf count on filled tree") {
            test.insert("5");
            test.insert("3");
            test.insert("7");

            REQUIRE(test.getLeafCount() == 2);
        }
    }

    // Height function
    SECTION("Get height function") {
        // Assumptions
        const int HEIGHT_OF_EMPTY_TREE = -1;

        SECTION("Get height on empty tree") {
            REQUIRE(test.getHeight() == HEIGHT_OF_EMPTY_TREE);
        }

        SECTION("Get height on tree with one node") {
            test.insert("5");

            REQUIRE(test.getHeight() == 0);
        }

        SECTION("Get height on tree filled to left") {
            test.insert("5");
            test.insert("4");
            test.insert("3");
            test.insert("2");

            REQUIRE(test.getHeight() == 3);
        }

        SECTION("Get height on tree filled to right") {
            test.insert("2");
            test.insert("3");
            test.insert("4");
            test.insert("5");

            REQUIRE(test.getHeight() == 3);
        }

        SECTION("Get height on tree filled evenly") {
            test.insert("5");
            test.insert("6");
            test.insert("4");
            test.insert("3");
            test.insert("7");

            REQUIRE(test.getHeight() == 2);
        }
    }

    // Level function
    SECTION("Get level function") {
        // Assumptions
        const int LEVEL_EMPTY_TREE = 0;
        const int HEIGHT_OF_TREE_DOESNT_CONTAIN_TARGET = 0;

        SECTION("Get level on empty tree") {
            REQUIRE(test.getLevel("0") == LEVEL_EMPTY_TREE);
        }

        SECTION("Get height on tree with one node that contains target") {
            test.insert("5");

            REQUIRE(test.getLevel("5") == 0);
        }

        SECTION(
            "Get height on tree with one node that doesn't contain target") {
            test.insert("5");

            REQUIRE(test.getLevel("1") == HEIGHT_OF_TREE_DOESNT_CONTAIN_TARGET);
        }

        SECTION("Get level on tree filled to left") {
            test.insert("5");
            test.insert("4");
            test.insert("3");
            test.insert("2");

            REQUIRE(test.getLevel("5") == 0);
            REQUIRE(test.getLevel("4") == 1);
            REQUIRE(test.getLevel("3") == 2);
            REQUIRE(test.getLevel("2") == 3);
        }

        SECTION("Get level on tree filled to right") {
            test.insert("2");
            test.insert("3");
            test.insert("4");
            test.insert("5");

            REQUIRE(test.getLevel("2") == 0);
            REQUIRE(test.getLevel("3") == 1);
            REQUIRE(test.getLevel("4") == 2);
            REQUIRE(test.getLevel("5") == 3);
        }

        SECTION("Get level on tree filled evenly") {
            test.insert("5");
            test.insert("6");
            test.insert("4");
            test.insert("3");
            test.insert("7");

            REQUIRE(test.getLevel("5") == 0);
            REQUIRE(test.getLevel("6") == 1);
            REQUIRE(test.getLevel("4") == 1);
            REQUIRE(test.getLevel("3") == 2);
            REQUIRE(test.getLevel("7") == 2);
        }
    }

    {
        // These sections give string outputs, and we can change the expected
        // delimiter here
        const std::string DELIMITER = " ";

        /**
         * @brief Helper to remove instances of DELIMITER from an input string,
         * and saves elements split by delimiter as elements of the returned
         * vector
         *
         * e.g. Input of "10 20 30" becomes vector<int> {"10", "20", "30"}
         */
        auto parseOutput = [&DELIMITER](const std::string& in) {
            std::vector<std::string> ans;

            size_t start, end = 0;

            while ((start = in.find_first_not_of(DELIMITER, end)) !=
                   std::string::npos) {
                end = in.find(DELIMITER, start);
                ans.push_back(in.substr(start, end - start));
            }

            return ans;
        };

        // Inorder traversal function
        SECTION("Inorder traversal function") {
            SECTION("Traversal of empty tree") {
                REQUIRE(test.getInOrderTraversal().size() == 0);
            }

            SECTION("Traversal of filled tree") {
                for (std::string i :
                     {"mary", "gene", "bea", "jen", "sue", "pat", "uma"})
                    test.insert(i);

                std::vector<std::string> expectedAns = {
                    "bea", "gene", "jen", "mary", "pat", "sue", "uma"};

                REQUIRE(parseOutput(test.getInOrderTraversal()) == expectedAns);
            }
        }

        // Preorder traversal function
        SECTION("Preorder traversal function") {
            SECTION("Traversal of empty tree") {
                REQUIRE(test.getPreOrderTraversal().size() == 0);
            }

            SECTION("Traversal of filled tree") {
                for (std::string i :
                     {"mary", "gene", "bea", "jen", "sue", "pat", "uma"})
                    test.insert(i);

                std::vector<std::string> expectedAns = {
                    "mary", "gene", "bea", "jen", "sue", "pat", "uma"};

                REQUIRE(parseOutput(test.getPreOrderTraversal()) ==
                        expectedAns);
            }
        }

        // Postorder traversal function
        SECTION("Postorder traversal function") {
            SECTION("Traversal of empty tree") {
                REQUIRE(test.getPostOrderTraversal().size() == 0);
            }

            SECTION("Traversal of filled tree") {
                for (std::string i :
                     {"mary", "gene", "bea", "jen", "sue", "pat", "uma"})
                    test.insert(i);

                std::vector<std::string> expectedAns = {
                    "bea", "jen", "gene", "pat", "uma", "sue", "mary"};

                REQUIRE(parseOutput(test.getPostOrderTraversal()) ==
                        expectedAns);
            }
        }

        // Ancestors function
        SECTION("Ancestors function") {
            SECTION("Ancestors of empty tree") {
                REQUIRE(test.getAncestors("0").size() == 0);
            }

            SECTION("Ancestors of tree with only node") {
                test.insert("5");

                REQUIRE(test.getAncestors("5").size() == 0);
            }

            SECTION("Ancestors of 3-node tree") {
                test.insert("5");
                test.insert("3");
                test.insert("7");

                REQUIRE(parseOutput(test.getAncestors("3"))[0] == "5");
                REQUIRE(parseOutput(test.getAncestors("7"))[0] == "5");
                REQUIRE(test.getAncestors("5").size() == 0);
            }

            SECTION("Ancestors of filled tree") {
                std::vector<std::string> insertOrder = {
                    "mary", "gene", "bea", "jen", "sue", "pat", "uma"};

                for (std::string i : insertOrder) test.insert(i);

                std::vector<std::vector<std::string>> expectedAns = {
                    {},
                    {"mary"},
                    {"gene", "mary"},
                    {"gene", "mary"},
                    {"mary"},
                    {"sue", "mary"},
                    {"sue", "mary"}};

                for (int i = 0; i < insertOrder.size(); i++) {
                    REQUIRE(parseOutput(test.getAncestors(insertOrder[i])) ==
                            expectedAns[i]);
                }
            }
        }
    }
}
