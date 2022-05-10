// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// This file includes all of the pieces of the BST implementation

// Include the node implementation
#include "BSTNode.h"

// Include the dictionary ADT
#include "dictionary.h"

#ifndef BST_H
#define BST_H

using namespace std;

// Binary Search Tree implementation for the Dictionary ADT
template <typename Key, typename E>
class BST : public Dictionary<Key, E> {
private:
    BSTNode<Key, E>* root;   // Root of the BST

    int nodecount;         // Number of nodes in the BST

    // Private "helper" functions
    void clearhelp(BSTNode<Key, E>*);
    BSTNode<Key, E>* inserthelp(BSTNode<Key, E>*,
        const Key&, const E&);
    BSTNode<Key, E>* deletemin(BSTNode<Key, E>*);
    BSTNode<Key, E>* getmin(BSTNode<Key, E>*);
    BSTNode<Key, E>* getmax(BSTNode<Key, E>*);
    BSTNode<Key, E>* removehelp(BSTNode<Key, E>*, const Key&);
    E* findhelp(BSTNode<Key, E>*, const Key&) const;
    void printhelp(BSTNode<Key, E>*, int) const;
    void vist(BSTNode<Key, E>*) const;
    BSTNode<Key, E>* getLeftPredecessor(BSTNode<Key, E>*, BSTNode<Key, E>*); // Added Predecessor function for the print help section
    BSTNode<Key, E>* getRightPredecessor(BSTNode<Key, E>*, BSTNode<Key, E>*); // Added Successor function for the print help section

public:
    BST() { root = NULL; nodecount = 0; }  // Constructor

    //Note from Prof Sipantzi -- I've commented out the destructor
    //since you would have to change clearhelp() to make it work with
    //doubly-threaded trees and that is not part of the assignment.
    //~BST() { clearhelp(root); }            // Destructor

    void clear()   // Reinitialize tree
    {
        clearhelp(root); root = NULL; nodecount = 0;
    }

    // Insert a record into the tree.
    // k Key value of the record.
    // e The record to insert.
    void insert(const Key& k, const E& e) {
        root = inserthelp(root, k, e);
        nodecount++;
    }

    // Remove a record from the tree.
    // k Key value of record to remove.
    // Return: The record removed, or NULL if there is none.
    E* remove(const Key& k) {
        E* temp = findhelp(root, k);   // First find it
        if (temp != NULL) {
            root = removehelp(root, k);
            nodecount--;
        }
        return temp;
    }
    // Remove and return the root node from the dictionary.
    // Return: The record removed, null if tree is empty.
    E* removeAny() {  // Delete min value
        if (root != NULL) {
            E* temp = new E;
            *temp = root->element();
            root = removehelp(root, root->key());
            nodecount--;
            return temp;
        }
        else return NULL;
    }

    // Return Record with key value k, NULL if none exist.
    // k: The key value to find. */
    // Return some record matching "k".
    // Return true if such exists, false otherwise. If
    // multiple records match "k", return an arbitrary one.
    E* find(const Key& k) const { return findhelp(root, k); }

    // Return the number of records in the dictionary.
    int size() { return nodecount; }

    void print() const { // Print the contents of the BST
        if (root == NULL) cout << "The BST is empty.\n";
        else printhelp(root, 0);
    }

    void printInorder(); // function that prints in order and it is in the public section so that we can access it in main

    void printReverse(); //function that prints in reverse and it is in the public section so that we can access it from main
};

// Visit -- prints out root
template <typename Key, typename E>
void BST<Key, E>::vist(BSTNode<Key, E>* r) const {
    cout << "Node - " << r->element() << endl;
}

// Clean up BST by releasing space back free store
template <typename Key, typename E>
void BST<Key, E>::
clearhelp(BSTNode<Key, E>* root) {
    if (root == NULL) return;
    clearhelp(root->left());
    clearhelp(root->right());
    delete root;
}

// Find and return the left parent of a node
// Precondition, child has a left parent
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::getLeftPredecessor(BSTNode<Key, E>* parent, BSTNode<Key, E>* child) {
    if (child->key() < parent->key()) {
        if (child == getmin(parent->left())) // get the minimum value and passes it from parent to left
            return parent;
        else return getLeftPredecessor(parent->left(), child); //and returns the predecessor function with parent and left section of child
    }
    if (child->key() > parent->key()) { 
        if (child == getmin(parent->right())) // similar logic to the function above but instead it sets it to right
            return parent;
        else return getLeftPredecessor(parent->right(), child); // and returns the predecessor function with parent to right section of child
    }
}

// Find and return the right parent of a node, if it exists
// Precondition, child has a right parent
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::getRightPredecessor(BSTNode<Key, E>* parent, BSTNode<Key, E>* child) { //similar logic to the whole function above with slight changes.
    if (child->key() < parent->key()) {
        if (child == getmax(parent->left())) // searching for the maximum value and passing it to the parent to left
            return parent;
        else return getRightPredecessor(parent->left(), child); //returning the predecessor to parent to right child
    }
    if (child->key() > parent->key()) { //same logic but inverted functions. 
        if (child == getmax(parent->right())) //searches for the maximum value and passing it to the parent to the right
            return parent;
        else return getRightPredecessor(parent->right(), child); //returning the predecessor to parent to right child
    }
}

// Insert a node into the BST, returning the updated tree
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::inserthelp(BSTNode<Key, E>* parent, const Key& k, const E& it) { //updating the inserthelp() function to accomodate the changes
    if (root == NULL) { // Empty tree: create node
        BSTNode<Key, E>* newBST = new BSTNode<Key, E>(k, it, NULL, NULL);
        newBST->setLeft(newBST); //the following functions are manually setting the left and right functions to pass newBst variable
        newBST->setRight(newBST);
        newBST->setLeftBit(0); //the following functions are set to 0 as a parameter
        newBST->setRightBit(0);
        return newBST;
    }
    if (k < parent->key()) {
        if (!parent->isLeftBranch()) {
            BSTNode<Key, E>* newBST = new BSTNode<Key, E>(k, it, NULL, NULL);
            parent->setLeft(newBST); // setting the parent to the functions from earlier
            parent->setLeftBit(1); 
            newBST->setLeftBit(0); // using the same logic however setting them to the leftbit
            newBST->setRightBit(0);
            newBST->setRight(parent);
            if (newBST == getmin(root))
                newBST->setLeft(root);
            else newBST->setLeft(getLeftPredecessor(root, newBST));
        }
        else parent->setLeft(inserthelp(parent->left(), k, it));
    }
    else if (k > parent->key()) {
        if (!parent->isRightBranch()) {
            BSTNode<Key, E>* newBST = new BSTNode<Key, E>(k, it, NULL, NULL);
            parent->setRight(newBST);
            parent->setRightBit(1); // Also, using the same logic but setting them to the rightbit
            newBST->setLeftBit(0); // setting rightbit to 0 as parameter
            newBST->setRightBit(0);
            newBST->setLeft(parent);
            if (newBST == getmax(root))
                newBST->setRight(root);
            else newBST->setRight(getRightPredecessor(root, newBST));
        }
        else parent->setRight(inserthelp(parent->right(), k, it));
    }
    return parent;       // Return tree with node inserted
}

//Find and return the min value of the BST
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
getmin(BSTNode<Key, E>* rt) {
    if (!rt->isLeftBranch())
        return rt;
    else return getmin(rt->left());
}

//Find and return the max value of the BST
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
getmax(BSTNode<Key, E>* rt) {
    if (!rt->isRightBranch())
        return rt;
    else return getmax(rt->right());
}

template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
deletemin(BSTNode<Key, E>* rt) {
    if (rt->left() == NULL) // Found min
        return rt->right();
    else {                      // Continue left
        rt->setLeft(deletemin(rt->left()));
        return rt;
    }
}

// Remove a node with key value k
// Return: The tree with the node removed
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::removehelp(BSTNode<Key, E>* rt, const Key& k) {
    if (rt == NULL) return NULL;    // k is not in tree
    else if (k < rt->key())
        rt->setLeft(removehelp(rt->left(), k));
    else if (k > rt->key())
        rt->setRight(removehelp(rt->right(), k));
    else {                            // Found: remove it
        BSTNode<Key, E>* temp = rt;
        if (rt->left() == NULL) {     // Only a right child
            rt = rt->right();         //  so point to right
            delete temp;
        }
        else if (rt->right() == NULL) { // Only a left child
            rt = rt->left();          //  so point to left
            delete temp;
        }
        else {                    // Both children are non-empty
            BSTNode<Key, E>* temp = getmin(rt->right());
            rt->setElement(temp->element());
            rt->setKey(temp->key());
            rt->setRight(deletemin(rt->right()));
            delete temp;
        }
    }
    return rt;
}

// Find a node with the given key value
template <typename Key, typename E>
E* BST<Key, E>::findhelp(BSTNode<Key, E>* root,
    const Key& k) const {
    if (root == NULL) return NULL;          // Empty tree
    if (k < root->key())
        return findhelp(root->left(), k);   // Check left
    else if (k > root->key())
        return findhelp(root->right(), k);  // Check right
    else {
        E* temp = new E;
        *temp = root->element();
        return temp;  // Found it
    }
}

// Print out a BST
template <typename Key, typename E>
void BST<Key, E>::
printhelp(BSTNode<Key, E>* root, int level) const {
    if (root->isLeftBranch())                  // If left subtree is not empty 
        printhelp(root->left(), level + 1);      // Do left subtree
    for (int i = 0; i < level; i++)                // Indent to level
        cout << "  ";
    cout << root->key() << "\n";               // Print node value
    if (root->isRightBranch())                 // If right subtree is not empty
        printhelp(root->right(), level + 1);         // Do right subtree
}

template <typename Key, typename E> // New function implemented to print the tree in order
void BST<Key, E>::printInorder() { 
    BSTNode<Key, E>* temp = getmin(root); //sets the temp variable to the min value of root
    while (temp != getmax(root)) {
        cout << temp->element() << endl; // displaying the element from the temp variable
        if (temp->rightBit() == 0)
            temp = temp->right();
        else temp = getmin(temp->right()); //else function to determine the minimum value and setting it to the right
    }
    cout << temp->element() << endl;
}

template<typename Key, typename E> // New function implemented to print the tree in reverse
void BST<Key, E>::printReverse() { //uses the same logic but using different functions
    BSTNode<Key, E>* temp = getmax(root); //sets the temp variable to the max value of root
    while (temp != getmin(root)) {
        cout << temp->element() << endl; //displaying the element from the temp variable
        if (temp->leftBit() == 0)
            temp = temp->left();
        else temp = getmax(temp->left()); //else function to determine the maximum value and setting it to the left
    }
    cout << temp->element() << endl;
}

#endif