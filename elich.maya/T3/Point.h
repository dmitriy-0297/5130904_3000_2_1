#ifndef POINT_H
#define POINT_H
#include <iosfwd>
namespace elich
{
  struct Point
  {
    int x, y;
  };
  bool operator==(const Point &, const Point &);
  std::ostream & operator<<(std::ostream &, const Point &);
  std::istream & operator>>(std::istream &, Point &);
}
#endif

