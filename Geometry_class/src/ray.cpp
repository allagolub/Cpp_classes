#include "../point.h"
#include "../ray.h"
#include "../vector.h"
#include "../segment.h"
#include "../IShape.h"
#include "string"
namespace geometry {
Ray& Ray::Move(const Vector& other) {
  first_.Move(other);
  second_.Move(other);
  return *this;
}
std::string Ray::ToString() {
  return "Ray(" + first_.ToString() + ", " + "Vector(" + std::to_string((second_ - first_).x_) + ", " +
         std::to_string((second_ - first_).y_) + "))";
}
Ray* Ray::Clone() const {
  auto copy = new Ray(first_, second_);
  return copy;
}
bool Ray::ContainsPoint(const Point& other) const {
  Vector tmp_ac = first_ - second_;
  Vector tmp_ab = first_ - other;
  return ((VectorProd(tmp_ac, tmp_ab) == 0) && (ScalarProd(tmp_ac, tmp_ab) >= 0));
}
bool Ray::CrossesSegment(const Segment& other) const {
  Vector ab(second_.x_ - first_.x_, second_.y_ - first_.y_);
  Vector ac(other.first_.x_ - first_.x_, other.first_.y_ - first_.y_);
  Vector ac_a(-(other.first_.x_ - first_.x_), -(other.first_.y_ - first_.y_));
  Vector ad(other.second_.x_ - second_.x_, other.second_.y_ - second_.y_);
  Vector cd(other.second_.x_ - other.first_.x_, other.second_.y_ - other.first_.y_);
  if ((first_.x_ - other.first_.x_) * (other.second_.y_ - other.first_.y_) ==
      (first_.y_ - other.first_.y_) * (other.second_.x_ - other.first_.x_)) {
    if (((first_.x_ >= other.first_.x_) && (first_.x_ <= other.second_.x_)) ||
        ((first_.x_ <= other.first_.x_) && (first_.x_ >= other.second_.x_))) {
      return true;
    }
  }
  return (VectorProd(ab, ac) * VectorProd(ab, ad) <= 0) && (VectorProd(ac_a, cd) * VectorProd(ab, cd) <= 0);
}
}  // namespace geometry