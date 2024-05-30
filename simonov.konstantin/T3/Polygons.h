#ifndef _POLYGONS_H
#define _POLYGONS_H
#include <vector>
#include <iostream>
#include <cmath>
namespace simonov
{
  struct Point
  {
    int x, y;

    Point(int x_ = 0, int y_ = 0) : x(x_), y(y_)
    {};
    bool operator !=(const Point& other) const
    {
      return (this->x != other.x || this->y != other.y);
    }
    double length(const Point& other) const
    {
      return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2));
    }
  };

  struct Vertexes
  {
    char vert;

    Vertexes(const char temp) : vert(temp)
    {};
  };

  struct Polygon
  {
    std::vector<Point> points;

    bool operator ==(const Polygon& other) const;
    bool operator !=(const Polygon& other) const;
    bool operator <(const Polygon& other) const;

    double area(void) const;
    bool rightTriangle(const Point& p1, const Point& p2, const Point& p3) const;
  };
  bool rightAngle(const Polygon& poly);

  std::istream& operator >> (std::istream& in, Vertexes&& ex);
  std::istream& operator >> (std::istream& in, Polygon& poly);
  std::istream& operator >> (std::istream& in, Point& pnt);
  std::ostream& operator << (std::ostream& stream, const Point& pnt);
  std::ostream& operator << (std::ostream& out, Polygon& poly);
}
#endif

