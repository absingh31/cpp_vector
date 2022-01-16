#include <new>
#include <cassert>

// Since it is a class which is templatized, I can not seperate out the hpp and cpp
// I hate having all contents in hpp, but what are the choices I have :p

#pragma once
/* Public APIs
push_back
size
[] ==> for indexing
pop_back
clear
*/


template<class T>
class abvector
{
public:
    abvector() {
        abAlloc(15);
    }

    ~abvector() {
        clear();
        ::operator delete(data_, capacity_ * sizeof(T));
    }

    void abAlloc(size_t newCapacity) {
        T* newDataBlock = (T*)::operator new(newCapacity * sizeof(T));

        for (size_t idx = 0; idx < size_; idx++) {
            newDataBlock[idx] = std::move(data_[idx]);
        }

        for (size_t idx = 0; idx < size_; idx++) {
            data_[idx].~T();
        }

        ::operator delete(data_, capacity_ * sizeof(T));
        data_ = newDataBlock;
        capacity_ = newCapacity;
    }

    void push_back(const T& value) {
        if (size_ >= capacity_) abAlloc(2*capacity_);
        data_[size_++] = value;
    }

    void push_back(T&& value) {
        if (size_ >= capacity_) abAlloc(2*capacity_);

        data_[size_++] = std::move(value);
    }

    size_t size() const{ return size_; }

    const T& operator[](const size_t index) const {
        assert(index < size_);

        return data_[index];
    }

    T& operator[](const size_t index) {
        assert(index < size_);

        return data_[index];
    }

    void pop_back() {
        if (size_ > 0) {
            size_--;
            data_[size_].~T();
        }
    }

    void clear() {
        for (size_t idx = 0; idx < size_; idx++) {
            data_[idx].~T();
        }

        size_ = 0;
    }

private:
    T* data_ = nullptr; // pointer to array
    size_t size_ = 0;
    size_t capacity_ = 0;
};



