#ifndef AR_H
#define AR_H

#include <algorithm>
#include <iostream>

template <class T>
class SharedPtr {
 private:
  struct Block {
    size_t shared_count = 0;
    size_t weak_count = 0;
    explicit Block(size_t first = 0, size_t second = 0) : shared_count(first), weak_count(second) {
    }
  };
  T* data_ = nullptr;
  Block* block_ = nullptr;

 public:
  SharedPtr(T* ptr) : data_(ptr) {  // NOLINT
    if (ptr == nullptr) {
      block_ = nullptr;
    } else {
      block_ = new Block(1, 0);
    }
  }
  SharedPtr(const SharedPtr& other) : data_(other.data_), block_(other.block_) {
    if (block_ != nullptr) {
      ++(block_->shared_count);
    }
  }
  SharedPtr& operator=(const SharedPtr& other) {
    if (this == &other) {
      return *this;
    }
    if (this != &other) {
      if (block_ != nullptr) {
        --(block_->shared_count);
        if (block_->shared_count == 0) {
          delete data_;
          if (block_->weak_count == 0) {
            delete block_;
          }
        }
      }
      data_ = other.data_;
      block_ = other.block_;
      if (block_ != nullptr) {
        ++(block_->shared_count);
      }
    }
    return *this;
  }
  SharedPtr(SharedPtr&& other) noexcept : SharedPtr() {
    Swap(other);
  }
  SharedPtr& operator=(SharedPtr&& other) noexcept {
    if (this == &other) {
      return *this;
    }
    if (this != &other) {
      if (block_ != nullptr) {
        --(block_->shared_count);
        if (block_->shared_count == 0) {
          delete data_;
          if (block_->weak_count == 0) {
            delete block_;
          }
        }
      }
    }
    data_ = other.data_;
    block_ = other.block_;
    other.block_ = nullptr;
    other.data_ = nullptr;
    return *this;
  }
  ~SharedPtr() {
    if (block_ == nullptr) {
      return;
    }
    --(block_->shared_count);
    if (block_->shared_count == 0) {
      delete data_;
      if (block_->weak_count == 0) {
        delete block_;
      }
    }
  }
  SharedPtr() = default;
  T& operator*() const {
    return *data_;
  }
  T* operator->() const {
    return data_;
  }
  T* Get() const {
    return data_;
  }
  void Reset(T* ptr = nullptr) {
    if (block_ != nullptr) {
      --(block_->shared_count);
      if (block_->shared_count == 0) {
        delete data_;
        if (block_->weak_count == 0) {
          delete block_;
        }
      }
    }
    data_ = ptr;
    block_ = nullptr;
    if (ptr != nullptr) {
      block_ = new Block(1, 0);
    }
  }
  void Swap(SharedPtr<T>& other) {
    std::swap(data_, other.data_);
    std::swap(block_, other.block_);
  }
  explicit operator bool() const {
    return (data_ != nullptr);
  }
  size_t UseCount() const {
    if (block_ == nullptr) {
      return 0;
    }
    return block_->shared_count;
  }
};
#endif