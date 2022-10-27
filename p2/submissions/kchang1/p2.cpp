#include <fstream>
#include <iostream>

#include "BST.h"

using namespace std;

// Prints out some basic statistics about a binary tre
template <typename T>
void printStats(BST<T>& tree) {
    cout << "# of nodes: " << tree.size() << endl;
    cout << "# of leaves: " << tree.getLeafCount() << endl;
    cout << "BST height: " << tree.getHeight() << endl;
    cout << "BST empty? " << (tree.empty() ? "true" : "false") << endl << endl;
}

// Prints out various DFS traversals of a binary tree
template <typename T>
void printTraversals(BST<T>& tree) {
    cout << "pre-order: " << tree.getPreOrderTraversal() << endl;
    cout << "in-order: " << tree.getInOrderTraversal() << endl;
    cout << "post-order: " << tree.getPostOrderTraversal() << endl << endl;
}

// Runs some test cases and prints out their results for a binary tree
template <typename T>
void printFullStats(BST<T>& tree) {
    // Calls helper method to print results of various traversals
    cout << "-- TEST TRAVERSALS" << endl;
    printTraversals(tree);

    // Hard codes some test values
    stringstream ss(
        "20 40 10 70 99 -2 59 43 20 40 10 70 99 -2 59 43 20 40 10 70 99 -2 59 "
        "43");

    // Gets results of level and ancestor calls for every value in the tree
    cout << "-- TEST LEVEL AND ANCESTORS" << endl;
    stringstream ss2(tree.getPreOrderTraversal());
    int nextVal;
    while (ss2 >> nextVal) {
        cout << "level(" << nextVal << "): " << tree.getLevel(nextVal)
             << ", ancestors(" << nextVal << "): " << tree.getAncestors(nextVal)
             << endl;
    }
    cout << endl;

    // Tests the contains method
    cout << "-- TEST CONTAINS" << endl;
    for (int i = 0; i < 8; i++) {
        ss >> nextVal;
        cout << "contains(" << nextVal
             << "): " << (tree.contains(nextVal) ? "true" : "false") << endl;
    }
    cout << endl;

    // Tests out removing various values
    cout << "-- TEST REMOVE" << endl;
    cout << "Removing in this order: ";
    for (int i = 0; i < 8; i++) {
        ss >> nextVal;
        cout << nextVal << " ";
        tree.remove(nextVal);
    }
    cout << endl;
    printStats(tree);
    printTraversals(tree);

    // Tests inserting various values
    cout << "-- TEST INSERT (again)" << endl;
    cout << "Removing in this order: ";
    for (int i = 0; i < 8; i++) {
        ss >> nextVal;
        cout << nextVal << " ";
        tree.insert(nextVal);
    }
    cout << endl;

    // Print out stats and traversals again of modified tree
    printStats(tree);
    printTraversals(tree);
}

// Main test method for integer tree
void testIntTree() {
    cout << "INTEGER BINARY SEARCH TREE" << endl;

    // Creates an int BST
    cout << "-- Create BST" << endl << endl;
    BST<int> tree;
    printStats(tree);

    // Asks for file
    cout << "Enter integer file: ";
    string path;
    cin >> path;
    ifstream inFile;
    inFile.open(path);

    // Opens and ingests file
    if (inFile) {
        cout << "-- TEST INSERT" << endl;
        cout << "Inserting in this order: ";
        string line;
        while (getline(inFile, line)) {
            tree.insert(stoi(line));
            cout << line << " ";
        }
        cout << endl;
    }
    printStats(tree);
    printFullStats(tree);
}

// String methods same as for int except minor type changes
template <typename T>
void printStrStats(BST<T>& tree) {
    cout << "# of nodes: " << tree.size() << endl;
    cout << "# of leaves: " << tree.getLeafCount() << endl;
    cout << "BST height: " << tree.getHeight() << endl;
    cout << "BST empty? " << (tree.empty() ? "true" : "false") << endl << endl;
}

template <typename T>
void printStrTraversals(BST<T>& tree) {
    cout << "pre-order: " << tree.getPreOrderTraversal() << endl;
    cout << "in-order: " << tree.getInOrderTraversal() << endl;
    cout << "post-order: " << tree.getPostOrderTraversal() << endl << endl;
}

template <typename T>
void printStrFullStats(BST<T>& tree) {
    cout << "-- TEST TRAVERSALS" << endl;
    printTraversals(tree);

    cout << "-- TEST LEVEL AND ANCESTORS" << endl;
    stringstream ss(
        "gene mary bea uma yan amy ron opal gene mary bea uma yan amy ron opal "
        "gene mary bea uma yan amy ron opal ");
    stringstream ss2(tree.getPreOrderTraversal());
    string nextVal;
    while (ss2 >> nextVal) {
        cout << "level(" << nextVal << "): " << tree.getLevel(nextVal)
             << ", ancestors(" << nextVal << "): " << tree.getAncestors(nextVal)
             << endl;
    }
    cout << endl;

    cout << "-- TEST CONTAINS" << endl;
    for (int i = 0; i < 8; i++) {
        ss >> nextVal;
        cout << "contains(" << nextVal
             << "): " << (tree.contains(nextVal) ? "true" : "false") << endl;
    }
    cout << endl;

    cout << "-- TEST REMOVE" << endl;
    cout << "Removing in this order: ";
    for (int i = 0; i < 8; i++) {
        ss >> nextVal;
        cout << nextVal << " ";
        tree.remove(nextVal);
    }
    cout << endl;
    printStrStats(tree);
    printStrTraversals(tree);

    cout << "-- TEST INSERT (again)" << endl;
    cout << "Removing in this order: ";
    for (int i = 0; i < 8; i++) {
        ss >> nextVal;
        cout << nextVal << " ";
        tree.insert(nextVal);
    }
    cout << endl;
    printStrStats(tree);
    printStrTraversals(tree);
}

void testStringTree() {
    cout << "STRING BINARY SEARCH TREE" << endl;

    cout << "-- Create BST" << endl << endl;
    BST<string> tree;
    printStrStats(tree);

    cout << "Enter string file: ";
    string path;
    cin >> path;
    ifstream inFile;
    inFile.open(path);

    if (inFile) {
        cout << "-- TEST INSERT" << endl;
        cout << "Inserting in this order: ";
        string line;
        while (getline(inFile, line)) {
            tree.insert(line);
            cout << line << " ";
        }
        cout << endl;
    }
    printStrStats(tree);
    printStrFullStats(tree);
}

int main() {
    // First test the int tree then test the string tree
    testIntTree();
    testStringTree();
    cout << "Goodbye!" << endl;
    return 0;
}
