#include "sequential-list.h"

SequentialList::SequentialList(unsigned int cap) {
    capacity_ = cap;
    size_ = 0;
    data_ = new DataType [cap];
}


SequentialList::~SequentialList() {
    delete [] data_;
    data_ = nullptr;
}


unsigned int SequentialList::size() const {
    return size_;
}

unsigned int SequentialList::capacity() const {
    return capacity_;
}


bool SequentialList::empty() const {
    return(size_ == 0);
}


bool SequentialList::full() const {
    return(size_ == capacity_);
}


SequentialList::DataType SequentialList::select(unsigned int index) const {
    if(index < size_){
        return data_[index];
    }
    return data_[size_-1];
}


unsigned int SequentialList::search(DataType val) const {
    for(unsigned int i = 0; i < size_; i++) {
        if (data_[i] == val) {
            return i;
        }
    }
    return size_;
}


void SequentialList::print() const {
    for(unsigned int i = 0; i < size_; i++)
    {
        std::cout << data_[i] << std::endl;
    }

}


bool SequentialList::insert(DataType val, unsigned int index) {
    if(index > size_ || full()) {
        return false;
    }
    for(unsigned int i = size_; i > index; i--) {
        data_[i] = data_[i-1];
    }
    data_[index] = val;
    size_ += 1;
    return true;

}


bool SequentialList::insert_front(DataType val) {
    if(full()) {
        return false;
    }

    if (size_!=0) {
        for (unsigned int i = size_; i > 0; i--) {
            data_[i] = data_[i - 1];
        }
    }
    data_[0] = val;
    size_ += 1;
    return true;
}



bool SequentialList::insert_back(DataType val) {

    if(full())
        return false;

    data_[size_] = val;
    size_ += 1;
    return true;
}


bool SequentialList::remove(unsigned int index) {
    if(empty() || index > size_)
        return false;

    for(unsigned int i = index; i < size_; i++){
        data_[i] = data_[i+1];
    }
    data_[size_-1] = DataType(NULL);
    size_ -= 1;
    return true;
}


bool SequentialList::remove_front() {
    if(empty())
        return false;

    for(unsigned int i = 0; i < size_; i++){
        data_[i] = data_[i+1];
    }
    data_[size_-1] = DataType(NULL);
    size_ -= 1;
    return true;
}

bool SequentialList::remove_back() {
    if(size_ == 0) {
        return false;
    }


    data_[size_-1] = DataType(NULL);
    size_ -= 1;
    return true;


}

bool SequentialList::replace(unsigned int index, DataType val) {
    if(index >= size_) {
        return false;
    }
    data_[index] = val;
    return true;
}
