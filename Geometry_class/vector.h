#ifndef GEOMETRY_VECTOR_H
#define GEOMETRY_VECTOR_H
#include <cstdint>
namespace geometry {
class Vector {
 public:
  int64_t x_;
  int64_t y_;
  explicit Vector(int64_t x, int64_t y) : x_(x), y_(y) {
  }
  friend Vector operator+(const Vector &first, const Vector &other) {
    return Vector(first.x_ + other.x_, first.y_ + other.y_);
  }
  friend Vector operator+(const Vector &other, const int64_t num);
  friend Vector operator-(const Vector &first, const Vector &other) {
    return Vector(first.x_ - other.x_, first.y_ - other.y_);
  }
  Vector operator+() const {
    return *this;
  }
  Vector operator-() const {
    Vector tmp(-x_, -y_);
    return tmp;
  }
  friend Vector operator*(const Vector first, const int64_t num) {
    Vector tmp(first.x_ * num, first.y_ * num);
    return tmp;
  }
  friend Vector operator/(const Vector first, const int64_t num) {
    Vector tmp(first.x_ / num, first.y_ / num);
    return tmp;
  }
  Vector &operator-=(const Vector &other) {
    *this = *this - other;
    return *this;
  }
  Vector &operator+=(const Vector &other) {
    *this = *this + other;
    return *this;
  }
  Vector &operator*=(const int64_t num) {
    *this = *this * num;
    return *this;
  }
  Vector &operator/=(const int64_t num) {
    *this = *this / num;
    return *this;
  }
  friend bool operator==(const Vector &first, const Vector &other) {
    return ((first.x_ == other.x_) && (first.y_ == other.y_));
  }
  friend bool operator!=(const Vector &first, const Vector &other) {
    return (!(first == other));
  }
  friend double ScalarProd(const Vector &first, const Vector &second) {
    return first.x_ * second.x_ + first.y_ * second.y_;
  }
  friend double VectorProd(const Vector &first, const Vector &second) {
    return first.x_ * second.y_ - first.y_ * second.x_;
  }
  friend Vector operator+(const Vector &other, const int64_t num) {
    Vector tmp(other.x_ + num, other.y_ + num);
    return tmp;
  }
};
}  // namespace geometry
#endif  //  GEOMETRY_VECTOR_H
