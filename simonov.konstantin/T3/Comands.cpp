#include "Comands.h"
#include "Polygons.h"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <functional>
#include <numeric>

const std::string ERROR_404 = "<INVALID COMMAND>";

int stringIsInt(std::string str)
{
  char* end;
  int isInt = strtol(str.c_str(), &end, 10);
  if (*end != '\0' || end == str.c_str())
    return -1;
  return static_cast<int>(isInt);
}

void area(const std::vector<simonov::Polygon>& poly, const std::string str)
{
  int value = 0;
  int del = std::numeric_limits<int>::max();
  size_t polySize = poly.size();
  value = stringIsInt(str);

  auto sumArea = [](int delit, int rest, double start, const simonov::Polygon& elem)
    {
      double ans = start;
      return ans + (elem.points.size() % delit == static_cast<size_t>(rest) || rest == -1 ? elem.area() : 0);
    };
  if (value == -1)
  {
    if (str == "EVEN")
      std::cout << std::fixed << std::setprecision(1) << std::accumulate(poly.begin(), poly.end(), 0.0,
        std::bind(sumArea, 2, 0, std::placeholders::_1, std::placeholders::_2)) << "\n";

    else if (str == "ODD")
      std::cout << std::fixed << std::setprecision(1) << std::accumulate(poly.begin(), poly.end(), 0.0,
        std::bind(sumArea, 2, 1, std::placeholders::_1, std::placeholders::_2)) << "\n";

    else if (str == "MEAN" && poly.size() != 0)
      std::cout << std::fixed << std::setprecision(1) << std::accumulate(poly.begin(), poly.end(), 0.0,
        std::bind(sumArea, 2, -1, std::placeholders::_1, std::placeholders::_2)) / polySize << "\n";

    else
      throw ERROR_404;
  }

  else if (value > 2)
    std::cout << std::fixed << std::setprecision(1) << std::accumulate(poly.begin(), poly.end(), 0.0,
      std::bind(sumArea, del, value, std::placeholders::_1, std::placeholders::_2)) << "\n";

  else
    throw ERROR_404;
}

void min(const std::vector<simonov::Polygon>& poly, const std::string str)
{
  if (poly.empty()) throw ERROR_404;

  if (str == "AREA")
  {
    auto minArea = *std::min_element(poly.begin(), poly.end(),
      [](const simonov::Polygon& p1, const simonov::Polygon& p2)
      {
        return p1 < p2;
      });

    std::cout << std::fixed << std::setprecision(1) << minArea.area() << "\n";
  }
  else if (str == "VERTEXES")
  {
    auto minVertexes = *std::min_element(poly.begin(), poly.end(),
      [](const simonov::Polygon& p1, const simonov::Polygon& p2)
      {
        return p1.points.size() < p2.points.size();
      });

    std::cout << minVertexes.points.size() << "\n";
  }
  else
    throw ERROR_404;
}

void max(const std::vector<simonov::Polygon>& poly, const std::string str)
{
  if (poly.empty()) throw ERROR_404;

  if (str == "AREA")
  {
    auto maxArea = *std::max_element(poly.begin(), poly.end(),
      [](const simonov::Polygon& p1, const simonov::Polygon& p2)
      {
        return p1 < p2;
      });

    std::cout << std::fixed << std::setprecision(1) << maxArea.area() << "\n";
  }
  else if (str == "VERTEXES")
  {
    auto maxVertexes = *std::max_element(poly.begin(), poly.end(),
      [](const simonov::Polygon& p1, const simonov::Polygon& p2)
      {
        return p1.points.size() < p2.points.size();
      });

    std::cout << maxVertexes.points.size() << "\n";
  }
  else
    throw ERROR_404;
}


void echo(std::vector<simonov::Polygon>& data, const std::string str, const simonov::Polygon& poly)
{
  if (str == "ECHO")
  {
    if (std::cin.fail() || std::cin.get() != '\n')
      throw ERROR_404;

    std::vector<simonov::Polygon> result;
    int count = 0;
    for (const simonov::Polygon& el : data)
    {
      result.push_back(el);
      if (el == poly)
      {
        ++count;
        result.push_back(el);
      }
    }
    std::cout << count << '\n';
  }
  else
    throw ERROR_404;
}

void rightShapes(const std::vector<simonov::Polygon>& poly, const std::string str)
{
  if (str == "RIGHTSHAPES")
  {
    std::cout << std::count_if(poly.cbegin(), poly.cend(), std::bind(simonov::rightAngle, std::placeholders::_1)) << '\n';
  }
  else
    throw ERROR_404;
}

void count(const std::vector<simonov::Polygon>& poly, const std::string str)
{
  int value = 0;
  int del = std::numeric_limits<int>::max();
  value = stringIsInt(str);
  auto calcPolygons = [](int delit, int rest, const simonov::Polygon& elem)
    {
      return (elem.points.size() % delit == static_cast<size_t>(rest) || rest == -1);
    };
  if (value == -1)
  {
    if (str == "EVEN")
    {
      std::cout << std::count_if(poly.begin(), poly.end(),
        std::bind(calcPolygons, 2, 0, std::placeholders::_1)) << "\n";
    }
    else if (str == "ODD")
    {
      std::cout << std::count_if(poly.begin(), poly.end(),
        std::bind(calcPolygons, 2, 1, std::placeholders::_1)) << "\n";
    }
  }
  else if (value > 2)
  {
    std::cout << std::count_if(poly.begin(), poly.end(),
      std::bind(calcPolygons, del, value, std::placeholders::_1)) << "\n";
  }
  else
    throw ERROR_404;
}
