#include "Polygons.h"
#include <iostream>

std::istream& simonov::operator>>(std::istream& in, Vertexes&& ex)
{
  std::istream::sentry sentry(in);
  
  if (!sentry)
    return in;

  char ch;
  in >> ch;

  if (!in || ch != ex.vert)
    in.setstate(std::ios::failbit);
  
  return in;
}

std::istream& simonov::operator>>(std::istream& in, Polygon& poly)
{
  std::istream::sentry sentry(in);

  if (!sentry)
    return in;

  size_t size;

  in >> size;

  if (size < 3)
  {
    in.setstate(std::istream::failbit);
    return in;
  }

  poly.points.clear();
  poly.points.resize(size);

  for (auto& p : poly.points)
    in >> p;

  return in;
}

std::istream& simonov::operator>>(std::istream& in, Point& pnt)
{
  std::istream::sentry sentry(in);

  if (!sentry)
    return in;

  in >> Vertexes('(') >> pnt.x >> Vertexes(';') >> pnt.y >> Vertexes(')');

  return in;
}

std::ostream& simonov::operator<<(std::ostream& out, const Point& pnt)
{
  std::ostream::sentry sentry(out);

  if (!sentry)
    return out;

  out << '(' << pnt.x << ';' << pnt.y << ')';
  return out;
}

std::ostream& simonov::operator<<(std::ostream& out, Polygon& poly)
{
  std::ostream::sentry sentry(out);

  if (!sentry)
    return out;

  out << poly.points.size() << ' ';

  for (const Point& p : poly.points)
    out << p << ' ';

  return out;
}
