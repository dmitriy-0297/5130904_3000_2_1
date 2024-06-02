#include "Point.h"
#include <iostream>
#include "data_struct.h"
bool elich::operator==(const Point & a, const Point & b)
{
  return a.x == b.x && a.y == b.y;
}
std::ostream & elich::operator<<(std::ostream & out, const Point & point)
{
  if (!std::ostream::sentry(out))
  {
    return out;
  }
  return out << '(' << point.x << ';' << point.y << ')';
}
std::istream & elich::operator>>(std::istream & in, Point & point)
{
  if (!std::istream::sentry(in))
  {
    return in;
  }
  Point new_point;
  in >> DelimeterIO{ '(' };
  in >> new_point.x >> DelimeterIO{ ';' } >> new_point.y;
  in >> DelimeterIO{ ')' };
  if (in)
  {
    point = new_point;
  }
  return in;
}

