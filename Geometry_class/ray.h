#ifndef GEOMETRY_RAY_H
#define GEOMETRY_RAY_H
#include "point.h"
#include "IShape.h"
namespace geometry {
class Ray : public IShape {
 public:
  Point first_;
  Point second_;
  Ray(const Point &first, const Point &second) : first_(first), second_(second) {
  }
  Ray() : first_(Point()), second_(Point()) {
  }
  Ray &Move(const Vector &) override;
  bool ContainsPoint(const Point &) const override;
  bool CrossesSegment(const Segment &) const override;
  Ray *Clone() const override;
  std::string ToString() override;
};
}  // namespace geometry
#endif  // GEOMETRY_LINE_H
