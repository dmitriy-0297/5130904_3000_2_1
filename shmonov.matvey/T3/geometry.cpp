#include "geometry.h"

shmonov::Triangle::Triangle(const Point &a, const Point &b, const Point &c)
{
  this->a = a;
  this->b = b;
  this->c = c;
}

shmonov::Frame shmonov::getFrame(const std::vector<Polygon> &data)
{
  if (data.size() == 0)
    throw std::runtime_error("Error: no one Polygon");

  shmonov::Point lowerLeft = data[0].points[0];
  shmonov::Point upperRight = data[0].points[0];
  for (const shmonov::Polygon &poly : data)
  {
    for (const shmonov::Point &p : poly.points)
    {
      if (p.x < lowerLeft.x)
        lowerLeft.x = p.x;
      if (p.x > upperRight.x)
        upperRight.x = p.x;
      if (p.y < lowerLeft.y)
        lowerLeft.y = p.y;
      if (p.y > upperRight.y)
        upperRight.y = p.y;
    }
  }
  return shmonov::Frame(lowerLeft, upperRight);
}

double shmonov::getDistance(const shmonov::Point &p1, const shmonov::Point &p2)
{
  int dx = p1.x - p2.x;
  int dy = p1.y - p2.y;
  return std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
}

double shmonov::Triangle::getArea() const
{
  double x = getDistance(a, b);
  double y = getDistance(a, c);
  double z = getDistance(b, c);
  double p = (x + y + z) / 2;
  return std::sqrt(p * (p - x) * (p - y) * (p - z));
}

double shmonov::Polygon::getArea() const
{
  shmonov::Point fixed = points[0], first = points[1];

  double square = std::accumulate(
      points.begin() + 2,
      points.end(),
      0.0,
      [fixed, &first](double accumulator, shmonov::Point second)
      {
        accumulator += Triangle(fixed, first, second).getArea();
        first = second;
        return accumulator;
      }
  );
  return square;
}

bool shmonov::Polygon::operator<(const Polygon &other) const
{
  return getArea() < other.getArea();
}

bool shmonov::Polygon::operator==(const Polygon &other) const
{
  if (points.size() == other.points.size())
  {
    for (std::size_t i = 0; i < points.size(); ++i)
    {
      if (points[i] != other.points[i])
        return false;
    }
    return true;
  }
  return false;
}

bool shmonov::Polygon::operator!=(const Polygon &other) const
{
  return !(*this == other);
}

bool shmonov::Point::operator==(const Point &other) const
{
  return x == other.x && y == other.y;
}

bool shmonov::Point::operator!=(const Point &other) const
{
  return !(*this == other);
}

shmonov::Frame::Frame(const Point &lowerLeft, const Point &upperRight)
{
  if (lowerLeft.x > upperRight.x || lowerLeft.y > upperRight.y)
    throw std::invalid_argument("Invalid frame");

  this->lowerLeft = lowerLeft;
  this->upperRight = upperRight;
}

bool shmonov::Frame::containsPoint(const Point &p) const
{
  return p.x >= lowerLeft.x && p.x <= upperRight.x && p.y >= lowerLeft.y && p.y <= upperRight.y;
}

bool shmonov::Frame::containsPolygon(const Polygon &poly) const
{
  return std::all_of(poly.points.begin(), poly.points.end(),
                     [this](const Point &p) { return containsPoint(p); });
}
