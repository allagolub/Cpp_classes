#include "../point.h"
#include "../vector.h"
#include "../line.h"
#include "../ray.h"
#include "../IShape.h"
#include "../segment.h"
namespace geometry {
Segment& Segment::Move(const Vector& other) {
  first_ = first_ + other;
  second_ = second_ + other;
  return *this;
}
std::string Segment::ToString() {
  return "Segment(" + first_.ToString() + ", " + second_.ToString() + ")";
}
Segment* Segment::Clone() const {
  auto copy = new Segment(first_, second_);
  return copy;
}
bool Segment::ContainsPoint(const Point& other) const {
  return other.CrossesSegment(*this);
}
bool Segment::CrossesSegment(const Segment& other) const {
  Line tmp_ab{first_, second_};
  Line tmp_cd{other.first_, other.second_};
  if (VectorProd((second_ - first_), (other.second_ - other.first_)) == 0) {
    return (first_.CrossesSegment(other)) || (second_.CrossesSegment(other)) || (other.first_.CrossesSegment(*this)) ||
           (other.second_.CrossesSegment(*this));
  }
  return (tmp_ab.CrossesSegment(other) && tmp_cd.CrossesSegment(*this));
}
}  // namespace geometry