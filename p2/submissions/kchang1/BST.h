//
// Created by Kevin Chang on 10/26/21.
//

#ifndef P2_BST_H
#define P2_BST_H

#include <sstream>
#include <string>

using namespace std;

template <typename T>
class BST {
   public:
    // Constructors, destructor, =op overload
    BST();
    BST(BST<T>&);
    BST<T>& operator=(BST<T>&);
    ~BST();

    void insert(T);                 // Inserts a value
    bool contains(T);               // Checks if the tree contains a value
    void remove(T);                 // Removes a value
    bool empty();                   // Checks if the tree is empty
    int size();                     // Returns the size of the tree
    int getLeafCount();             // Returns the number of leaf nodes
    int getHeight();                // Gets the height of the tree
    int getLevel(T);                // Gets the level of a particular value
    string getInOrderTraversal();   // Prints the inorder traversal results in a
                                    // space separated string
    string getPreOrderTraversal();  // Prints the preorder traversal results in
                                    // a space separated string
    string getPostOrderTraversal();  // Prints the postorder traversal results
                                     // in a space separated string
    string getAncestors(T);  // Prints the ancestors of a particular value in a
                             // space separated string

   private:
    struct Node {  // Node structure to hold data
        T data;
        Node* left;
        Node* right;
    };

    Node* root;  // Root pointer for the entire BST

    void copyTree(
        Node*&,
        Node*&);  // Helper method to copy contents from one tree to another

    void destroyTree(Node*&);      // Destroys a tree from memory
    void insert(Node*&, Node*&);   // Inserts a value
    void remove(Node*&, T);        // Removes a value
    void makeDeletion(Node*&, T);  // Deletes a value
    bool contains(Node*&, T);      // Checks if the tree contains a value

    int size(Node*&);          // Returns the size
    int getLeafCount(Node*&);  // Returns the number of leaf nodes
    int getHeight(Node*&);     // Returns the height
    int getLevel(Node*&, T);   // Gets the level of a particular value

    void getInOrderTraversal(Node*&,
                             stringstream&);  // Helper method for traversal by
                                              // adding values to stringstream
    void getPreOrderTraversal(Node*&,
                              stringstream&);  // Helper method for traversal by
                                               // adding values to stringstream
    void getPostOrderTraversal(
        Node*&, stringstream&);  // Helper method for traversal by adding values
                                 // to stringstream

    bool getAncestors(Node*&, stringstream&,
                      T);  // Helper method for getting ancestors by adding
                           // values to stringstream
};

// Default constructor
template <typename T>
BST<T>::BST() {
    root = nullptr;
}

// Copy constructor
template <typename T>
BST<T>::BST(BST<T>& tree2) {
    root = nullptr;
    copyTree(root, tree2.root);
}

// Destructor
template <typename T>
BST<T>::~BST() {
    destroyTree(root);
}

// Destructor helper
template <typename T>
void BST<T>::destroyTree(Node*& ptr) {
    if (ptr) {
        destroyTree(ptr->left);
        destroyTree(ptr->right);
        delete ptr;
    }
    ptr = nullptr;
}

// Equals operator
template <typename T>
BST<T>& BST<T>::operator=(BST<T>& tree2) {
    if (this != &tree2) {
        destroyTree(root);
        copyTree(root, tree2.root);
    }
    return *this;
}

// Helper method to copy contents of tree
template <typename T>
void BST<T>::copyTree(Node*& tree1, Node*& tree2) {
    // If tree 2's not null
    if (tree2) {
        // Generate new node for tree1 if needed
        if (!tree1) {
            tree1 = new Node;
            tree1->left = nullptr;
            tree1->right = nullptr;
        }
        // Copy data
        tree1->data = tree2->data;

        // Copy data from left and right nodes of tree2
        copyTree(tree1->left, tree2->left);
        copyTree(tree1->right, tree2->right);
    }
}

// Insert a new item
template <typename T>
void BST<T>::insert(T item) {
    // Create new node
    Node* newNode = new Node;
    // Add item
    newNode->data = item;
    // Set left and right to be nullptr
    newNode->left = newNode->right = nullptr;

    // Insert helper
    insert(root, newNode);
}

// Insert helper method
template <typename T>
void BST<T>::insert(Node*& ptr, Node*& newNode) {
    if (ptr == nullptr)
        // Create a newNode if needed
        ptr = newNode;
    else if (ptr->data > newNode->data)
        // Else insert data to correct spot
        insert(ptr->left, newNode);
    else
        insert(ptr->right, newNode);
}

// Returns if a value is contained in the BST
template <typename T>
bool BST<T>::contains(T item) {
    // Call helper method
    return contains(root, item);
}

// Helper method to check if a value is contained in BST
template <typename T>
bool BST<T>::contains(Node*& ptr, T item) {
    // Check if ptr is null
    if (ptr) {
        // Check if data matches what we're looking for, if not, recurse
        if (ptr->data == item) {
            return true;
        } else if (ptr->data > item) {
            return contains(ptr->left, item);
        } else {
            return contains(ptr->right, item);
        }
    }
    return false;
}

// Remove an item
template <typename T>
void BST<T>::remove(T item) {
    // Call helper
    remove(root, item);
}

// Helper to remove an item
template <typename T>
void BST<T>::remove(Node*& ptr, T item) {
    // Check if ptr is null
    if (ptr != nullptr) {
        // If not, recurse or make deletion
        if (ptr->data > item)
            remove(ptr->left, item);
        else if (ptr->data < item)
            remove(ptr->right, item);
        else
            makeDeletion(ptr, item);
    }
}

// Delete an item
template <typename T>
void BST<T>::makeDeletion(Node*& ptr, T item) {
    // Iterate and remove
    Node* curr = nullptr;
    if (ptr != nullptr) {
        if (ptr->left == nullptr) {
            curr = ptr;
            ptr = ptr->right;
            delete curr;
        } else if (ptr->right == nullptr) {
            curr = ptr;
            ptr = ptr->left;
            delete curr;
        } else {
            curr = ptr->right;
            while (curr->left != nullptr) curr = curr->left;
            ptr->data = curr->data;
            remove(ptr->right, curr->data);
        }
    }
}

// Returns if the tree is empty or not
template <typename T>
bool BST<T>::empty() {
    return root == nullptr;
}

// Returns the size
template <typename T>
int BST<T>::size() {
    // Calls helper
    return size(root);
}

// Helper size method
template <typename T>
int BST<T>::size(Node*& ptr) {
    // Return 0 if empty, otherwise recurse
    if (ptr == nullptr) {
        return 0;
    } else {
        return 1 + size(ptr->left) + size(ptr->right);
    }
}

// Counts number of leaf nodes
template <typename T>
int BST<T>::getLeafCount() {
    // Calls helper method
    return getLeafCount(root);
}

// Helper method for getting leaf count
template <typename T>
int BST<T>::getLeafCount(Node*& ptr) {
    // Check if ptr is null
    if (ptr == nullptr) {
        return 0;
    } else {
        // If it's not, recurse until we get to a leaf node
        if (ptr->left == nullptr && ptr->right == nullptr) {
            return 1;
        } else {
            return getLeafCount(ptr->left) + getLeafCount(ptr->right);
        }
    }
}

// Gets the height of the tree
template <typename T>
int BST<T>::getHeight() {
    // Call helper method
    return getHeight(root);
}

// Helper method to get height
template <typename T>
int BST<T>::getHeight(Node*& ptr) {
    // If ptr is null return 0
    if (ptr == nullptr) {
        return 0;
    } else {
        // Otherwise recurse
        return 1 + max(getHeight(ptr->left), getHeight(ptr->right));
    }
}

// Gets the level of a particular item
template <typename T>
int BST<T>::getLevel(T target) {
    // Call helper method
    return getLevel(root, target);
}

// Helper method to get level
template <typename T>
int BST<T>::getLevel(Node*& ptr, T target) {
    // If ptr is null return -1
    if (ptr == nullptr) {
        return -1;
    } else {
        // Otherwise if we found the target we return 0
        if (ptr->data == target) {
            return 0;
        } else {
            // Otherwise we travel towards the correct side of the bst based on
            // value
            if (ptr->data < target) {
                // If ans is -1, so it doesn't exist in the tree, we return 01,
                // otherwise we add 1 to the answer each time we go up a level
                int ans = getLevel(ptr->right, target);
                return ans == -1 ? -1 : 1 + ans;
            } else {
                int ans = getLevel(ptr->left, target);
                return ans == -1 ? -1 : 1 + ans;
            }
        }
    }
}

// Get inorder traversal
template <typename T>
string BST<T>::getInOrderTraversal() {
    // Create a stringstream to store answer
    stringstream ss;
    // Helper method
    getInOrderTraversal(root, ss);
    return ss.str();
}

// Helper method
template <typename T>
void BST<T>::getInOrderTraversal(Node*& ptr, stringstream& ss) {
    // If ptr isn't null
    if (ptr != nullptr) {
        // Recurse in the proper order and add to ss
        getInOrderTraversal(ptr->left, ss);
        ss << ptr->data << " ";
        getInOrderTraversal(ptr->right, ss);
    }
    return;
}

// Get preorder traversal
template <typename T>
string BST<T>::getPreOrderTraversal() {
    // Create a stringstream to store answer
    stringstream ss;
    // Helper method
    getPreOrderTraversal(root, ss);
    return ss.str();
}

// Helper method
template <typename T>
void BST<T>::getPreOrderTraversal(Node*& ptr, stringstream& ss) {
    // If ptr isn't null
    if (ptr != nullptr) {
        // Recurse in the proper order and add to ss
        ss << ptr->data << " ";
        getPreOrderTraversal(ptr->left, ss);
        getPreOrderTraversal(ptr->right, ss);
    }
    return;
}

// Get postorder traversal
template <typename T>
string BST<T>::getPostOrderTraversal() {
    // Create a stringstream to store answer
    stringstream ss;
    // Helper method
    getPostOrderTraversal(root, ss);
    return ss.str();
}

// Helper method
template <typename T>
void BST<T>::getPostOrderTraversal(Node*& ptr, stringstream& ss) {
    // If ptr isn't null
    if (ptr != nullptr) {
        // Recurse in the proper order and add to ss
        getPostOrderTraversal(ptr->left, ss);
        getPostOrderTraversal(ptr->right, ss);
        ss << ptr->data << " ";
    }
    return;
}

// Get ancestors of a particular value
template <typename T>
string BST<T>::getAncestors(T target) {
    // Create stringstream to store answer
    stringstream ss;
    // Helper method
    getAncestors(root, ss, target);
    return ss.str();
}

// Helper method
template <typename T>
bool BST<T>::getAncestors(Node*& ptr, stringstream& ss, T target) {
    // If ptr isn't null
    if (ptr != nullptr) {
        if (ptr->data == target) {
            // If current node is target, return true so above functions save to
            // ss, but don't include current node's value
            return true;
        } else if (ptr->data < target) {
            // Otherwise, traverse binary search tree according to whether
            // current node's value is larger or smaller than target
            if (getAncestors(ptr->right, ss, target)) {
                // If the right side of the tree contains the target value (so
                // getAncestors(ptr->right) evaluates true) then also save
                // current node's value to ss as it's an ancestor node, then
                // return true so above functions also save to ss
                ss << ptr->data << " ";
                return true;
            }
        } else {
            if (getAncestors(ptr->left, ss, target)) {
                ss << ptr->data << " ";
                return true;
            }
        }
    }

    // Return false if target's not found so nothing is saved to ss
    return false;
}

#endif  // P2_BST_H