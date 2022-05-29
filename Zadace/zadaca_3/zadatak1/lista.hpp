#include <iostream>
#include <iterator>
#pragma once
template <typename T>

class List {
   public:
    List() = default;

    List(const List& other) {}

    List(List&& other);
    ~List() {
	Node* temp;
	while (first_) {
	    temp = first_->next;
	    delete first_;
	    first_ = temp;
	}
    }
    void pop_front() {
	if (size_ == 0) return;

	if (size_ == 1) {
	    delete first_;
	    first_ = last_ = nullptr;
	} else {
	    auto temp = first_;
	    first_ = first_->next;
	    delete temp;
	}
	size_--;
    }
    void pop_back() {
	if (size_ == 0) return;
	if (size_ == 1) {
	    delete first_;
	    first_ = last_ = nullptr;
	} else {
	    auto temp = first_;
	    while (temp->next != last_) {
		temp = temp->next;
	    }
	    temp->next = nullptr;
	    delete last_;
	    last_ = temp;
	}
	size_--;
    }

    class iterator;
    iterator begin() { return iterator(nullptr, first_); }
    iterator end() { return iterator(last_, nullptr); }

   private:
    struct Node {
	T data;
	Node* next;
	Node(const T& elem, Node* node = nullptr) : data{elem}, next{node} {}
	Node(T&& elem, Node* node = nullptr) : data{elem}, next{node} {}
    };

    Node* first_ = nullptr;
    Node* last_ = nullptr;
    size_t size_ = 0;
};

template <typename T>
class List<T>::iterator : public std::iterator<std::forward_iterator_tag, T> {
   public:
    iterator() = default;
    iterator(Node* prev, Node* current)
	: prevNode_{prev}, currentNode_{current} {}
    iterator& operator++() {
	prevNode_ = currentNode_;
	currentNode_ = currentNode_->next;
	return *this;
    }

    iterator operator++(int) {
	iterator temp = iterator(prevNode_, currentNode_);
	prevNode_ = currentNode_;
	currentNode_ = currentNode_->next;
	return temp;
    }

    bool operator==(const iterator& other) {
	return currentNode_ == other.currentNode_;
    }

    bool operator!=(const iterator& other) {
	return currentNode_ != other.currentNode_;
    }

    T& operator*() { return currentNode_->data; }

    T* operator->() { return &currentNode_->data; }

   private:
    Node* currentNode_;
    Node* prevNode_;
};
