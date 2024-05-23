#include "Structs.h"

std::istream& sevostyanova::operator>>(std::istream& input, Delimetr && del)
{
  std::istream::sentry sentry(input);
  if (!sentry)
    return input;
  char el;
  input >> el;
  if (!input || el != del.del)
    input.setstate(std::istream::failbit);
  return input;

}

std::istream & sevostyanova::operator>>(std::istream & input, Point& point)
{
  std::istream::sentry sentry(input);
  if (!sentry)
    return input;
  input >> Delimetr('(') >> point.x >> Delimetr(';') >> point.y >> Delimetr(')');
  return input;
}

std::istream& sevostyanova::operator>>(std::istream& input, Polygon& data)
{
  std::istream::sentry sentry(input);
  if (!sentry)
    return input;

  int cnt_tops;
  input >> cnt_tops;

  if (cnt_tops < 3)
  {
    input.setstate(std::istream::failbit);
    return input;
  }
  data.points.clear();
  data.points.resize(cnt_tops);
  for (auto& pnt : data.points)
    input >> pnt;
  return input;

}

std::ostream& sevostyanova::operator<<(std::ostream& output, const Point& point)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
    return output;

  output << " (" << point.x << ";" << point.y<<")";
  return output;
}

std::ostream& sevostyanova::operator<<(std::ostream& output, const Polygon& data)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
    return output;
  output << data.points.size();
  for (auto & pnt : data.points)
    output << pnt;
  return output;
}

// Ccalculating the area of a triangle using a determinant
double triangle_area(sevostyanova::Point p1, sevostyanova::Point p2, sevostyanova::Point p3)
{ return 0.5 * abs(p1.y * (p3.x - p2.x) + p2.y * (p1.x - p3.x) + p3.y * (p2.x - p1.x)); }

double sevostyanova::Polygon::area( void) const
{
  const Point pnt = points.at(0);
  Point next = points.at(1);
  auto result = [&pnt, &next](double sum, const Point& el)
    {
      sum += triangle_area(pnt, next, el);
      next = el;
      return sum;
    };
  return std::accumulate(points.begin() + 2, points.end(), 0.0, result);
}

bool sevostyanova::Polygon::operator==(Polygon& otherData)
{
  if (points.size() != otherData.points.size())
    return false;
  else
    for (int i = 0; i < points.size(); ++i)
      if (points.at(i) != otherData.points.at(i))
        return false;
  return true;
}

bool sevostyanova::Point::operator!=(Point& otherPoint)
{
  return x != otherPoint.x || y != otherPoint.y;
}
