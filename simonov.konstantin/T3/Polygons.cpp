#include "Polygons.h"
#include <numeric>
#include <algorithm>
bool simonov::Polygon::operator==(const Polygon& other) const
{
  if (this->points.size() != other.points.size())
  {
    return false;
  }
  for (size_t i = 0; i < this->points.size(); i++)
  {
    if (this->points[i] != other.points[i])
    {
      return false;
    }
  }
  return true;
}

bool simonov::Polygon::operator!=(const Polygon& other) const
{
  return !(*this == other);
}

bool simonov::Polygon::operator<(const Polygon& other) const
{
  return area() < other.area();
}

double simonov::Polygon::area(void) const
{
  double ans = 0.0f;
  double firstSum = 0.0f;
  double secondSum = 0.0f;

  for (size_t i = 0; i < points.size() - 1; i++)
  {
    firstSum += points[i].x * points[i + 1].y;
    secondSum += points[i + 1].x * points[i].y;
  }

  firstSum += points[points.size() - 1].x * points[0].y;
  secondSum += points[0].x * points[points.size() - 1].y;

  ans = std::abs(0.5f * (firstSum - secondSum));
  return ans;
}

bool simonov::rightAngle(const Polygon& poly)
{
  if (poly.points.size() < 3)
    throw "<INVALID COMMAND>";
  Polygon temp = poly;
  temp.points.push_back(poly.points[0]);
  temp.points.push_back(poly.points[1]);

  for (size_t i = 2; i < temp.points.size(); ++i) {
    if (temp.rightTriangle(temp.points[i], temp.points[i - 1], temp.points[i - 2])) {
      return true;
    }
  }
  return false;
}

bool simonov::Polygon::rightTriangle(const Point& p1, const Point& p2, const Point& p3) const
{
  double firstSide = p1.length(p2);
  double secondSide = p2.length(p3);
  double hypotenuse = p1.length(p3);
  double epsilon = 0.0001;

  return abs(pow(firstSide, 2) + pow(secondSide, 2) - pow(hypotenuse, 2)) < epsilon;
}
