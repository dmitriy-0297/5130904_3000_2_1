#include "Polygon.h"
#include <iostream>

std::istream& checkDelimiter(std::istream& in, char expectedDelimiter) {
  char c = '\0';
  if (in >> c && c != expectedDelimiter) {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  return checkDelimiter(in, dest.del);
}

std::istream& operator>>(std::istream& in, Point& dest) {
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  Point point;
  if (checkDelimiter(in, '(') && in >> point.x && checkDelimiter(in, ';') && in >> point.y && checkDelimiter(in, ')')) {
    dest = point;
  }
  else {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& operator>>(std::istream& in, Polygon& dest) {
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  Polygon polygon;
  std::size_t vertexes;
  if (!(in >> vertexes)) {
    in.setstate(std::ios::failbit);
    return in;
  }

  if (vertexes < 3) {
    in.setstate(std::ios::failbit);
    return in;
  }

  polygon.points.reserve(vertexes);
  Point point;
  for (std::size_t i = 0; i < vertexes; ++i) {
    if (in >> point) {
      polygon.points.push_back(point);
    }
    else {
      in.setstate(std::ios::failbit);
      break;
    }
  }

  if (in.good() && polygon.points.size() == vertexes) {
    dest = polygon;
  }
  else {
    in.setstate(std::ios::failbit);
  }
  return in;
}
