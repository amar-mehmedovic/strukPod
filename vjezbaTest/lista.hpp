#include <iostream>
#include <iterator>
#include <stdexcept>
#pragma once

template <typename T>
class Lista {
   public:
    // DEFAULT C-TOR
    //
    Lista() = default;
    bool empty() { return size_ == 0; }
    size_t size() { return size_; }

    // ADDING element to back
    //
    void push_back(const T& elem) {
	auto new_node = new Node(elem);
	if (empty()) {
	    first_ = last_ = new_node;
	} else {
	    last_->next = new_node;
	    last_ = new_node;
	}
	size_++;
    }
    // AT operator
    T& at(size_t indeks) const {
	if (indeks < 0 || indeks > size_) {
	    throw std::out_of_range("Out of range index");
	}
	int i = 0;
	auto temp = first_;
	while (temp != nullptr) {
	    if (i == indeks) {
		return temp->data;
	    }
	    temp = temp->next;
	    i++;
	}
	throw std::out_of_range("Out of range index");
    }

    // IZBRISATI SVE CVOROVE
    void clear() {
	if (!empty()) {
	    Node* temp = first_;
	    while (first_ != nullptr) {
		temp = temp->next;
		delete first_;
		first_ = temp;
	    }
	}
	first_ = last_ = nullptr;
	size_ = 0;
    }
    // ADDING element to front
    void push_front(const T& elem) {
	auto new_node = new Node(elem, first_);
	if (empty()) {
	    last_ = new_node;
	} else {
	    first_ = new_node;
	}
	size_++;
    }
    // COPY C-TOR
    Lista(const Lista& other) : first_{nullptr}, last_{nullptr}, size_{0} {
	if (!other.empty()) {
	    for (auto i = other.first_; i != nullptr; i = i->next) {
		push_back(i->data);
	    }
	}
    }
    // COPY MOVE C-TOR
    Lista(Lista&& other)
	: first_{other.first_}, last_{other.last_}, size_{other.size_} {
	first_ = nullptr;
	last_ = nullptr;
	size_ = 0;
    }

    // OPERATOR =
    Lista& operator=(const Lista& other) {
	if (this != &other) {
	    clear();
	    for (auto temp = first_; temp != nullptr; temp = temp->next) {
		push_back(temp->data);
	    }
	}
	return *this;
    }

    // MOVE OPERATOR =
    Lista& operator=(Lista&& other) {
	if (this != &other) {
	    clear();
	    first_ = other.first_;
	    last_ = other.last_;
	    size_ = other.size_;
	}
    }
    // DESTRUCTOR
    ~Lista() { clear(); }

    void push_back(T&& element) {
	auto new_node = new Node(std::move(element));
	if (empty()) {
	    first_ = last_ = new_node;
	} else {
	    last_->next = new_node;
	    last_ = new_node;
	}
	size_++;
    }

    void push_front(T&& element) {
	auto new_node = new Node(std::move(element), first_);
	if (empty()) {
	    last_ = new_node;
	} else {
	    first_ = new_node;
	}
	size_++;
    }

    class iterator;

   private:
    struct Node {
	T data;
	Node* next;
	// PRAVILO 6-TORKE
	Node(const T& element, Node* node = nullptr)
	    : data{element}, next{node} {}
	Node(T&& element, Node* node = nullptr) : data{element}, next{node} {}
    };
    Node* first_ = nullptr;
    Node* last_ = nullptr;
    size_t size_ = 0;
};
template <typename T>
class Lista<T>::iterator : public std::iterator<std::forward_iterator_tag, T> {
   public:
    iterator() = default;
    iterator(Node* node) : ptr_{node} {}
    friend class Lista<T>;

   private:
    Node* ptr_;
};
