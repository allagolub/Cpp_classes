#ifndef UNTITLED54_VECTOR_H
#define UNTITLED54_VECTOR_H
#define VECTOR_MEMORY_IMPLEMENTED
#include <new>
#include <algorithm>
#include <initializer_list>
#include <stdexcept>

template <class T>
class Vector {
 public:
  using Iterator = T *;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ValueType = T;
  using Pointer = T *;
  using ConstPointer = const T *;
  using Reference = T &;
  using ConstReference = const T &;
  using SizeType = size_t;
  using ConstIterator = const T *;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

  Vector() : arr_(nullptr), capacity_(0), size_(0) {
  }
  Vector(size_t size, const T &value) {
    size_ = size;
    capacity_ = size;
    if (size_ == 0) {
      arr_ = nullptr;
    } else {
      size_t i = 0;
      arr_ = static_cast<T *>(operator new(sizeof(T) * size_));
      for (; i < size_; i++) {
        try {
          new (arr_ + i) T(value);
        } catch (...) {
          for (size_t j = 0; j < i; ++j) {
            (arr_ + j)->~T();
          }
          operator delete(arr_);
          arr_ = nullptr;
          size_ = 0;
          capacity_ = 0;
          throw;
        }
      }
    }
  }
  explicit Vector(size_t size) {
    size_ = size;
    capacity_ = size;
    if (size_ == 0) {
      arr_ = nullptr;
    } else {
      size_t i = 0;
      arr_ = static_cast<T *>(operator new(sizeof(T) * size_));
      for (; i < size_; i++) {
        try {
          new (arr_ + i) T();
        } catch (...) {
          for (size_t j = 0; j < i; ++j) {
            (arr_ + j)->~T();
          }
          operator delete(arr_);
          arr_ = nullptr;
          size_ = 0;
          capacity_ = 0;
          throw;
        }
      }
    }
  }
  template <class Iterator, class = std::enable_if_t<std::is_base_of_v<
                                std::forward_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>>>
  Vector(Iterator first, Iterator last) : capacity_(std::distance(first, last)), size_(capacity_) {
    if ((size_ == 0) && (capacity_ == 0)) {
      arr_ = nullptr;
    } else {
      size_t i = 0;
      arr_ = static_cast<T *>(operator new(sizeof(T) * capacity_));
      try {
        for (; i < size_; i++) {
          new (arr_ + i) T;
        }
      } catch (...) {
        for (size_t j = 0; j < i; ++j) {
          (arr_ + j)->~T();
        }
        operator delete(arr_);
        arr_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        throw;
      }
      size_t k = 0;
      for (auto it = first; it != last; it++) {
        try {
          arr_[k] = *it;
          k++;
        } catch (...) {
          for (size_t j = 0; j < size_; ++j) {
            (arr_ + j)->~T();
          }
          operator delete(arr_);
          arr_ = nullptr;
          size_ = 0;
          capacity_ = 0;
          throw;
        }
      }
    }
  }
  Vector(const std::initializer_list<T> &list) : Vector(list.begin(), list.end()) {
  }
  void PopBack() {
    (arr_ + size_ - 1)->~T();
    size_--;
  }
  Iterator begin() {  // NOLINT
    return arr_;
  }
  ConstIterator begin() const {  // NOLINT
    return arr_;
  }
  Iterator end() {  // NOLINT
    return arr_ + size_;
  }
  ConstIterator end() const {  // NOLINT
    return arr_ + size_;
  }
  ConstIterator cbegin() const {  // NOLINT
    return arr_;
  }
  ConstIterator cend() const {  // NOLINT
    return arr_ + size_;
  }
  ReverseIterator rbegin() {  // NOLINT
    return std::make_reverse_iterator(arr_ + size_);
  }
  ConstReverseIterator rbegin() const {  // NOLINT
    return std::make_reverse_iterator(arr_ + size_);
  }
  ReverseIterator rend() {  // NOLINT
    return std::make_reverse_iterator(arr_);
  }
  ConstReverseIterator rend() const {  // NOLINT
    return std::make_reverse_iterator(arr_);
  }
  ConstReverseIterator crbegin() const {  // NOLINT
    return std::make_reverse_iterator(arr_ + size_);
  }
  ConstReverseIterator crend() const {  // NOLINT
    return std::make_reverse_iterator(arr_);
  }
  ~Vector() {
    for (size_t i = 0; i < size_; ++i) {
      (arr_ + i)->~T();
    }
    operator delete(arr_);
    size_ = 0;
    capacity_ = 0;
  }
  Vector(const Vector &other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    if ((size_ == 0) && (capacity_ == 0)) {
      arr_ = nullptr;
    } else {
      arr_ = static_cast<T *>(operator new(sizeof(T) * capacity_));
      for (size_t i = 0; i < size_; i++) {
        try {
          new (arr_ + i) T(other.arr_[i]);
        } catch (...) {
          for (size_t j = 0; j < i; ++j) {
            (arr_ + j)->~T();
          }
          operator delete(arr_);
          arr_ = nullptr;
          size_ = 0;
          capacity_ = 0;
          throw;
        }
      }
    }
    if (arr_ == nullptr) {
      size_ = 0;
      capacity_ = 0;
    }
  }
  Vector &operator=(const Vector &other) {
    if (arr_ == other.arr_) {
      return *this;
    }
    if (other.arr_ == nullptr) {
      for (size_t j = 0; j < size_; ++j) {
        (arr_ + j)->~T();
      }
      operator delete(arr_);
      arr_ = nullptr;
      size_ = 0;
      capacity_ = 0;
    } else {
      auto new_arr = static_cast<T *>(operator new(sizeof(T) * other.capacity_));
      size_t i = 0;
      try {
        for (; i < other.size_; ++i) {
          new (new_arr + i) T(other.arr_[i]);
        }
      } catch (...) {
        for (size_t j = 0; j < i; ++j) {
          (new_arr + j)->~T();
        }
        operator delete(new_arr);
        throw;
      }
      for (size_t j = 0; j < size_; ++j) {
        (arr_ + j)->~T();
      }
      operator delete(arr_);
      arr_ = new_arr;
      size_ = other.size_;
      capacity_ = other.capacity_;
    }

    return (*this);
  }
  Vector(Vector &&other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    if ((size_ == 0) && (capacity_ == 0)) {
      arr_ = nullptr;
    } else {
      arr_ = other.arr_;
      other.arr_ = nullptr;
      other.size_ = 0;
      other.capacity_ = 0;
    }
  }
  Vector &operator=(Vector &&other) noexcept {
    if (this == &other) {
      return *this;
    }
    for (size_t i = 0; i < size_; ++i) {
      (arr_ + i)->~T();
    }
    if (arr_ != nullptr) {
      operator delete(arr_);
    }
    size_ = other.size_;
    capacity_ = other.capacity_;
    if ((size_ == 0) && (capacity_ == 0)) {
      arr_ = nullptr;
    } else {
      arr_ = other.arr_;
    }
    other.arr_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
    return (*this);
  }

  size_t Size() const {
    return size_;
  }
  size_t Capacity() const {
    return capacity_;
  }
  bool Empty() const {
    return size_ == 0u;
  }
  T &operator[](size_t idx) {
    return arr_[idx];
  }
  const T &operator[](size_t idx) const {
    return arr_[idx];
  }
  const T &At(size_t idx) const {
    if (idx >= size_) {
      throw std::out_of_range("out_of_range");
    }
    return arr_[idx];
  }
  T &At(size_t idx) {
    if (idx >= size_) {
      throw std::out_of_range("out_of_range");
    }
    return arr_[idx];
  }
  T &Front() {
    return arr_[0];
  }
  const T &Front() const {
    return arr_[0];
  }
  T &Back() {
    return arr_[size_ - 1];
  }
  const T &Back() const {
    return arr_[size_ - 1];
  }
  T *Data() {
    return arr_;
  }
  const T *Data() const {
    return arr_;
  }
  void Clear() {
    for (size_t j = 0; j < size_; ++j) {
      (arr_ + j)->~T();
    }
    size_ = 0;
  }

  friend bool operator==(const Vector<T> &first, const Vector<T> &second) {
    if (first.size_ == second.size_) {
      for (size_t i = 0; i < second.size_; i++) {
        if (first.arr_[i] != second.arr_[i]) {
          return false;
        }
      }
      return true;
    }
    return false;
  }
  void ShrinkToFit() {
    if ((size_ == 0) && (capacity_ == 0)) {
      return;
    }
    if ((size_ == 0) && (capacity_ != 0)) {
      capacity_ = 0;
      operator delete(arr_);
      arr_ = nullptr;
      return;
    }
    auto new_arr = static_cast<T *>(operator new(sizeof(T) * size_));
    size_t i = 0;
    for (; i < size_; i++) {
      try {
        new (new_arr + i) T(std::move(arr_[i]));
      } catch (...) {
        for (size_t j = 0; j < i; ++j) {
          (new_arr + j)->~T();
        }
        operator delete(new_arr);
        throw;
      }
    }
    for (size_t j = 0; j < size_; ++j) {
      (arr_ + j)->~T();
    }
    operator delete(arr_);
    arr_ = new_arr;
    capacity_ = size_;
  }
  friend bool operator!=(const Vector<T> &first, const Vector<T> &second) {
    return !(first == second);
  }
  friend bool operator<(const Vector<T> &first, const Vector<T> &second) {
    const size_t min_size = std::min(second.size_, first.size_);
    for (size_t i = 0; i < min_size; i++) {
      if (first.arr_[i] < second.arr_[i]) {
        return true;
      }
      if (first.arr_[i] > second.arr_[i]) {
        return false;
      }
    }
    if (min_size == 0) {
      if (first.size_ != min_size) {
        return false;
      }
      return (!((min_size == first.size_) && (second == first)));
    }
    if (second == first) {
      return false;
    }
    return !((min_size == second.size_));
  }
  friend bool operator<=(const Vector<T> &first, const Vector<T> &second) {
    return ((first < second) || (second == first));
  }
  friend bool operator>(const Vector<T> &first, const Vector<T> &second) {
    return !(first <= second);
  }
  friend bool operator>=(const Vector<T> &first, const Vector<T> &second) {
    return ((first > second) || (second == first));
  }

  void Swap(Vector<T> &other) {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(arr_, other.arr_);
  }
  void Resize(size_t n) {
    if (size_ != n) {
      if (n > capacity_) {
        auto new_arr = static_cast<T *>(operator new(sizeof(T) * n));
        size_t i = 0;
        for (; i < size_; ++i) {
          try {
            new (new_arr + i) T(std::move(arr_[i]));
          } catch (...) {
            for (size_t j = 0; j < i; ++j) {
              (new_arr + j)->~T();
            }
            operator delete(new_arr);
            throw;
          }
        }
        try {
          for (i = size_; i < n; ++i) {
            new (new_arr + i) T();
          }
        } catch (...) {
          for (size_t j = 0; j < i; ++j) {
            (new_arr + j)->~T();
          }
          operator delete(new_arr);
          throw;
        }
        for (size_t j = 0; j < size_; ++j) {
          (arr_ + j)->~T();
        }
        operator delete(arr_);
        arr_ = new_arr;
        capacity_ = n;
        size_ = n;
      } else {
        if (size_ < n) {
          size_t i = size_;
          try {
            for (; i < n; ++i) {
              new (arr_ + i) T();
            }
          } catch (...) {
            for (size_t j = 0; j < i; ++j) {
              (arr_ + j)->~T();
              throw;
            }
          }
        } else {
          for (size_t i = size_ - 1; i >= n; --i) {
            (arr_ + i)->~T();
          }
        }
      }
      size_ = n;
    }
  }
  void Resize(size_t n, const T &value) {
    if (size_ != n) {
      if (n > capacity_) {
        auto new_arr = static_cast<T *>(operator new(sizeof(T) * n));
        size_t i = 0;
        try {
          for (; i < size_; ++i) {
            new (new_arr + i) T(std::move(arr_[i]));
          }
        } catch (...) {
          for (size_t j = 0; j < i; ++j) {
            (new_arr + j)->~T();
          }
          operator delete(new_arr);
          throw;
        }
        try {
          for (i = size_; i < n; ++i) {
            new (new_arr + i) T(value);
          }
        } catch (...) {
          for (size_t j = 0; j < i; ++j) {
            (new_arr + j)->~T();
          }
          operator delete(new_arr);
          throw;
        }
        for (size_t j = 0; j < size_; ++j) {
          (arr_ + j)->~T();
        }
        operator delete(arr_);
        arr_ = new_arr;
        if (capacity_ < n) {
          capacity_ = n;
        }
        size_ = n;
      } else {
        if (size_ < n) {
          size_t i = size_;
          try {
            for (; i < n; ++i) {
              new (arr_ + i) T(value);
            }
          } catch (...) {
            for (size_t j = 0; j < i; ++j) {
              (arr_ + j)->~T();
            }
            throw;
          }
        } else {
          for (size_t i = size_ - 1; i >= n; --i) {
            (arr_ + i)->~T();
          }
        }
      }
      size_ = n;
    }
  }
  void PushBack(const T &value) {
    auto tmp = static_cast<T *>(operator new(sizeof(T)));
    try {
      new (tmp) T((value));
    } catch (...) {
      (tmp)->~T();
      operator delete(tmp);
      throw;
    }
    if ((size_ == 0) && (capacity_ == 0)) {
      Reserve(1);
    } else if (capacity_ == size_) {
      Reserve(2 * size_);
    }

    new (arr_ + size_) T(value);
    size_++;
    (tmp)->~T();
    operator delete(tmp);
  }
  void PushBack(T &&value) {
    auto tmp = static_cast<T *>(operator new(sizeof(T)));
    try {
      new (tmp) T(std::move(value));
    } catch (...) {
      (tmp)->~T();
      operator delete(tmp);
      throw;
    }
    if ((size_ == 0) && (capacity_ == 0)) {
      Reserve(1);
    } else if (capacity_ == size_) {
      Reserve(2 * size_);
    }

    new (arr_ + size_) T(std::move(*tmp));
    size_++;
    (tmp)->~T();
    operator delete(tmp);
  }
  void Reserve(size_t n) {
    if (n <= capacity_) {
      return;
    }
    auto new_arr = static_cast<T *>(operator new(sizeof(T) * n));
    size_t i = 0;
    try {
      for (; i < size_; ++i) {
        new (new_arr + i) T(std::move(arr_[i]));
      }
    } catch (...) {
      for (size_t j = 0; j < i; ++j) {
        (arr_ + j)->~T();
      }
      operator delete(arr_);
      throw;
    }
    for (size_t k = 0; k < size_; ++k) {
      (arr_ + k)->~T();
    }
    operator delete(arr_);
    arr_ = new_arr;
    capacity_ = n;
  }
  template <typename... Args>
  void EmplaceBack(Args &&... args) {
    auto tmp = static_cast<T *>(operator new(sizeof(T)));
    try {
      new (tmp) T(std::forward<Args>(args)...);
    } catch (...) {
      tmp->~T();
      operator delete(tmp);
      throw;
    }
    if ((size_ == 0) && (capacity_ == 0)) {
      Reserve(1);
    } else if (capacity_ == size_) {
      Reserve(2 * size_);
    }
    new (arr_ + size_) T(std::move(*tmp));
    size_++;
    (tmp)->~T();
    operator delete(tmp);
  }

 private:
  T *arr_;
  size_t capacity_;
  size_t size_;
};
#endif  // UNTITLED54_VECTOR_H
