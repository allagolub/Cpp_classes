#include "../vector.h"
#include "../segment.h"
#include "../IShape.h"
#include "../ray.h"
#include "../circle.h"
#include <cmath>
#include <string>
#include <algorithm>
namespace geometry {
Circle& Circle::Move(const Vector& other) {
  center_.Move(other);
  return *this;
}
std::string Circle::ToString() {
  return "Circle(" + center_.ToString() + ", " + std::to_string(rad_) + ")";
}
Circle* Circle::Clone() const {
  auto copy = new Circle(center_, rad_);
  return copy;
}
bool Circle::ContainsPoint(const Point& other) const {
  int64_t dist = (other.x_ - center_.x_) * (other.x_ - center_.x_);
  dist += (other.y_ - center_.y_) * (other.y_ - center_.y_);
  return (dist <= rad_ * rad_);
}
int64_t LenLine(const Vector& other) {
  return (other.x_ * other.x_) + (other.y_ * other.y_);
}
bool Circle::CrossesSegment(const Segment& other) const {
  if ((ContainsPoint(other.first_) && !(ContainsPoint(other.second_))) ||
      (ContainsPoint(other.second_) && !(ContainsPoint(other.first_)))) {
    return true;
  }
  int64_t dist = 0;
  if (ScalarProd(other.second_ - other.first_, center_ - other.first_) <= 0) {
    dist = LenLine(center_ - other.first_);
  } else if (ScalarProd(other.first_ - other.second_, center_ - other.second_) <= 0) {
    dist = LenLine(center_ - other.second_);
  } else {
    dist = VectorProd(center_ - other.first_, other.second_ - other.first_) / LenLine(other.second_ - other.first_);
    dist *= VectorProd(center_ - other.first_, other.second_ - other.first_);
  }
  if (dist > rad_ * rad_) {
    return false;
  }
  Vector ab(other.first_.x_ - center_.x_, other.first_.y_ - center_.y_);
  Vector ac(other.second_.x_ - center_.x_, other.second_.y_ - center_.y_);
  int64_t len_ab = LenLine(ab);
  int64_t len_ac = LenLine(ac);
  return (len_ab >= rad_ * rad_) || (len_ac >= rad_ * rad_);
}
}  // namespace geometry