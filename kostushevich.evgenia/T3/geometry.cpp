#include "geometry.h"

kostushevich::Triangle::Triangle(const Point &a, const Point &b, const Point &c)
{
  this->a = a;
  this->b = b;
  this->c = c;
}

double kostushevich::getDistance(const kostushevich::Point &p1, const kostushevich::Point &p2)
{
  int dx = p1.x - p2.x;
  int dy = p1.y - p2.y;
  return std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
}

double kostushevich::Triangle::getArea() const
{
  double x = getDistance(a, b);
  double y = getDistance(a, c);
  double z = getDistance(b, c);
  double p = (x + y + z) / 2;
  return std::sqrt(p * (p - x) * (p - y) * (p - z));
}

double kostushevich::Polygon::getArea() const
{
  kostushevich::Point fixed = points[0], first = points[1];

  double square = std::accumulate(
      points.begin() + 2,
      points.end(),
      0.0,
      [fixed, &first](double accumulator, kostushevich::Point second)
      {
        accumulator += Triangle(fixed, first, second).getArea();
        first = second;
        return accumulator;
      }
  );
  return square;
}

bool kostushevich::Polygon::operator<(const Polygon &other) const
{
  return getArea() < other.getArea();
}

bool kostushevich::Polygon::operator==(const Polygon &otherEl) const
{
  if (points.size() != otherEl.points.size())
  {
    return false;
  }
  for (size_t i = 0; i < this->points.size(); i++)
  {
    if (points[i] != otherEl.points[i])
    {
      return false;
    }
  }
  return true;
}

bool kostushevich::Polygon::operator!=(const Polygon &other) const
{
  return !(*this == other);
}

bool kostushevich::Point::operator==(const Point &other) const
{
  return x == other.x && y == other.y;
}

bool kostushevich::Point::operator!=(const Point &other) const
{
  return !(*this == other);
}
