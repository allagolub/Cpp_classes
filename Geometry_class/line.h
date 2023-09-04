#ifndef GEOMETRY_LINE_H
#define GEOMETRY_LINE_H
#include "point.h"
#include "IShape.h"

namespace geometry {
class Line : public IShape {
 public:
  Point first_;
  Point second_;
  struct Ratio {
    int64_t a = 0;
    int64_t b = 0;
    int64_t c = 0;
  };
  Line(const Point &first, const Point &second) : first_(first), second_(second) {
  }
  Line() : first_(Point()), second_(Point()) {
  }
  Line &Move(const Vector &) override;
  bool ContainsPoint(const Point &) const override;
  bool CrossesSegment(const Segment &other) const override;
  Line *Clone() const override;
  std::string ToString() override;
  Ratio RatioLine() const;
};
}  // namespace geometry
#endif  // GEOMETRY_LINE_H
