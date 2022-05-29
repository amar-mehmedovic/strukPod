#pragma once

#include <algorithm>
#include <iostream>
#include <stdexcept>

template <typename T>
class MojVector {
   public:
    MojVector() {
	size_ = 0;
	capacity_ = 6;
	arr_ = new T[capacity_];
    }

    MojVector(const std::initializer_list<T> &lista) {
	size_ = lista.size();
	capacity_ = lista.size() + 1;
	arr_ = new T[capacity_];
	std::copy(lista.begin(), lista.end(), arr_);
    }

    MojVector(const MojVector &other) {
	size_ = other.size_;
	capacity_ = other.capacity_;
	arr_ = new T[capacity_];
	std::copy(other.arr_, other.arr_ + capacity_, arr_);
    }
    MojVector &operator=(const MojVector &other) {
	if (this == &other) {
	    return *this;
	}
	size_ = other.size_;
	capacity_ = other.capacity_;
	delete[] arr_;
	arr_ = new T[capacity_];
	std::copy(other.arr_, other.arr_ + capacity_, arr_);
	return *this;
    }

    MojVector(MojVector &&other) {
	size_ = other.size_;
	capacity_ = other.capacity_;
	arr_ = other.arr_;
	other.arr_ = nullptr;
	other.size_ = 0;
	other.capacity_ = 0;
    }

    MojVector &operator=(MojVector &&other) {
	size_ = other.size_;
	capacity_ = other.capacity_;
	delete[] arr_;
	arr_ = other.arr_;
	other.arr_ = nullptr;
	other.size_ = 0;
	other.capacity_ = 0;
	return *this;
    }

    ~MojVector() {
	delete[] arr_;
	size_ = 0;
	capacity_ = 0;
    }

    void push_back(const T element) {
	if (size_ >= capacity_) {
	    reallocate(2 * capacity_);
	}
	arr_[size_++] = element;
    }

    T &at(size_t index) const {
	if (index < 0 || index >= size_) {
	    throw std::out_of_range("Izvan opsega vektora");
	}
	return arr_[index];
    }

    T &operator[](size_t index) const { return arr_[index]; }

    void clear() {
	delete[] arr_;
	size_ = 0;
	capacity_ = 1;
	arr_ = new T[capacity_];
    }

    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }
    const T &back() const { return arr_[size_ - 1]; }
    const T &front() const { return *arr_; }
    T &back() { return arr_[size_ - 1]; };
    T &front() { return *arr_; };

    void resize(size_t new_size) { size_ = new_size; }
    void reallocate(size_t new_capacity) {
	T *new_arr = new T[new_capacity];
	for (int i = 0; i < size_; i++) {
	    new_arr[i] = arr_[i];
	}
	capacity_ = new_capacity;
	delete[] arr_;
	arr_ = new_arr;
	new_arr = nullptr;
    }

    void pop_back() {
	if (empty()) {
	    std::cout << "Vektor prazan!!" << std::endl;
	    return;
	}
	arr_[--size_] = 0;
    }
    size_t capacity() const { return capacity_; }

    bool operator==(const MojVector &other) const {
	if (size_ != other.size_) {
	    return false;
	}
	for (int i = 0; i < size_; i++) {
	    if (arr_[i] != other.arr_[i]) {
		return false;
	    }
	}
	return true;
    }

    bool operator!=(const MojVector &other) const {
	if (size_ != other.size_) {
	    return true;
	}
	for (int i = 0; i < size_; i++) {
	    if (arr_[i] != other.arr_[i]) {
		return true;
	    }
	}
	return false;
    }

    class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
       public:
	Iterator(T *ptr) : ptr_{ptr} {}
	T &operator*() const { return *ptr_; }
	T *operator->() const { return ptr_; }
	Iterator &operator++() {
	    ptr_++;
	    return *this;
	}
	Iterator operator++(int) {
	    auto temp = ptr_;
	    ++ptr_;
	    return temp;
	}
	Iterator &operator--() {
	    --ptr_;
	    return *this;
	}
	Iterator operator--(int) {
	    auto temp = ptr_;
	    --ptr_;
	    return temp;
	}
	Iterator operator+(size_t index) { return Iterator(ptr_ + index); }
	Iterator operator-(size_t index) { return Iterator(ptr_ - index); }
	size_t operator-(Iterator other) {
	    auto pos = ptr_;
	    int distance = 0;
	    if (*this < other) {
		throw std::out_of_range("NIje dozvoljeno");
	    }
	    while (pos != other.ptr_) {
		distance++;
		pos--;
	    }
	    return distance;
	}

	bool operator==(const Iterator &it) const { return ptr_ == it.ptr_; }
	bool operator!=(const Iterator &it) const { return ptr_ != it.ptr_; }
	bool operator<(const Iterator &it) const { return ptr_ < it.ptr_; }

	~Iterator() { ptr_ = nullptr; }

       private:
	T *ptr_;
    };

    Iterator begin() const { return Iterator(arr_); }
    Iterator end() const { return Iterator(arr_ + size_); }

    Iterator find(const T &element) const {
	for (int i = 0; i < size_; i++) {
	    if (arr_[i] == element) return Iterator(arr_ + i);
	}
	return Iterator(arr_ + size_);
    }

    MojVector &insert(Iterator pos, T element) {
	if (size_ == capacity_) {
	    reallocate(2 * capacity_);
	}
	size_t index = pos - Iterator(arr_);
	for (int i = size_ - 1; i >= index; i++) {
	    arr_[i + 1] = arr_[i];
	}
	arr_[index] = element;
	return *this;
    }

    Iterator erase(Iterator pos) {
	auto temp = pos;
	for (auto i = pos + 1; i != end();) {
	    *pos++ = *i++;
	}
	size_--;
	return temp;
    }
    Iterator erase(Iterator beginIt, Iterator endIt) {
	size_t remove = endIt - beginIt;
	for (auto i = beginIt; i < end();) {
	    *i++ = *endIt++;
	}
	size_ = size_ - remove;
    }

   private:
    size_t capacity_;
    size_t size_;
    T *arr_;
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const MojVector<T> &other) {
    for (int i = 0; i < other.size(); i++) {
	out << other.at(i) << ",";
    }
    return out;
}

