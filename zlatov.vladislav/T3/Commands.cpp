#include "Commands.h"
#include <map>
#include <algorithm>
#include <iostream>
#include <functional>
#include <numeric>
#include <iomanip>
#include <string>
#include <cmath>

void zlatov::area(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in)
{
  std::map<std::string, std::function<void(const std::vector<Polygon>& polygon, std::ostream& out)>> areas;
  areas["EVEN"] = areaEvenPolygons;
  areas["ODD"] = areaOddPolygons;
  areas["MEAN"] = areaAverage;
  auto outInvalid = std::bind(outputMessage, std::placeholders::_1, "<INVALID COMMAND>\n");
  std::string parameter;
  in >> parameter;
  try
  {
    areas.at(parameter)(polygons, out);
  }
  catch (const std::out_of_range& ex)
  {
    if (std::isdigit(parameter[0]) && std::stoi(parameter) > 2)
    {
      areaByVertexCount(std::stoi(parameter), polygons, out);
    }
    else
    {
      outInvalid(out);
    }
  }
}

void zlatov::areaEvenPolygons(const std::vector<Polygon>& polygons, std::ostream& out)
{
  std::vector<Polygon> EvenPolygons_vec;
  std::copy_if(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(EvenPolygons_vec),
    [](const Polygon& polygon)
    {
      return !(polygon.points.size() % 2);
    });
  double sum = calculateTotalArea(EvenPolygons_vec);
  out << std::setprecision(1) << std::fixed << sum << '\n';
}

void zlatov::areaOddPolygons(const std::vector<Polygon>& polygons, std::ostream& out)
{
  std::vector<Polygon> OddPolygons_vec;
  std::copy_if(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(OddPolygons_vec),
    [](const Polygon& polygon)
    {
      return (polygon.points.size() % 2);
    });
  double sum = calculateTotalArea(OddPolygons_vec);
  out << std::setprecision(1) << std::fixed << sum << '\n';
}

void zlatov::areaAverage(const std::vector<Polygon>& polygons, std::ostream& out)
{
  if (polygons.empty())
  {
    throw std::out_of_range("");
  }
  double sum = calculateTotalArea(polygons);
  out << std::setprecision(1) << std::fixed << sum / polygons.size() << '\n';
}

void zlatov::areaByVertexCount(std::size_t vertexes, const std::vector<Polygon>& polygons, std::ostream& out)
{
  auto NVertexes = std::bind(std::equal_to<size_t>{}, vertexes, std::placeholders::_1);
  std::vector<Polygon> polygonsWithNVertexes;
  std::copy_if(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(polygonsWithNVertexes),
    [NVertexes](const Polygon& polygon)
    {
      return NVertexes(polygon.points.size());
    });

  double sum = calculateTotalArea(polygonsWithNVertexes);
  out << std::setprecision(1) << std::fixed << sum << '\n';
}

double zlatov::calculateTotalArea(const std::vector<Polygon>& polygons)
{
  std::vector<double> AreasOfPolygons_vec;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(AreasOfPolygons_vec),
    [](const Polygon& polygon)
    {
      return computeArea(polygon);
    });

  double sumOfAreas = std::accumulate(
    AreasOfPolygons_vec.begin(),
    AreasOfPolygons_vec.end(),
    0,
    std::bind(std::plus<double>{}, std::placeholders::_1, std::placeholders::_2));
  return sumOfAreas;
}

double zlatov::computeArea(const Polygon& polygon)
{
  std::vector<double> sumOfCoords_vec;
  std::transform(
    polygon.points.begin(),
    std::prev(polygon.points.end()),
    std::next(polygon.points.begin()),
    std::back_inserter(sumOfCoords_vec),
    [](const Point& a, const Point& b)
    {
      return a.x * b.y;
    });

  double sum = std::accumulate(
    sumOfCoords_vec.begin(),
    sumOfCoords_vec.end(),
    0,
    std::bind(std::plus<double>{}, std::placeholders::_1, std::placeholders::_2));

  std::vector<double> diffOfCoords_vec;
  std::transform(
    polygon.points.begin(),
    std::prev(polygon.points.end()),
    std::next(polygon.points.begin()),
    std::back_inserter(diffOfCoords_vec),
    [](const Point& a, const Point& b)
    {
      return a.y * b.x;
    });

  double diff = std::accumulate(
    diffOfCoords_vec.begin(),
    diffOfCoords_vec.end(),
    0,
    std::bind(std::plus<double>{}, std::placeholders::_1, std::placeholders::_2));

  return 0.5 * std::abs(sum + polygon.points.back().x * polygon.points.front().y - diff - polygon.points.front().x * polygon.points.back().y);
}

void zlatov::max(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in)
{
  std::map<std::string, std::function<void(const std::vector<Polygon>& polygons, std::ostream& out)>> maxes;
  maxes["AREA"] = maxAreaPolygon;
  maxes["VERTEXES"] = maxVertexCountPolygon;
  auto outInvalid = std::bind(outputMessage, std::placeholders::_1, "<INVALID COMMAND>\n");
  std::string parameter;
  in >> parameter;
  try
  {
    maxes.at(parameter)(polygons, out);
  }
  catch (const std::out_of_range& ex)
  {
    outInvalid(out);
  }
}

void zlatov::maxAreaPolygon(const std::vector<Polygon>& polygons, std::ostream& out)
{
  std::vector<double> areasOfPolygons_vec;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(areasOfPolygons_vec),
    [](const Polygon& polygon)
    {
      return computeArea(polygon);
    });
  if (areasOfPolygons_vec.empty())
  {
    throw std::out_of_range("");
  }
  std::sort(areasOfPolygons_vec.begin(), areasOfPolygons_vec.end());
  out << std::setprecision(1) << std::fixed << areasOfPolygons_vec.back() << '\n';
}

void zlatov::maxVertexCountPolygon(const std::vector<Polygon>& polygons, std::ostream& out)
{
  std::vector<std::size_t> vertexesOfPolygons_vec;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(vertexesOfPolygons_vec),
    [](const Polygon& polygon)
    {
      return polygon.points.size();
    });
  if (vertexesOfPolygons_vec.empty())
  {
    throw std::out_of_range("");
  }
  std::sort(vertexesOfPolygons_vec.begin(), vertexesOfPolygons_vec.end());
  out << vertexesOfPolygons_vec.back() << '\n';
}

void zlatov::min(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in)
{
  std::map<std::string, std::function<void(const std::vector<Polygon>& polygons, std::ostream& out)>> mines;
  mines["AREA"] = minAreaPolygon;
  mines["VERTEXES"] = minVertexCountPolygon;
  auto outInvalid = std::bind(outputMessage, std::placeholders::_1, "<INVALID COMMAND>\n");
  std::string parameter;
  in >> parameter;
  try
  {
    mines.at(parameter)(polygons, out);
  }
  catch (const std::out_of_range& ex)
  {
    outInvalid(out);
  }
}

void zlatov::minAreaPolygon(const std::vector<Polygon>& polygons, std::ostream& out)
{
  std::vector<double> areasOfPolygons_vec;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(areasOfPolygons_vec),
    [](const Polygon& polygon)
    {
      return computeArea(polygon);
    });
  if (areasOfPolygons_vec.empty())
  {
    throw std::out_of_range("");
  }
  std::sort(areasOfPolygons_vec.begin(), areasOfPolygons_vec.end());
  out << std::setprecision(1) << std::fixed << areasOfPolygons_vec.front() << '\n';
}

void zlatov::minVertexCountPolygon(const std::vector<Polygon>& polygons, std::ostream& out)
{
  std::vector<std::size_t> vertexesOfPolygons_vec;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(vertexesOfPolygons_vec),
    [](const Polygon& polygon)
    {
      return polygon.points.size();
    });
  if (vertexesOfPolygons_vec.empty())
  {
    throw std::out_of_range("");
  }
  std::sort(vertexesOfPolygons_vec.begin(), vertexesOfPolygons_vec.end());
  out << vertexesOfPolygons_vec.front() << '\n';
}

void zlatov::count(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in)
{
  std::map<std::string, std::function<void(const std::vector<Polygon>& polygons, std::ostream& out)>> counts;
  counts["EVEN"] = countEvenPolygons;
  counts["ODD"] = countOddPolygons;
  auto outInvalid = std::bind(outputMessage, std::placeholders::_1, "<INVALID COMMAND>\n");
  std::string parameter;
  in >> parameter;
  try
  {
    counts.at(parameter)(polygons, out);
  }
  catch (const std::out_of_range& ex)
  {
    if (std::isdigit(parameter[0]) && std::stoi(parameter) > 2)
    {
      countPolygonsByVertex(std::stoi(parameter), polygons, out);
    }
    else
    {
      outInvalid(out);
    }
  }
}

void zlatov::countEvenPolygons(const std::vector<Polygon>& polygons, std::ostream& out)
{
  std::vector<std::size_t> EvenPolygons_vec;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(EvenPolygons_vec),
    [](const Polygon& polygon)
    {
      return !(polygon.points.size() % 2);
    });
  std::size_t EvenNum = std::accumulate(
    EvenPolygons_vec.begin(),
    EvenPolygons_vec.end(),
    0,
    std::bind(std::plus<std::size_t>{}, std::placeholders::_1, std::placeholders::_2));
  out << EvenNum << '\n';
}

void zlatov::countOddPolygons(const std::vector<Polygon>& polygons, std::ostream& out)
{
  std::vector<std::size_t> OddPolygons_vec;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(OddPolygons_vec),
    [](const Polygon& polygon)
    {
      return (polygon.points.size() % 2);
    });
  std::size_t OddNum = std::accumulate(
    OddPolygons_vec.begin(),
    OddPolygons_vec.end(),
    0,
    std::bind(std::plus<std::size_t>{}, std::placeholders::_1, std::placeholders::_2));
  out << OddNum << '\n';
}

void zlatov::countPolygonsByVertex(std::size_t vertexes, const std::vector<Polygon>& polygons, std::ostream& out)
{
  std::vector<std::size_t> NVertexesPolygons_vec;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(NVertexesPolygons_vec),
    [vertexes](const Polygon& polygon)
    {
      return polygon.points.size() == vertexes;
    });
  std::size_t NVertexesNum = std::accumulate(
    NVertexesPolygons_vec.begin(),
    NVertexesPolygons_vec.end(),
    0,
    std::bind(std::plus<std::size_t>{}, std::placeholders::_1, std::placeholders::_2));
  out << NVertexesNum << '\n';
}

void zlatov::perms(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in)
{
  Polygon givenPolygon;
  in >> givenPolygon;
  std::size_t givenPolygonVertexes = givenPolygon.points.size();
  auto outInvalid = std::bind(outputMessage, std::placeholders::_1, "<INVALID COMMAND>\n");
  std::vector<Polygon> nVertexes_vec;
  std::copy_if(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(nVertexes_vec),
    [givenPolygonVertexes](const Polygon& polygon)
    {
      return polygon.points.size() == givenPolygonVertexes;
    });
  if (nVertexes_vec.empty())
  {
    outInvalid(out);
  }
  else
  {
    auto comparePolygons = std::bind(arePermutations, givenPolygon, std::placeholders::_1);
    std::size_t count = std::count_if(polygons.begin(), polygons.end(), comparePolygons);
    out << count << '\n';
  }
}

bool zlatov::arePermutations(const Polygon& left, const Polygon& right)
{
  if (left.points.size() != right.points.size())
  {
    return false;
  }
  auto isPointContains = std::bind(verifyPoints, left, std::placeholders::_1);
  std::size_t countPointsIn = std::count_if(right.points.begin(), right.points.end(), isPointContains);
  return left.points.size() == countPointsIn;
}

bool zlatov::verifyPoints(const Polygon& polygon, const Point& point)
{
  return std::find_if(polygon.points.begin(), polygon.points.end(), [point](const Point& pointToCompare)
    { return (pointToCompare.x == point.x && pointToCompare.y == point.y); }) != polygon.points.end();
}

void zlatov::rightshapes(const std::vector<Polygon>& polygons, std::ostream& out)
{
  std::size_t count = std::count_if(polygons.begin(), polygons.end(), isRightAngle);
  out << count << '\n';
}

bool zlatov::isRightAngle(const Polygon& polygon)
{
  std::vector<Point> points_vec;
  auto makeVector = std::bind(createVector, std::placeholders::_1, std::placeholders::_2);
  std::transform(
    polygon.points.begin(),
    std::prev(polygon.points.end()),
    std::next(polygon.points.begin()),
    std::back_inserter(points_vec),
    makeVector);
  points_vec.push_back(makeVector(polygon.points.back(), polygon.points.front()));
  std::vector<double> cosOfVectors;
  auto getCos = std::bind(calculateCosine, std::placeholders::_1, std::placeholders::_2);
  std::transform(
    points_vec.begin(),
    std::prev(points_vec.end()),
    std::next(points_vec.begin()),
    std::back_inserter(cosOfVectors),
    getCos);
  cosOfVectors.push_back(getCos(points_vec.back(), points_vec.front()));
  return std::find_if(cosOfVectors.begin(), cosOfVectors.end(), [](const double& cos)
    { return cos == 0; }) != cosOfVectors.end();
}

zlatov::Point zlatov::createVector(const Point& firstPoint, const Point& secondPoint)
{
  return zlatov::Point{ secondPoint.x - firstPoint.x, secondPoint.y - firstPoint.y };
}

double zlatov::calculateCosine(const Point& firstPoint, const Point& secondPoint)
{
  double topExpr = (firstPoint.x * secondPoint.x + firstPoint.y * secondPoint.y);
  double botExprFirst = std::sqrt(std::pow(firstPoint.x, 2) + std::pow(firstPoint.y, 2));
  double botExprSecond = std::sqrt(std::pow(secondPoint.x, 2) + std::pow(secondPoint.y, 2));
  return topExpr / (botExprFirst * botExprSecond);
}

void zlatov::outputMessage(std::ostream& out, const std::string& message)
{
  out << message;
}
