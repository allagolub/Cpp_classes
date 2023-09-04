#ifndef GEOMETRY_CIRCLE_H
#define GEOMETRY_CIRCLE_H
#include "vector.h"
#include "IShape.h"
#include "segment.h"
namespace geometry {
class Circle : public IShape {
 public:
  Point center_;
  int64_t rad_ = 0;
  explicit Circle(const Point &center, const int rad) : center_(center), rad_(rad) {
  }
  Circle() = default;
  Circle &Move(const Vector &) override;
  bool ContainsPoint(const Point &) const override;
  bool CrossesSegment(const Segment &) const override;
  Circle *Clone() const override;
  std::string ToString() override;
};
}  // namespace geometry
#endif  // GEOMETRY_CIRCLE_H
