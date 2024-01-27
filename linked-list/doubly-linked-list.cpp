#include "doubly-linked-list.h"

DoublyLinkedList::Node::Node(DataType data) {
    value = data;
    next = nullptr;
    prev = nullptr;
}


DoublyLinkedList::DoublyLinkedList() {
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}

DoublyLinkedList::~DoublyLinkedList() {
    Node *curr = head_;
    Node* next;
    while (curr!= nullptr) {
        next = curr -> next;
        delete curr;
        curr = next;
    }
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;

}


unsigned int DoublyLinkedList::size() const {
    return size_;
}


unsigned int DoublyLinkedList::capacity() const {
    return CAPACITY;
}


bool DoublyLinkedList::empty() const {
    return(size_ == 0);
}


bool DoublyLinkedList::full() const {
    return(size_ == CAPACITY);
}


DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const {
    if (index >= size_){
        return tail_ -> value;
    }
    Node *node = getNode(index);
    return node -> value;
}

unsigned int DoublyLinkedList::search(DataType value) const {
    Node* curr = head_;
    unsigned int index = 0;
    while (curr != nullptr){
        if(curr -> value == value){
            return index;
        }
        curr = curr -> next;
        index+=1;
    }
    return size_;

}


void DoublyLinkedList::print() const {
    if (head_ == nullptr) {
        return;
    }
    Node *temp = head_;
    while (temp != nullptr) {
        std::cout<< temp->value<< "->";
        temp = temp->next;
    }
    std::cout<<std::endl;
}


DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const {
    Node* curr = head_;
    if (index == 0){
        return head_;
    }
    for (unsigned int i = 0; i < index; i++) {
        curr = curr -> next;
    }
    return curr;
}


bool DoublyLinkedList::insert(DataType value, unsigned int index) {
    //modelled based on Week 4 Assignment Template
    if(index>size_  || full())
        return false;

    //insert at front
    if(index == 0) {
        insert_front(value);
        return true;
    }

    //insert at back
    if(index == size_) {
        insert_back(value);
        return true;
    }

    Node *newNode = new Node(value);
    Node *curr = getNode(index);
    Node *previous = curr->prev;

    newNode -> prev = previous;
    newNode->next = curr;
    curr->prev = newNode;
    previous->next = newNode;

    size_++;

    return true;

}

bool DoublyLinkedList::insert_front(DataType value) {
    if (full()) {
        return false;
    }

    Node *newNode = new Node(value);

    if (head_ == nullptr || size_ == 0) {
        head_ = newNode;
        tail_ = newNode;
        size_++;
        return true;
    }
    newNode -> next = head_;
    head_->prev = newNode;
    head_ = newNode;
    size_++;
    return true;
}


bool DoublyLinkedList::insert_back(DataType value) {
    if (full()) {
        return false;
    }

    Node *newNode = new Node(value);
    if (size_ == 0) {
        head_ = newNode;
        tail_ = newNode;
        size_++;
        return true;
    }
    newNode-> prev = tail_;
    tail_->next = newNode;
    tail_ = newNode;
    size_ ++;
    return true;

}

bool DoublyLinkedList::remove(unsigned int index) {
    if (empty() || index >= size_)
        return false;

    //front
    if (index == 0){
        remove_front();
        return true;
    }
    //back
    if (index == size_ - 1)
    {
      remove_back();
      return true;
    }

    Node *previous = getNode(index-1);
    Node *curr = previous->next;
    previous->next = curr->next;
    delete curr;
    size_--;
    return true;

}


bool DoublyLinkedList::remove_front() {
    if (empty()) {
        return false;
    }

    Node *temp = head_;
    head_= head_->next;
    if (head_ == nullptr) {
        tail_ = nullptr;
    }
    delete temp;
    size_--;
    return true;

}


bool DoublyLinkedList::remove_back() {
    if (empty()) {
        return false;
    }
    if (size_ == 1){
        head_ = nullptr;
        tail_ = nullptr;
        size_--;
        return true;
    }
    Node *end = tail_;
    tail_ = tail_->prev;
    tail_ -> next = nullptr;

    delete end;
    end = nullptr;

    size_--;
    return true;
}


bool DoublyLinkedList::replace(unsigned int index, DataType value) {
    if(index >= size_ || size_ == 0) {
        return false;
    }
    Node *curr = getNode(index);
    curr->value = value;
    return true;

}
