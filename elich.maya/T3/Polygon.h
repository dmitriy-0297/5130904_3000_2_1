#ifndef POLYGON_H
#define POLYGON_H
#include <iosfwd>
#include <vector>
#include "Point.h"
namespace elich
{
  using points_t = std::vector< Point >;
  struct Polygon
  {
    points_t points;
  };
  std::ostream & operator<<(std::ostream &, const Polygon &);
  std::istream & operator>>(std::istream &, Polygon &);
  bool operator==(const Polygon &, const Polygon &);
  double getPolygonArea(const Polygon &);
  size_t getPolygonVertexes(const Polygon &);
}
#endif

