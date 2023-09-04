#include "../point.h"
#include "../segment.h"
#include "../ray.h"
#include <cmath>
#include "../polygon.h"
namespace geometry {
Polygon& Polygon::Move(const Vector& other) {
  int64_t size = points_.size();
  for (int64_t i = 0; i < size; ++i) {
    points_[i].Move(other);
  }
  return *this;
}
std::string Polygon::ToString() {
  std::string s;
  s = "Polygon(";
  int64_t size = points_.size();
  for (int64_t i = 0; i < size; i++) {
    if (i != size - 1) {
      s += points_[i].ToString() + ", ";
    } else {
      s += points_[i].ToString();
    }
  }
  return s + ")";
}
Polygon* Polygon::Clone() const {
  auto copy = new Polygon;
  *copy = *this;
  return copy;
}
bool Polygon::ContainsPoint(const Point& other) const {
  int64_t size = points_.size();
  const int k_max_len = 1000001;
  for (int64_t i = 1; i < size; i++) {
    if (other.CrossesSegment(Segment{points_[i], points_[i - 1]})) {
      return true;
    }
  }
  if (other.CrossesSegment(Segment{points_[0], points_[size - 1]})) {
    return true;
  }
  Point add(Point(other.x_ + k_max_len, other.y_ + 1));
  Segment ab(other, add);
  int64_t count = 0;
  for (int64_t i = 1; i < size; i++) {
    if (ab.CrossesSegment(Segment{points_[i], points_[i - 1]})) {
      count++;
    }
  }
  if (ab.CrossesSegment(Segment(points_[0], points_[size - 1]))) {
    count++;
  }
  return (count % 2 == 1);
}
bool Polygon::CrossesSegment(const Segment& other) const {
  int64_t size = points_.size();
  for (int64_t i = 1; i < size; i++) {
    if (other.CrossesSegment(Segment{points_[i], points_[i - 1]})) {
      return true;
    }
  }
  return (other.CrossesSegment(Segment(points_[0], points_[size - 1])));
}
}  // namespace geometry
