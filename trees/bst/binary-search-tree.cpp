#include "binary-search-tree.h"
#include <algorithm>
#include <queue>
#include <iostream>

BinarySearchTree::Node::Node(DataType newval) {
    val = newval;
    left = nullptr;
    right = nullptr;
}

int BinarySearchTree::getNodeDepth(Node* n) const {
    if(n == nullptr) return -1;
    if (n->left == nullptr && n->right == nullptr) return 0;
    else {
        return 1 + std::max(getNodeDepth(n->left), getNodeDepth(n->right));
    }
}

BinarySearchTree::BinarySearchTree() {
    size_ = 0;
    root_ = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
    std:: queue<Node*> Q;
    if(root_ != nullptr){
        Q.push(root_);
    }
    while (!Q.empty()) {
        Node *P = Q.front();
        Q.pop();
        if (P->left != nullptr) {
            Q.push(P->left);
        }
        if (P->right != nullptr) {
            Q.push(P->right);
        }
        delete P;
    }
}

unsigned int BinarySearchTree::size() const {
    return size_;
}

BinarySearchTree::DataType BinarySearchTree::max() const {

    Node *curr = root_;
    while(curr -> right != nullptr){
        curr = curr -> right;
    }
    return curr->val;
}

BinarySearchTree::DataType BinarySearchTree::min() const {
    Node *curr = root_;
    while(curr -> left != nullptr){
        curr = curr -> left;
    }
    return curr->val;

}

unsigned int BinarySearchTree::depth() const {
    return getNodeDepth(root_);
}

void BinarySearchTree::print() const {
    if(root_ == nullptr){
        return;
    }
    std:: queue <Node*> Q;
    Q.push(root_);
    while (!Q.empty()) {
        Node *P = Q.front();
        Q.pop();
        std::cout << P->val << ", ";
        if (P->left != nullptr) Q.push(P->left);
        if (P->right != nullptr) Q.push(P->right);
    }
    std::cout<< std::endl;
}

bool BinarySearchTree::exists(DataType val) const {
    Node *curr = root_;
    while(curr != nullptr) {
        if (curr -> val == val) {
            return true;
        }
        else if (curr->val > val) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }
    return false;
}

BinarySearchTree::Node* BinarySearchTree::getRootNode() {
    return root_;
}

BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress() {
    return &root_;
}

bool BinarySearchTree::insert(DataType val) {
    if (exists(val)){
        return false;
    }

    Node *newNode = new Node(val);

    if (root_ == nullptr){
        root_ = newNode;
        size_ = 1;
        return true;
    }

    Node *prev = nullptr;
    Node *curr = root_;

    while(curr != nullptr){
        prev = curr;
        if (curr -> val < val)
            curr = curr -> right;
        else
            curr = curr -> left;
    }

    if (prev->val < val)
        prev->right = newNode;
    else
        prev->left = newNode;

    size_++;
    return true;
}



bool BinarySearchTree::remove(DataType val) {
    if (!exists(val)) {
        return false;
    }
    Node *curr = root_;
    Node *prev = nullptr;

    while (curr != nullptr && curr->val != val) {
        prev = curr;
        if (val < curr->val) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    //leaf
    if (curr->right == nullptr && curr->left == nullptr) {
        if (curr == root_) {
            root_ = nullptr;
        } else if (curr == prev->left) {
            prev->left = nullptr;
        } else {
            prev->right = nullptr;
        }
        delete curr;
        curr = nullptr;
    }

    //1 child
    else if (curr ->left == nullptr || curr->right == nullptr){
        Node *child;
        if (curr ->left == nullptr) {
            child = curr->right;
        } else{
            child = curr->left;
        }

        if (curr == root_) {
            root_ = child;
        } else if (curr == prev->left) {
            prev->left = child;
        } else {
            prev->right = child;
        }

        delete curr;
        curr = nullptr;
    }

    //2 child
    else {
        Node *parent = curr;
        Node *pred = curr->left;

        //find predecessor
        while (pred->right != nullptr) {
            parent = pred;
            pred = pred->right;

        }
        if(parent != curr) {
            parent->right = pred->left;
        }
        else {
            parent->left = pred->left;
        }
        curr->val = pred->val;
        delete pred;
        pred = nullptr;
    }
    size_--;
    return true;
}

