#include "../point.h"
#include "../line.h"
#include "../vector.h"
#include "../segment.h"
#include "../IShape.h"
#include "string"
namespace geometry {
Line& Line::Move(const Vector& other) {
  first_.Move(other);
  second_.Move(other);
  return *this;
}
std::string Line::ToString() {
  return "Line(" + std::to_string(RatioLine().a) + ", " + std::to_string(RatioLine().b) + ", " +
         std::to_string(RatioLine().c) + ")";
}
Line* Line::Clone() const {
  auto copy = new Line(first_, second_);
  return copy;
}
bool Line::ContainsPoint(const Point& other) const {
  return ((other.x_ * RatioLine().a + other.y_ * RatioLine().b + RatioLine().c == 0));
}
bool Line::CrossesSegment(const Segment& other) const {
  Vector tmp_ab(second_.x_ - first_.x_, second_.y_ - first_.y_);
  Vector tmp_ad(other.first_.x_ - first_.x_, other.first_.y_ - first_.y_);
  Vector tmp_ac(other.second_.x_ - first_.x_, other.second_.y_ - first_.y_);
  if ((*this).ContainsPoint(other.first_) || (*this).ContainsPoint(other.second_)) {
    return true;
  }
  return ((VectorProd(tmp_ab, tmp_ad) * VectorProd(tmp_ab, tmp_ac) < 0));
}
Line::Ratio Line::RatioLine() const {
  Vector tmp = second_ - first_;
  Ratio rt;
  rt.b = -tmp.x_;
  rt.a = tmp.y_;
  rt.c = -rt.a * first_.x_ - rt.b * first_.y_;
  return rt;
}
}  // namespace geometry