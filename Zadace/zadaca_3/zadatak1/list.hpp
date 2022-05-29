#include <iostream>

#pragma once

template <typename T>
class List {
   public:
    List() = default;
    List(const List& other);
    List(List&& other);
    List& operator=(const List& other);
    List& operator=(List&& other);
    ~List();

    void clear();
    void push_back(const T& element);
    void push_front(const T& element);
    void push_back(T&& element);
    void push_front(T&& element);
    size_t size() const;
    bool empty() const;
    void pop_front();
    void pop_back();

    T& front();
    T& back();

    const T& at(size_t index) const;

    class iterator;
    iterator begin();
    iterator end();

    void insert(iterator position, const T& element);
    // void insert(iterator position, T&& element);

    iterator erase(iterator position);

   private:
    struct Node;
    Node* first_ = nullptr;
    Node* last_ = nullptr;
    size_t size_ = 0;
};

template <typename T>
void List<T>::push_back(const T& element) {
    auto new_node = new Node(element);
    if (empty()) {
	last_ = first_ = new_node;
    } else {
	last_->next = new_node;
	last_ = new_node;
    }
    size_++;
}

template <typename T>
void List<T>::push_front(const T& element) {
    auto new_node = new Node(element, first_);
    first_ = new_node;
    if (last_ == nullptr) {
	last_ = first_;
    }
    size_++;
}

template <typename T>
const T& List<T>::at(size_t index) const {
    if ((index < 0) || (index > size_)) {
	throw std::out_of_range("Index is out of range");
    }

    auto temp = first_;
    int i = 0;
    while (temp != nullptr) {
	if (i == index) {
	    return temp->data;
	}
	temp = temp->next;
	i++;
    }
    throw std::out_of_range("Index is out of range");
}

template <typename T>
size_t List<T>::size() const {
    return size_;
}

template <typename T>
bool List<T>::empty() const {
    return size_ == 0;
}

template <typename T>
List<T>::List(const List& other) : first_{nullptr}, last_{nullptr}, size_{0} {
    if (!other.empty()) {
	for (auto temp = other.first_; temp != nullptr; temp = temp->next) {
	    push_back(temp->data);
	}
    }
}

template <typename T>
List<T>::List(List&& other)
    : first_{other.first_}, last_{other.last_}, size_{other.size_} {
    other.first_ = nullptr;
    other.last_ = nullptr;
    other.size_ = 0;
}

template <typename T>
List<T>& List<T>::operator=(const List& other) {
    if (this != &other) {
	clear();
	for (auto temp = other.first_; temp != nullptr; temp = temp->next) {
	    push_back(temp->data);
	}
    }
    return *this;
}

template <typename T>
List<T>& List<T>::operator=(List&& other) {
    if (this != &other) {
	clear();
	first_ = other.first_;
	last_ = other.last_;
	size_ = other.size_;

	other.first_ = nullptr;
	other.last_ = nullptr;
	other.size_ = 0;
    }
    return *this;
}

template <typename T>
List<T>::~List() {
    clear();
}

template <typename T>
void List<T>::clear() {
    if (!empty()) {
	auto temp = first_;
	while (temp != nullptr) {
	    first_ = temp;
	    temp = temp->next;
	    delete first_;
	    size_--;
	}
    }
    first_ = last_ = nullptr;
}

template <typename T>
void List<T>::pop_front() {
    if (empty()) return;

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

template <typename T>
void List<T>::pop_back() {
    if (empty()) return;
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

// TODO DRUGI DIO
template <typename T>
struct List<T>::Node {
    T data;
    Node* next;

    Node(const T& elem, Node* node = nullptr) : data{elem}, next{node} {}
    Node(T&& elem, Node* node = nullptr) : data{elem}, next{node} {}
};

// DRUGI DIO
template <typename T>
void List<T>::push_back(T&& element) {
    std::cout << "push_back T&&" << std::endl;
    auto new_node = new Node(std::move(element));
    if (empty()) {
	last_ = first_ = new_node;
    } else {
	last_->next = new_node;
	last_ = new_node;
    }
    size_++;
}

template <typename T>
void List<T>::push_front(T&& element) {
    std::cout << "push_front T&&" << std::endl;
    auto new_node = new Node(std::move(element), first_);
    first_ = new_node;
    if (last_ == nullptr) {
	last_ = first_;
    }
    size_++;
}

template <typename T>
T& List<T>::front() {
    return first_->data;
}

template <typename T>
T& List<T>::back() {
    return last_->data;
}

template <typename T>
class List<T>::iterator : public std::iterator<std::forward_iterator_tag, T> {
   public:
    friend class List<T>;

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
    Node* prevNode_;
    Node* currentNode_;
};

template <typename T>
typename List<T>::iterator List<T>::begin() {
    return iterator(nullptr, first_);
}

template <typename T>
typename List<T>::iterator List<T>::end() {
    return iterator(last_, nullptr);
}

// O(n)
// template <typename T>
// void List<T>::insert(iterator position, const T& element) {
//   if(position == begin()){
//     push_front(element);
//   } else if(position == end()){
//     push_back(element);
//   } else {
//     auto newNode = new Node(element, position.p_);
//     auto temp = first_;
//     while(temp->next != position.p_){
//       temp = temp->next;
//     }
//     temp->next = newNode;
//     size_++;
//   }
// }

// O(1)
template <typename T>
void List<T>::insert(iterator position, const T& element) {
    if (position == begin()) {
	push_front(element);
    } else if (position == end()) {
	push_back(element);
    } else {
	auto newNode = new Node(element, position.currentNode_);
	position.prevNode_->next = newNode;
	size_++;
    }
}

// O(n)
// template <typename T>
// typename List<T>::iterator List<T>::erase(iterator position) {
//   if(position == begin()){
//     pop_front();
//     return begin();
//   } else if(position == end()){
//     pop_back();
//     return iterator(last_);
//   } else {
//     auto temp = first_;
//     while(temp->next != position.p_){
//       temp = temp->next;
//     }

//     auto nodeToDelete = position.p_;
//     auto newNext = nodeToDelete->next;
//     temp->next = newNext;
//     delete nodeToDelete;
//     size_--;
//     return iterator(newNext);
//   }
// }

// O(1)
template <typename T>
typename List<T>::iterator List<T>::erase(iterator position) {
    if (position == begin()) {
	pop_front();
	return begin();
    }

    auto nodeToDelete = position.currentNode_;
    if (position.currentNode_ == last_) {
	std::cout << "Erasing end of list..." << std::endl;
	position.prevNode_->next = nullptr;
	last_ = position.prevNode_;
	last_->next = nullptr;
	delete nodeToDelete;
	size_--;
	return end();
    }

    auto prevNode = position.prevNode_;
    auto nextNode = nodeToDelete->next;
    prevNode->next = nextNode;
    delete nodeToDelete;
    size_--;
    return iterator(prevNode, nextNode);
}
