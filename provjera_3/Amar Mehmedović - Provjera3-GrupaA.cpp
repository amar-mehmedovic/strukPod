#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

template <typename T>
class Lista {
   public:
    Lista() : head_{nullptr}, tail_{nullptr}, size_{0} {}
    size_t size() const { return size_; }
    void push_back(const T &e) {
	if (size_ == 0) {
	    head_ = tail_ = new Node{e, nullptr, nullptr};
	} else {
	    tail_->next_ = new Node{e, tail_, nullptr};
	    tail_ = tail_->next_;
	}
	++size_;
    }
    void print() {
	if (size_ == 0) {
	    return;
	} else {
	    auto temp = head_;
	    while (temp != nullptr) {
		std::cout << temp->data_ << " ";
		temp = temp->next_;
	    }
	    std::cout << "" << std::endl;
	}
    }

    Lista &erase_front() {
	if (size_ == 0) {
	    throw std::out_of_range("List is empty");
	}
	if (size_ == 1) {
	    delete head_;
	    head_ = tail_ = nullptr;
	} else {
	    auto temp = head_;
	    temp = temp->next_;
	    delete head_;
	    temp->prev_ = nullptr;
	    head_ = temp;
	}
	size_--;
	return *this;
    }
    void append(const Lista &other) {
	for (auto i = other.head_; i != nullptr; i = i->next_) {
	    push_back(i->data_);
	}
    }

   private:
    struct Node {
	T data_;
	Node *prev_;
	Node *next_;
    };
    Node *head_;
    Node *tail_;
    size_t size_;
};

int main() {
    Lista<int> lista, lista2;

    lista.push_back(1);
    lista.push_back(2);
    lista.push_back(3);
    lista.push_back(4);
    lista.push_back(5);
    lista.push_back(6);

    lista2.push_back(7);
    lista2.push_back(8);
    lista2.push_back(9);

    // Priprema - pogledati kod main funkcije i napraviti sve definicije
    // metoda kako bi se main program mogao kompajlirati (neka definicije budu
    // prazne)

    // Zadatak 1 - metod print treba isprintati listu u ostream objekat
    // Ispis treba biti u jednoj liniji, sa razmacima izmedu elemenata i novim
    // redom
    lista.print();

    // Zadatak 2 - implementirati metod erase_front() koji brise elemente sa
    // pocetka lista
    lista.erase_front().erase_front();
    lista.print();

    // Zadatak 3 - implementirati metod append() koji treba da nadoveze jednu
    // listu na drugu
    lista2.append(lista);
    lista2.print();

    return 0;
}
