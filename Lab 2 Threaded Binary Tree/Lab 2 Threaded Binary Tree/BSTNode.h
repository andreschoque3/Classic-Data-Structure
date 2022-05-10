// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// This is the file to include for access to the complete binary node
// template implementation

#include "book.h"
#include "BinNode.h"

#ifndef BSTNODE_H
#define BSTNODE_H

// Simple binary tree node implementation
template <typename Key, typename E>
class BSTNode : public BinNode<E> {
private:
    Key k;                  // The node's key
    E it;                   // The node's value
    BSTNode* lc;            // Pointer to left child
    BSTNode* rc;            // Pointer to right child
    unsigned int lBit : 1;  // Bit field for the left pointer
    unsigned int rBit : 1;  // Bit field for the right pointer

public:
    // Two constructors -- with and without initial values
    BSTNode() { lc = rc = NULL; lBit = rBit = 0; } // calling the left and right bit variables
    BSTNode(Key K, E e, BSTNode* l = NULL, BSTNode* r = NULL)
    {
        k = K; it = e; lc = l; rc = r; lBit = rBit = 0; // also calling the left and right bit variables
    }

    ~BSTNode() {}             // Destructor

    // Functions to set and return the value and key
    E& element() { return it; }
    void setElement(const E& e) { it = e; }
    Key& key() { return k; }
    void setKey(const Key& K) { k = K; }

    // Functions to set and return the children
    inline BSTNode* left() const { return lc; }
    void setLeft(BinNode<E>* b) { lc = (BSTNode*)b; }
    inline BSTNode* right() const { return rc; }
    void setRight(BinNode<E>* b) { rc = (BSTNode*)b; }

    // Return true if it is a leaf, false otherwise
    bool isLeaf() { return (lc == NULL) && (rc == NULL); }

    //Functions to set and return the bit fields
    int leftBit() const { return lBit; } 
    void setLeftBit(unsigned int i) { lBit = i; }
    int rightBit() const { return rBit; }
    void setRightBit(unsigned int i) { rBit = i; }

    //Functions to assess if the left and right pointers are branches or threads 
    //Updates the binary tree into a threaded binary tree
    bool isLeftBranch() const {
        bool value = false;
        if (leftBit() == 1)
            value = true;
        return value;
    }

    bool isRightBranch() const {
        bool value = false;
        if (rightBit() == 1)
            value = true;
        return value;
    }
};

#endif