#include <algorithm>
#include <numeric>

#include "poly.h"

bool usikov::Polygon::operator ==( const Polygon &other ) const
{
  if (points.size() != other.points.size())
    return false;

  for (size_t i = 0; i < points.size(); i++)
  {
    if (points[i] != other.points[i])
      return false;
  }
  return true;
}

bool usikov::Polygon::operator !=( const Polygon &other ) const
{
  return !(*this == other);
}

bool usikov::Polygon::operator <( const Polygon &other ) const
{
  if (points.size() < other.points.size())
    return true;
  if (points.size() > other.points.size())
    return false;
  return area() < other.area();
}

bool usikov::Segment::isIntersect( const Segment &other ) const
{
  int
    a11 = end.x - start.x,
    a12 = other.start.x - other.end.x,
    a21 = end.y - start.y,
    a22 = other.start.y - other.end.y,
    dx = other.start.x - start.x,
    dy = other.start.y - start.y;

  if (a11 == 0 || a11 * a22 - a21 * a12 == 0)
    return false;

  double t2 = double(dy * a11 - dx * a21) / (a11 * a22 - a21 * a12);
  double t1 = double(dx - a12 * t2) / a11;

  if (t1 < 0 || t2 < 0 || t1 > 1 || t2 > 1)
    return false;

  return true;
}

double triangleArea( const usikov::Point &p1,
                     const usikov::Point &p2,
                     const usikov::Point &p3 )
{
  // Names given as names in Geron's formula so they're correct
  double
    a = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)),
    b = sqrt((p1.x - p3.x) * (p1.x - p3.x) + (p1.y - p3.y) * (p1.y - p3.y)),
    c = sqrt((p3.x - p2.x) * (p3.x - p2.x) + (p3.y - p2.y) * (p3.y - p2.y));
  double p = (a + b + c) / 2;

  return sqrt(p * (p - a) * (p - b) * (p - c));
}

std::vector<usikov::Segment> usikov::Polygon::createSegmentPool( void ) const
{
  std::vector<Segment> res(points.size());
  Point prev = points[0];

  auto segmentCreator = [&]
  ( const Point &cur )
  {
    Segment ans = {prev, cur};

    prev = cur;
    return ans;
  };

  std::transform(points.begin() + 1, points.end(), res.begin(), segmentCreator);
  res.back() = Segment({points[points.size() - 1], points[0]});

  return res;
}

bool usikov::Polygon::contains( const Point &pnt ) const
{
  std::vector<int> xArr(points.size());
  std::vector<int> yArr(points.size());

  std::transform(points.begin(), points.end(),
                 xArr.begin(), []( const Point &pnt ){ return pnt.x; });
  std::transform(points.begin(), points.end(),
                 yArr.begin(), []( const Point &pnt ){ return pnt.y; });

  int maxX = *std::max_element(xArr.begin(), xArr.end());
  int maxY = *std::max_element(yArr.begin(), yArr.end());

  Point outOfBounds = {maxX + 3, maxY + 3};
  Segment ray = {pnt, outOfBounds};
  auto sgmtPool = createSegmentPool();

  auto countIntr = [&ray]
  ( int ac, const Segment &sgmt )
  {
    return ac + sgmt.isIntersect(ray);
  };

  int res = std::accumulate(sgmtPool.begin(), sgmtPool.end(), 0, countIntr);

  return res & 1;
}

bool usikov::Polygon::isIntersect( const Polygon &other ) const
{
  auto otherSegments = other.createSegmentPool();
  auto ourSegments = createSegmentPool();

  // Could use sweepline but I forgot algorithm :((

  auto countInner = [&]
  ( int ac, const Point &pnt )
  {
    return ac + contains(pnt);
  };

  int inner = std::accumulate(other.points.begin(), other.points.end(), 0, countInner);

  if (inner != 0)
    return true;

  auto countIntrOneIter = [&]
  ( int ac, const Segment &sgmt )
  {
    auto countIntrNested = [&sgmt]
    ( int accum, const Segment &sgmtOther )
    {
      return accum + sgmt.isIntersect(sgmtOther);
    };

    return ac + std::accumulate(otherSegments.begin(), otherSegments.end(), 0, countIntrNested);
  };

  int res = std::accumulate(ourSegments.begin(), ourSegments.end(), 0, countIntrOneIter);

  return res != 0;
}

double usikov::Polygon::area( void ) const
{
  const Point p0 = points[0];
  Point prev = points[1];

  auto counter = [&p0, &prev]
  ( double ac, const Point &cur )
  {
    ac += triangleArea(p0, prev, cur);
    prev = cur;
    return ac;
  };

  return std::accumulate(points.begin() + 2, points.end(), 0.0, counter);
}