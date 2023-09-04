#ifndef GEOMETRY_SEGMENT_H
#define GEOMETRY_SEGMENT_H
#include "point.h"
#include "vector.h"
#include "IShape.h"
namespace geometry {
class Segment : public IShape {
 public:
  Point first_;
  Point second_;
  explicit Segment(const Point &first, const Point &second) : first_(first), second_(second) {
  }
  Segment() : first_(Point()), second_(Point()) {
  }
  Segment &Move(const Vector &) override;
  bool ContainsPoint(const Point &) const override;
  bool CrossesSegment(const Segment &) const override;
  Segment *Clone() const override;
  std::string ToString() override;
};
}  // namespace geometry
#endif  // GEOMETRY_SEGMENT_H
