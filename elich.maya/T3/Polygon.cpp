#include "Polygon.h"
#include <iostream>
#include <iterator>
#include <numeric>
#include "data_struct.h"
#include "iofmtguard.h"
std::ostream & elich::operator<<(std::ostream & out, const Polygon & polygon)
{
  if (!std::ostream::sentry(out))
  {
    return out;
  }
  out << polygon.points.size() << ' ';
  std::copy(polygon.points.begin(),
   std::prev(polygon.points.end()),
   std::ostream_iterator< Point >(out, " "));
  out << *std::prev(polygon.points.end());
  return out;
}
std::istream & elich::operator>>(std::istream & in, Polygon & polygon)
{
  if (!std::istream::sentry(in))
  {
    return in;
  }
  Polygon new_polygon;
  size_t count = 0;
  in >> count;
  if (count < 3)
  {
    in.setstate(std::ios::failbit);
  }
  if (!in)
  {
    return in;
  }
  elich::iofmtguard guard(in);
  in >> std::noskipws;
  for (size_t i = 0; i < count && in; ++i)
  {
    in >> DelimeterIO{ ' ' };
    Point new_point;
    in >> new_point;
    new_polygon.points.push_back(new_point);
  }
  in >> DelimeterIO{ '\n' };
  if (in)
  {
    polygon = new_polygon;
  }
  return in;
}
bool elich::operator==(const Polygon & a, const Polygon & b)
{
  if (a.points.size() != b.points.size())
  {
    return false;
  }
  return std::equal(a.points.begin(), a.points.end(), b.points.begin());
}
double elich::getPolygonArea(const Polygon & polygon)
{
  const points_t & points = polygon.points;
  Point prev = points[points.size() - 1];
  double area = std::accumulate(points.begin(),
   points.end(),
   0.f,
   [&prev](double result, const Point & point) -> double
   {
     result += (prev.x + point.x) * (prev.y - point.y);
     prev = point;
     return result;
   });
  return std::abs(area / 2.0);
}
size_t elich::getPolygonVertexes(const Polygon & polygon)
{
  return polygon.points.size();
}

