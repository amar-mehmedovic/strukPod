#include <algorithm>
#include <iostream>

namespace SP {

template <typename T>
class Vector {
   public:
    Vector() = default;
    Vector(const Vector& other)
	: capacity_(other.capacity_),
	  size_(other.size_),
	  ptr_(new T[capacity_]) {
	std::copy(other.ptr_, other.ptr_ + size_, ptr_);
    }

    Vector(Vector&& other)
	: capacity_(other.capacity_), size_(other.size_), ptr_(other.ptr_) {
	other.ptr_ = nullptr;
    }

    Vector& operator=(const Vector& other) {
	if (this != &other) {
	    capacity_ = other.capacity_;
	    size_ = other.size_;
	    delete[] ptr_;
	    ptr_ = new T[capacity_];
	    std::copy(other.ptr_, other.ptr_ + size_, ptr_);
	}
	return *this;
    }

    Vector& operator=(Vector&& other) {
	if (this != &other) {
	    capacity_ = other.capacity_;
	    size_ = other.size_;
	    delete[] ptr_;
	    ptr_ = other.ptr_;
	    other.ptr_ = nullptr;
	}
	return *this;
    }

    template <typename U>
    void push_back(U&& newElement) {
	if (size_ == capacity_) reallocate();
	ptr_[size_++] = std::forward<U>(newElement);
    }

    // Zadatak 1)
    //    Ispravno implementirati push_front metod
    //    koji ubacuje elemente na pocetak vektora
    template <typename U>
    void push_front(U&& newElement) {
	if (size_ >= capacity_) {
	    reallocate();
	}
	for (int i = size_ - 1; i >= 0; i--) {
	    ptr_[i + 1] = ptr_[i];
	}
	ptr_[0] = newElement;
	size_++;
	newElement = 0;
    }

    const T& operator[](int index) const { return ptr_[index]; }
    T& operator[](int index) { return ptr_[index]; }

    size_t size() const { return size_; }

    // Zadatak 2)
    //    Implementirati transform metod koji poziva
    //    predicate funkciju nad svakim clanom vektora
    template <typename U>
    void transform(U predicate) {
	for (int i = 0; i < size_; i++) {
	    predicate(ptr_[i]);
	}
    }

   private:
    size_t capacity_ = 8;
    size_t size_ = 0;
    T* ptr_ = new T[capacity_];

    void reallocate() {
	capacity_ *= 2;
	T* newPtr = new T[capacity_];
	std::copy(ptr_, ptr_ + size_, newPtr);
	delete[] ptr_;
	ptr_ = newPtr;
    }
};

}  // namespace SP

int main() {
    SP::Vector<int> vec, vec2, vec3;
    vec.push_back(10);
    vec.push_back(9);
    vec.push_back(12);
    vec.push_back(6);
    vec.push_back(14);
    vec.push_back(14);
    vec.push_back(30);
    vec.push_back(12);
    vec.push_back(15);
    vec.push_back(14);
    vec.push_back(1);
    vec.push_back(25);
    vec2 = vec;
    vec3 = std::move(vec);
    //  Otkomentirati ovaj dio koda nakon implementacije push_front
    //
    //  ************************************
    for (auto i = 0; i < 10000; ++i) {
	vec3.push_front(i + 100);
    }

    for (auto i = 0; i < vec3.size(); ++i) {
	std::cout << vec3[i] << std::endl;
    }
    //  ************************************

    // Zadatak 3)
    //    Pozvati transform tako da se svaki parni clan vektora
    //     `vec3` uveca za 10
    auto lambda = [](auto& a) {
	if (a % 2 == 0) {
	    a = a + 10;
	}
    };
    vec3.transform(lambda);
    // Vas kod ovdje
}
