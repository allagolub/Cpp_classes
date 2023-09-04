#ifndef AR_H
#define AR_H

#include <algorithm>
#include <iostream>

template <class T>
class UniquePtr {
 private:
  T* ptr_;

 public:
  explicit UniquePtr(T* ptr) : ptr_(ptr) {
  }
  UniquePtr(const UniquePtr& other) = delete;
  UniquePtr& operator=(const UniquePtr& other) = delete;
  UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
  }
  UniquePtr& operator=(UniquePtr&& other) noexcept {
    if (this != &other) {
      delete ptr_;
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
    }
    return *this;
  }
  ~UniquePtr() {
    delete ptr_;
  }
  UniquePtr() {
    ptr_ = nullptr;
  }
  T& operator*() const {
    return *ptr_;
  }
  T* operator->() const {
    return ptr_;
  }
  T* Get() const {
    return ptr_;
  }
  T* Release() {
    T* old = ptr_;
    ptr_ = nullptr;
    return old;
  }
  void Reset(T* ptr = nullptr) {
    delete ptr_;
    ptr_ = ptr;
  }
  void Swap(UniquePtr& other) {
    std::swap(ptr_, other.ptr_);
  }
  explicit operator bool() const {
    return (ptr_ != nullptr);
  }
};
#endif