#include "avl-tree.h"
#include <cstdlib>
#include <algorithm>

bool AVLTree::insert(DataType val) {
    bool result = BinarySearchTree::insert(val);
    if (result == false) return false;
    bal(val);
    return true;
}

bool AVLTree::remove(DataType val) {
    bool result = BinarySearchTree::remove(val);
    if (result == false) return false;
    bal(val);
    return true;
}

bool AVLTree::bal(DataType val) {
    Node* alphaParent = nullptr;
    Node* alpha = nullptr;

    Node* A = nullptr;
    Node* childOfA = nullptr;

    Node* curr = *rootAddress;
    Node* prev = nullptr;

    while (curr != nullptr){
        if (abs(Height(curr->right) - Height(curr->left)) == 2){
            alpha = curr;
            alphaParent = prev;
        }
        prev = curr;
        if (curr->val > val) curr = curr->left;
        else curr = curr->right;
    }

    if (alpha == nullptr) return true;

    if (Height(alpha->left) > Height(alpha->right))
        A = alpha->left;
     else
        A = alpha->right;

    if (Height(A->left) > Height(A->right))
        childOfA = A->left;
    else
        childOfA = A->right;

    //rotations
    if (childOfA->val > alpha->val && childOfA->val > A->val)
        leftRotation(alpha, alphaParent);

    else if (childOfA->val < alpha->val && childOfA->val < A->val)
        rightRotation(alpha, alphaParent);

    else if (childOfA->val < alpha->val && childOfA->val > A->val)
        leftRightRotation(alpha, A, alphaParent);

    else if (childOfA->val > alpha->val && val < A->val) {
        rightLeftRotation(alpha, A, alphaParent);
    }
    return true;
}

bool AVLTree::leftRightRotation(Node *alpha, Node *A, Node *alphaParent) {
    leftRotation( A, alpha );
    rightRotation( alpha, alphaParent );
    return true;
}

bool AVLTree::rightLeftRotation(Node *alpha, Node *A, Node *alphaParent) {
    rightRotation( A, alpha);
    leftRotation( alpha, alphaParent );
    return true;
}

bool AVLTree::leftRotation(Node* alpha, Node* parent) {
    Node* A = nullptr;
    if (Height(alpha->left) > Height(alpha->right))A = alpha->left;
    else A = alpha->right;

    alpha->right = A->left;
    A->left = alpha;

    if (parent == nullptr) *rootAddress = A;
    else if (parent->left == alpha) parent->left = A;
    else parent->right = A;

    return true;
}

bool AVLTree::rightRotation(Node *alpha, Node *parent) {
    Node* A = nullptr;
    if (Height(alpha->left) > Height(alpha->right)) A = alpha->left;
    else A = alpha->right;

    alpha->left = A->right;
    A->right = alpha;

    if (parent == nullptr) *rootAddress = A;
    else if (parent->right == alpha) parent->right = A;
    else parent->left = A;

    return true;
}


int AVLTree::Height(Node *n) const {
    if (n == nullptr){
        return -1;
    }
    else if (n->right == nullptr && n->left == nullptr){
        return 0;
    }
    else {
        return (1 + std::max(Height(n->left), Height(n->right)));
    }
}