#ifndef COMMANDS_H
#define COMMANDS_H
#include <iosfwd>
#include <vector>
#include "Polygon.h"
namespace elich
{
  using istream_t = std::istream;
  using polygons_t = std::vector< Polygon >;
  bool getArea(istream_t &, polygons_t &, std::ostream &);
  bool getMax(istream_t &, polygons_t &, std::ostream &);
  bool getMin(istream_t &, polygons_t &, std::ostream &);
  bool getCount(istream_t &, polygons_t &, std::ostream &);
  bool getEcho(istream_t &, polygons_t &, std::ostream &);
  bool getMaxSeq(istream_t &, polygons_t &, std::ostream &);
  double areaOdd(polygons_t &);
  double areaEven(polygons_t &);
  double areaMean(polygons_t &);
  double areaNum(size_t, polygons_t &);
  double getMaxArea(polygons_t &);
  size_t getMaxVertexes(polygons_t &);
  double getMinArea(polygons_t &);
  size_t getMinVertexes(polygons_t &);
  size_t countEven(polygons_t &);
  size_t countOdd(polygons_t &);
  size_t countNum(size_t, polygons_t &);
}
#endif

