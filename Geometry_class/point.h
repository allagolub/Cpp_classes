#ifndef GEOMETRY_POINT1_H
#define GEOMETRY_POINT1_H
#include "vector.h"
#include "IShape.h"
namespace geometry {
class Point : public IShape {
 public:
  int64_t x_;
  int64_t y_;
  Point() = default;
  Point(const int64_t x, const int64_t y) : x_(x), y_(y) {
  }
  Point &Move(const Vector &other) override;
  bool ContainsPoint(const Point &other) const override;
  bool CrossesSegment(const Segment &other) const override;
  Point *Clone() const override;
  std::string ToString() override;
};
Point operator+(const Point &first, const Vector &other);
Point operator-(const Point &first, const Vector &other);
Vector operator-(const Point &first, const Point &other);
bool operator==(const Point &first, const Point &other);
}  // namespace geometry

#endif  // GEOMETRY_POINT_H
