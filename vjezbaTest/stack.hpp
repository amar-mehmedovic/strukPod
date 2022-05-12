#include <iostream>
#include <stdexcept>
#pragma once

template <typename T>
class Stack {
   private:
    T* arr_;
    size_t size_;
    size_t capacity_;

   public:
    // DEFAULT C-TOR
    Stack(size_t capacity = 100)
	: size_{0}, capacity_{capacity}, arr_{new T[capacity_]} {}
    // COPY C-TOR
    Stack(const Stack& other) {
	size_ = other.size_;
	capacity_ = other.capacity_;
	arr_ = new T[capacity_];
	std::copy(other.arr_, other.arr_ + size_, arr_);
    }
    // DESTRUCTOR
    ~Stack() {
	delete[] arr_;
	size_ = 0;
	capacity_ = 0;
	arr_ = nullptr;
    }
    void print() const {
	for (int i = 0; i < size_; i++) {
	    std::cout << arr_[i];
	}
	std::cout << "" << std::endl;
    }

    Stack& push(const T& elem) {
	if (size_ >= capacity_) {
	    throw std::out_of_range("Out of space");
	}
	arr_[size_++] = elem;
	return *this;
    }

    Stack& push(T&& elem) {
	if (size_ >= capacity_) {
	    throw std::out_of_range("Out of space");
	}
	arr_[size_++] = std::move(elem);
    }

    T& top() {
	if (size_ == 0) {
	    throw std::out_of_range("Stack empty");
	}
	return arr_[size_ - 1];
    }

    const T& top() const {
	if (size_ == 0) {
	    throw std::out_of_range("Stack empty");
	}
	return arr_[size_ - 1];
    }
    void reallocate(size_t new_capacity) {
	if (capacity_ == new_capacity) {
	    return;
	}
	auto new_size = size_;
	if (size_ > new_capacity) {
	    new_size = new_capacity;
	}
	auto temp = new T[new_capacity];
	std::copy(arr_, arr_ + new_size, temp);
	delete[] arr_;
	arr_ = temp;
	temp = nullptr;
	capacity_ = new_capacity;
	size_ = new_size;
    }
    T pop() {
	if (size_ == 0) {
	    throw std::out_of_range("Stack empty");
	}
	auto value = arr_[size_ - 1];
	arr_[size_ - 1] = 0;
	size_--;
    }
};
