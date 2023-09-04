#include "../vector.h"
#include "../segment.h"
#include "string"
namespace geometry {
bool Point::ContainsPoint(const Point &other) const {
  return (other.x_ == x_) && (other.y_ == y_);
}
Point operator+(const Point &first, const Vector &other) {
  return Point(first.x_ + other.x_, first.y_ + other.y_);
}
Point operator-(const Point &first, const Vector &other) {
  return Point(other.x_ - first.x_, other.y_ - first.y_);
}
Vector operator-(const Point &first, const Point &other) {
  return Vector(-other.x_ + first.x_, -other.y_ + first.y_);
}
Point &Point::Move(const Vector &other) {
  *this = *this + other;
  return *this;
}
std::string Point::ToString() {
  return "Point(" + std::to_string(x_) + ", " + std::to_string(y_) + ")";
}
Point *Point::Clone() const {
  auto copy = new Point(x_, y_);
  return copy;
}
bool Point::CrossesSegment(const Segment &other) const {
  Vector tmp_ac = other.first_ - other.second_;
  Vector tmp_ab = other.first_ - *this;
  Vector tmp_ca = other.second_ - other.first_;
  Vector tmp_cb = other.second_ - *this;
  if (other.first_ == other.second_) {
    return ContainsPoint(other.first_);
  }
  bool ray_ac = ((VectorProd(tmp_ac, tmp_ab) == 0) && (ScalarProd(tmp_ac, tmp_ab) >= 0));
  bool ray_ca = ((VectorProd(tmp_ca, tmp_cb) == 0) && (ScalarProd(tmp_ca, tmp_cb) >= 0));
  return ray_ac && ray_ca;
}
bool operator==(const Point &first, const Point &other) {
  return (first.x_ == other.x_) && (other.y_ == first.y_);
}
}  // namespace geometry