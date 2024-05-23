#ifndef STRUCTS_H
#define STRUCTS_H
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include<numeric>

namespace sevostyanova
{
  struct Point
  {
    int x, y;
    bool operator != (Point& otherPoint);
  };
  struct Polygon
  {
    std::vector<Point> points;
    double area( void ) const;
    bool operator == (Polygon& otherData);
  };
  struct Delimetr
  {
    char del;
    Delimetr(const char el) : del(el) {};
  };
  std::istream & operator >> (std::istream & input, Delimetr && del);
  std::istream & operator >> (std::istream & input, Point & point);
  std::istream & operator >> (std::istream & input, Polygon & data);
  std::ostream & operator << (std::ostream & output, const Point & point);
  std::ostream& operator << (std::ostream& output, const Polygon& data);
};
#endif
