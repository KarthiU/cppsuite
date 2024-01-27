#ifndef LAB3_AVL_TREE_H
#define LAB3_AVL_TREE_H

#include "binary-search-tree.h"

class AVLTree : public BinarySearchTree {
    Node**rootAddress = BinarySearchTree::getRootNodeAddress();
public:
    // Overriden insert and remove functions
    // Do not modify these definitions

    // The AVL tree should be kept balanced after calling just insert or remove.
    bool insert(DataType val);
    bool remove(DataType val);

    // Define additional functions and attributes below if you need

    bool bal(DataType val);
    bool leftRightRotation(Node *alpha, Node *A, Node *alphaParent);
    bool rightLeftRotation(Node *alpha, Node *A, Node *alphaParent);
    bool leftRotation(Node *alpha, Node *parent);
    bool rightRotation(Node *alpha, Node *parent);
    int Height(Node *n) const;




};

#endif  // LAB3_AVL_TREE_H
