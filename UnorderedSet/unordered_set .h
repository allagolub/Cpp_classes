#ifndef UNORDERED_SET_H
#define UNORDERED_SET_H

#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

template <class KeyT>
class UnorderedSet {
 public:
  UnorderedSet() = default;
  explicit UnorderedSet(const size_t count) : size_(0), capacity_(count) {
    arr_.resize(count);
  }

  template <class Iterator>
  UnorderedSet(const Iterator &first, const Iterator &second) {
    size_ = std::distance(first, second);
    capacity_ = std::distance(first, second);
    arr_.resize(capacity_);
    for (auto it = first; it != second; it++) {
      size_t pos = h_(*it) % capacity_;
      arr_[pos].push_back(*it);
    }
  }
  UnorderedSet(const UnorderedSet &u) : size_(u.size_), capacity_(u.capacity_) {
    arr_.resize(capacity_);
    arr_ = u.arr_;
  }
  UnorderedSet(UnorderedSet &&u) : UnorderedSet() {
    Swap(u, *this);
  }
  UnorderedSet &operator=(UnorderedSet const &u) {
    if (this != &u) {
      UnorderedSet tmp(u);
      Swap(tmp, *this);
    }
    return *this;
  }

  UnorderedSet &operator=(UnorderedSet &&other) noexcept {
    size_ = other.size_;
    capacity_ = other.capacity_;
    arr_.resize(capacity_);
    arr_ = other.arr_;
    other.size_ = 0;
    for (size_t i = 0; i < other.capacity_; i++) {
      other.arr_[i] = {};
    }
    other.capacity_ = 0;
    return *this;
  }
  friend void Swap(UnorderedSet &first, UnorderedSet &us) {
    std::swap(us.arr_, first.arr_);
    std::swap(us.size_, first.size_);
    std::swap(us.capacity_, first.capacity_);
  }
  size_t Size() const {
    return size_;
  }
  void Clear() {
    size_ = 0;
    for (size_t i = 0; i < capacity_; i++) {
      arr_[i] = {};
    }
  }
  bool Empty() const {
    return size_ == 0u;
  }
  bool Find(KeyT key) const {
    if (capacity_ == 0) {
      return false;
    }
    auto pos = h_(key) % capacity_;
    auto ind = std::find(arr_[pos].begin(), arr_[pos].end(), key);
    return (ind != arr_[pos].end());
  }
  std::pair<size_t, size_t> FindPos(KeyT key) const {
    if (capacity_ == 0) {
      return std::make_pair(size_, 0);
    }
    auto pos = h_(key) % capacity_;
    for (auto i = arr_[pos].begin(); arr_[pos].end() != i; i++) {
      auto ind = std::find(arr_[pos].begin(), arr_[pos].end(), key);
      if (ind != arr_[pos].end()) {
        return std::make_pair(pos, std::distance(arr_[pos].begin(), ind));
      }
    }
    return std::make_pair(size_, 0);
  }
  size_t BucketCount() const {
    return capacity_;
  }
  size_t BucketSize(size_t ind) const {
    if (ind >= capacity_) {
      return 0;
    }
    return arr_[ind].size();
  }
  size_t Bucket(KeyT key) const {
    return h_(key) % capacity_;
  }
  double LoadFactor() const {
    if (capacity_ * size_ == 0) {
      return 0;
    }
    return double(size_) / capacity_;
  }
  void Erase(const KeyT &elem) {
    size_t first = FindPos(elem).first;
    size_t second = FindPos(elem).second;
    auto res = arr_[first].begin();
    for (size_t i = 0; i < second; i++) {
      res++;
    }
    arr_[first].erase(res);
    size_--;
  }
  ~UnorderedSet() = default;
  void Rehash(const size_t new_bucket_count) {
    if ((new_bucket_count == capacity_) || (new_bucket_count < size_)) {
      return;
    }
    UnorderedSet<KeyT> tmp;
    tmp.size_ = size_;
    tmp.capacity_ = new_bucket_count;
    tmp.arr_.resize(tmp.capacity_);

    for (size_t i = 0; i < capacity_; ++i) {
      for (auto it = arr_[i].begin(); it != arr_[i].end(); ++it) {
        size_t pos = h_(*it) % tmp.capacity_;
        tmp.arr_[pos].push_back(*it);
      }
    }
    *this = tmp;
  }
  void Reserve(const size_t new_bucket_count) {
    if (new_bucket_count <= capacity_) {
      return;
    }
    Rehash(new_bucket_count);
  }
  void Insert(const KeyT &val) {
    std::pair<size_t, size_t> it = FindPos(val);
    if (!((it.first == size_) && (it.second == 0))) {
      return;
    }
    if ((size_ == 0) && (capacity_ == 0)) {
      Rehash(1);
    } else {
      if (capacity_ == size_) {
        Rehash(2 * capacity_);
      }
    }
    auto pos = h_(val) % capacity_;
    size_++;
    arr_[pos].push_back(val);
  }
  void Insert(const KeyT &&val) {
    std::pair<size_t, size_t> it = FindPos(val);
    if (!((it.first == size_) && (it.second == 0))) {
      return;
    }
    if ((size_ == 0) && (capacity_ == 0)) {
      Rehash(1);
    } else {
      if (capacity_ == size_) {
        Rehash(2 * capacity_);
      }
    }
    auto pos = h_(val) % capacity_;
    size_++;
    arr_[pos].push_back(std::move(val));
  }

 private:
  std::hash<KeyT> h_;
  std::vector<std::list<KeyT>> arr_ = std::vector<std::list<KeyT>>();
  size_t size_ = 0;
  size_t capacity_ = 0;
};
#endif