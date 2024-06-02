#include "Comands.h"
#include "Polygons.h"
#include <algorithm>
#include <string>
#include <cmath>
#include <iomanip>
#include <functional>
#include <numeric>
#include <vector>

const std::string ERROR_404 = "<INVALID COMMAND>";

void rightShapes(const std::vector<simonov::Polygon>& poly)
{
  std::cout << std::count_if(poly.cbegin(), poly.cend(), std::bind(simonov::rightAngle, std::placeholders::_1)) << '\n';
}

void count(const std::vector<simonov::Polygon>& data)
{
  std::string str;
  std::cin >> str;

  auto calcPolygons = [](const simonov::Polygon& poly, std::size_t rest, std::size_t vertexes)
    {
      return ((poly.points.size() % 2 == rest) || (rest == 2 && poly.points.size() == vertexes));
    };

  if (str == "EVEN")
    std::cout << std::count_if(data.begin(), data.end(),
      std::bind(calcPolygons, std::placeholders::_1, 0, 0)) << '\n';

  else if (str == "ODD")
    std::cout << std::count_if(data.begin(), data.end(),
      std::bind(calcPolygons, std::placeholders::_1, 1, 0)) << '\n';

  else if (std::all_of(str.begin(), str.end(), isdigit) && stoi(str) > 2)
    std::cout << std::count_if(data.begin(), data.end(),
      std::bind(calcPolygons, std::placeholders::_1, 2, stoi(str))) << '\n';

  else
    throw ERROR_404;
}

void area(const std::vector<simonov::Polygon>& vecPoly)
{
  std::string str;
  std::cin >> str;

  auto sumArea = [](double answer, const simonov::Polygon& vecPoly, std::size_t rest, std::size_t vertexes)
    {
      if ((vecPoly.points.size() % 2 == rest) || (rest == 2 && vecPoly.points.size() == vertexes) || (rest == 3))
        answer += vecPoly.area();
      return answer;
    };


  if (str == "MEAN" && vecPoly.size() != 0)
  {
    std::cout << std::accumulate(vecPoly.begin(), vecPoly.end(), 0.0,
      std::bind(sumArea, std::placeholders::_1, std::placeholders::_2, 3, 0)) / vecPoly.size() << std::endl;
  }
  else if (str == "EVEN")
  {
    std::cout << std::accumulate(vecPoly.begin(), vecPoly.end(), 0.0,
      std::bind(sumArea, std::placeholders::_1, std::placeholders::_2, 0, 0)) << '\n';
  }
  else if (str == "ODD")
  {
    std::cout << std::accumulate(vecPoly.begin(), vecPoly.end(), 0.0,
      std::bind(sumArea, std::placeholders::_1, std::placeholders::_2, 1, 0)) << '\n';
  }
  else if (std::all_of(str.begin(), str.end(), isdigit) && stoi(str) > 2)
  {
    std::cout << std::accumulate(vecPoly.begin(), vecPoly.end(), 0.0,
      std::bind(sumArea, std::placeholders::_1, std::placeholders::_2, 2, stoi(str))) << '\n';
  }
  else
  {
    throw ERROR_404;
  }
}

void echo(std::vector<simonov::Polygon>& data)
{
  simonov::Polygon poly;
  std::cin >> poly;

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
  data.resize(result.size());
  copy(result.begin(), result.end(), data.begin());
  std::cout << count << '\n';
}

void min(const std::vector<simonov::Polygon>& vecPoly)
{
  if (vecPoly.empty())
    throw ERROR_404;

  std::string str;
  std::cin >> str;

  if (str == "VERTEXES")
  {
    std::vector<std::size_t> sizes(vecPoly.size());

    std::cout << std::accumulate(vecPoly.begin() + 1, vecPoly.end(), vecPoly[0].points.size(),
      [](std::size_t min, const simonov::Polygon& poly)
      {
        return (poly.points.size() < min ? poly.points.size() : min);
      }
    ) << '\n';
  }
  else if (str == "AREA")
    std::cout << std::min_element(vecPoly.begin(), vecPoly.end())->area() << '\n';
  else
    throw ERROR_404;
}

void max(const std::vector<simonov::Polygon>& vecData)
{
  if (vecData.empty())
    throw ERROR_404;

  std::string str;
  std::cin >> str;

  if (str == "VERTEXES")
  {
    std::vector<std::size_t> sizes(vecData.size());

    std::cout << std::accumulate(vecData.begin() + 1, vecData.end(), vecData[0].points.size(),
      [](std::size_t max, const simonov::Polygon& poly)
      {
        return (poly.points.size() > max ? poly.points.size() : max);
      }
    ) << '\n';
  }
  else if (str == "AREA")
    std::cout << std::max_element(vecData.begin(), vecData.end())->area() << '\n';
  else
    throw ERROR_404;
}
