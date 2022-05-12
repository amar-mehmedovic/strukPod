#include <initializer_list>
#include <iostream>
#include <iterator>
template <typename T>
class Vektor {
   public:
    // Pravilo 6torke //
    Vektor() : size_{0}, capacity_{1}, arr_{new T[capacity_]} {}
    // COPY C-TOR
    Vektor(const Vektor& other) {
	size_ = other.size_;
	capacity_ = other.capacity_;
	arr_ = new T[capacity_];
    }
    // MOVE COPY C-TOR
    Vektor(Vektor&& other) {
	size_ = other.size_;
	capacity_ = other.capacity_;
	arr_ = other.arr_;
	other.arr_ = nullptr;
	other.size_ = 0;
	other.capacity = 0;
    }
    // OPERATOR =
    Vektor& operator==(const Vektor& other) {
	if (this == &other) {
	    return *this;
	}
	size_ = other.capacity_;
	capacity_ = other.capacity_;
	delete[] arr_;
	arr_ = new T[capacity_];
	std::copy(other.arr_, other.arr_ + capacity_, arr_);
	return *this;
    }
    // MOVE OPERATOR =
    Vektor& operator==(Vektor&& other) {
	size_ = other.size_;
	capacity_ = other.capacity_;
	delete[] arr_;
	arr_ = other.arr_;
	other.arr_ = nullptr;
    }

    // DESTRUCTOR
    ~Vektor() {
	delete[] arr_;
	size_ = 0;
	capacity_ = 0;
    }
    // INITIALIZER LIST
    Vektor(const std::initializer_list<T>& lista) {
	size_ = lista.size;
	capacity_ = lista.size * 2;
	arr_ = new T[capacity_];
	std::copy(lista.begin(), lista.end(), arr_);
    }
    bool empty() { return size_ == 0; }
    size_t size() { return size_; }

    void push_back(const T& element) {
	if (size_ >= capacity_) {
	    reallocate(capacity_);
	}
	arr_[size_++];
    }

    void pop_back() {
	if (empty()) {
	    return;
	}
	arr_[size_--] = 0;
    }

    class iterator : public std::iterator<std::random_access_iterator_tag, T> {
       public:
	iterator(T* ptr = nullptr) : ptr_{ptr} {}
	T& operator*() { return *ptr_; }
	T* operator->() { return ptr_; }
	iterator operator+(int index) { return iterator(ptr_ + index); }
	iterator operator++() {
	    ptr_++;
	    return *this;
	}
	iterator operator++(int) {
	    T* temp = ptr_;
	    ptr_++;
	    return temp;
	}
	size_t operator-(iterator other) {
	    T* temp = ptr_;
	    int distance = 0;
	    while (temp != other.ptr) {
		temp--;
		distance++;
	    }
	    return distance;
	}
	~iterator() { ptr_ = nullptr; }

       private:
	T* ptr_;
    };
    iterator begin() { return iterator(arr_); }
    iterator end() { return iterator(&arr_[size_]); }
    void insert(iterator pos, T& elem) {
	if (size_ >= capacity_) {
	    reallocate(capacity_);
	}
	size_t index = pos - iterator(arr_);
	for (int i = size() - 1; i >= index; i--) {
	    arr_[i + 1] = arr_[i];
	}
	arr_[index] = elem;
    }

    iterator erase(iterator pos) {
	if (empty()) {
	    return iterator(end());
	}
	auto temp = pos;
	for (auto i = pos + 1; i != end();) {
	    *pos++ = *i++;
	}
	size_--;
	return temp;
    }

   private:
    void reallocate(size_t new_capacity) {
	new_capacity *= 2;
	auto* temp = new T[new_capacity];
	std::copy(arr_, arr_ + capacity_, temp);
	capacity_ = new_capacity;
	delete[] arr_;
	arr_ = temp;
	temp = nullptr;
    }
    size_t size_;
    size_t capacity_;
    T* arr_;
};
