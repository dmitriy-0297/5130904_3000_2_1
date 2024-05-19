#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <iostream>

struct Point {
  int x, y;
};

struct Polygon {
  std::vector<Point> points;
};

struct DelimiterIO {
  char del;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, Point& dest);
std::istream& operator>>(std::istream& in, Polygon& dest);

#endif // POLYGON_H
