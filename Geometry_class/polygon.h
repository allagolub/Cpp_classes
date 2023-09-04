#ifndef GEOMETRY_Poligon_H
#define GEOMETRY_Poligon_H
#include "point.h"
#include "vector.h"
#include "IShape.h"
#include "segment.h"
#include <vector>
namespace geometry {
class Polygon : public IShape {
 public:
  std::vector<Point> points_;
  explicit Polygon(const std::vector<Point> &points) : points_(points) {
  }
  Polygon() = default;
  Polygon &Move(const Vector &) override;
  bool ContainsPoint(const Point &) const override;
  bool CrossesSegment(const Segment &) const override;
  Polygon *Clone() const override;
  std::string ToString() override;
};
}  // namespace geometry
#endif  // GEOMETRY_Poligon_H
