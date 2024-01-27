#include "dynamic-stack.h"
#include <iostream>

const DynamicStack::StackItem DynamicStack::EMPTY_STACK = -999;

DynamicStack::DynamicStack() {
    init_capacity_ = 16;
    capacity_ = init_capacity_;
    items_ = new StackItem[capacity_];
    size_ = 0;
}

DynamicStack::DynamicStack(unsigned int capacity){
    capacity_ = capacity;
    init_capacity_ = capacity;
    items_ = new StackItem[capacity_];
    size_ = 0;
}

DynamicStack::~DynamicStack() {
    delete [] items_;
    items_ = nullptr;

}

unsigned int DynamicStack::size() const {
    return size_;
}

bool DynamicStack::empty() const {
    return size_ == 0;
}

DynamicStack::StackItem DynamicStack::peek() const {
    if (empty())
        return EMPTY_STACK;
    return items_[size_-1];
}

void DynamicStack::push(StackItem value) {
    if (size_ == capacity_)
    {
        StackItem *newItems = new StackItem[capacity_*2];
        capacity_ *= 2;
        for (int i = 0; i < size_; i++)
        {
            newItems[i] = items_[i];
        }

        int *prevItems = items_;
        items_ = newItems;
        delete [] prevItems;
        prevItems = nullptr;
        newItems = nullptr;
    }
    items_[size_] = value;
    size_++;

}

DynamicStack::StackItem DynamicStack::pop() {
    if(empty())
    {
        return EMPTY_STACK;
    }

    StackItem pop = items_[size_ - 1];
    items_[size_ - 1] = EMPTY_STACK ;
    size_--;

    if(size_ <= capacity_/4 && capacity_/2 >= init_capacity_) {
        StackItem *newItems = new StackItem[capacity_ / 2];
        capacity_ /= 2;
        for (int i = 0; i < size_+1; i++) {
            newItems[i] = items_[i];
        }
        int *prevItems = items_;
        items_ = newItems;
        delete[] prevItems;
        prevItems = nullptr;
        newItems = nullptr;
    }
    return pop;
}

void DynamicStack::print() const {
    for (int i = size_-1; i >= 0; i--) {
        std::cout << items_[i] << std::endl;
    }
}
