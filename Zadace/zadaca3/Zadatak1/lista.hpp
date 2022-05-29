#pragma once

#include <iostream>

template <typename T>
class mojaLista {
   public:
    mojaLista() = default;
    mojaLista(const std::initializer_list<T>& elements);
    mojaLista(const mojaLista& other);
    mojaLista(mojaLista&& other);
    mojaLista& operator=(const mojaLista& other);
    mojaLista& operator=(mojaLista&& other);
    ~mojaLista();

    void clear();
    // void push_back(const T& element);
    template <typename U>
    void push_back(U&& element);
    // void push_front(const T& element);
    template <typename U>
    void push_front(U&& element);
    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }
    void pop_front();
    void pop_back();

    // slozenost O(n)
    const T& at(size_t index) const;
    T& front();
    T& back();

    bool operator==(const mojaLista<T>& other);
    bool operator!=(const mojaLista<T>& other);

    class iterator;
    iterator begin();
    iterator end();

    void insert(iterator position, const T& element);
    // void insert(iterator position, T&& element);

    iterator erase(iterator position);

   private:
    struct Node {
	T data;
	Node* next;
    };

    Node* front_ = nullptr;
    Node* back_ = nullptr;
    size_t size_ = 0;
};

template <typename T>
mojaLista<T>::mojaLista(const std::initializer_list<T>& elements)
    : size_{elements.size()}, front_{nullptr}, back_{nullptr} {
    auto it = elements.begin();
    while (it != elements.end()) {
	push_back(*it);
	++it;
    }
}

template <typename T>
mojaLista<T>::mojaLista(const mojaLista& other) {
    auto temp = other.front_;
    while (temp != nullptr) {
	push_back(temp->data);
	temp = temp->next;
    }
}

template <typename T>
mojaLista<T>::mojaLista(mojaLista&& other)
    : front_(other.front_), back_(other.back_), size_(other.size_) {
    other.front_ = nullptr;
    other.back_ = nullptr;
    other.size_ = 0;
}

template <typename T>
mojaLista<T>& mojaLista<T>::operator=(const mojaLista& other) {
    clear();
    Node* temp = other.front_;
    while (temp != nullptr) {
	push_back(temp->data);
	temp = temp->next;
    }
    return *this;
}

template <typename T>
mojaLista<T>& mojaLista<T>::operator=(mojaLista&& other) {
    std::swap(front_, other.front_);
    std::swap(back_, other.back_);
    std::swap(size_, other.size_);
    return *this;
}

template <typename T>
mojaLista<T>::~mojaLista() {
    clear();
}

template <typename T>
void mojaLista<T>::clear() {
    while (front_ != nullptr) {
	auto temp = front_->next;
	delete front_;
	front_ = temp;
    }
    back_ = nullptr;
    size_ = 0;
}

// template <typename T>
//  void mojaLista<T>::push_back(const T& element) {
// }

// template <typename T>
//  void mojaLista<T>::push_front(const T& element) {
// }

template <typename T>
template <typename U>
void mojaLista<T>::push_back(U&& element) {
    if (!front_) {
	back_ = front_ = new Node{std::forward<U>(element), nullptr};
    } else {
	auto temp = new Node{std::forward<U>(element), nullptr};
	back_ = back_->next = temp;
    }
    ++size_;
}

template <typename T>
template <typename U>
void mojaLista<T>::push_front(U&& element) {
    // if (back_ == nullptr)
    //     push_back(element);
    // else
    //     front_ = new Node{ std::forward<U>(element), front_->next };
    // ++size_;
}

// slozenost O(n)
template <typename T>
const T& mojaLista<T>::at(size_t index) const {
    auto it = begin();
    for (int i = 0; i < index; ++i) ++it;
    return *it;
}

template <typename T>
T& mojaLista<T>::front() {
    return front_->data;
}

template <typename T>
T& mojaLista<T>::back() {
    return back_->data;
}

template <typename T>
void mojaLista<T>::pop_front() {
    auto temp = sentinel->next->next;
    delete sentinel->next;
    sentinel->next = temp;
    --size_;
}

template <typename T>
void mojaLista<T>::pop_back() {
    if (sentinel->next == sentinel) return;
    node* it = sentinel->next;
    while (it->next != sentinel) it = it->next;
    delete it;
    --size_;
}

template <typename T>
class mojaLista<T>::iterator
    : public std::iterator<std::forward_iterator_tag, T> {
   public:
    friend class mojaLista<T>;

    iterator(Node* p) : p_{p} {}

    iterator& operator++() {
	if (!p_) return *this;
	p_ = p_->next;
	return *this;
    }

    iterator operator++(int) {
	auto temp = p_;
	p_ = p_->next;
	return temp;
    }

    bool operator==(const iterator& other) { return p_ == other.p_; }
    bool operator!=(const iterator& other) { return !(p_ == other.p_); }
    T& operator*() { return p_->data; }
    T* operator->() { return p_; }

   private:
    Node* p_;
};

template <typename T>
typename mojaLista<T>::iterator mojaLista<T>::begin() {
    return front_;
}

template <typename T>
typename mojaLista<T>::iterator mojaLista<T>::end() {
    return back_;
}

// O(1)
template <typename T>
void mojaLista<T>::insert(iterator position, const T& element) {
    if (position == iterator(back_)) {
	auto temp = back_;
	push_back(element);
	// std::swap( temp -> data, back_ -> data );
    } else {
	(*position.p_).next = new Node{element, position.p_->next};
	std::swap((*position.p_).data, position.p_->next->data);
    }
    ++size_;
}

// O(1)
template <typename T>
typename mojaLista<T>::iterator mojaLista<T>::erase(iterator position) {
    auto temp = (*position.p_).next;
    std::swap((*position.p_).data, temp->data);
    (*position.p_).next = temp->next;
    delete temp;
    --size_;
    return position.p_;
}

template <typename T>
bool mojaLista<T>::operator==(const mojaLista<T>& other) {
    if (this->size_ != other.size_) return false;
    auto it1 = begin();
    auto it2 = other.begin();
    while (it1 != end()) {
	if (*it1 != *it2)
	    return false;
	else {
	    ++it1;
	    ++it2;
	}
    }
    return true;
}

template <typename T>
bool mojaLista<T>::operator!=(const mojaLista<T>& other) {
    return !(*this == other);
}
