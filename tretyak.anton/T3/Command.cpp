#include <string>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iomanip>
#include "Command.h"

const std::string I_C = "<INVALID COMMAND>";

int cmd::validStringToInt(std::string str)
{
  char *end;
  int sInt = strtol(str.c_str(), &end, 10);
  if (*end != '\0' || end == str.c_str())
  {
    return -1;
  }
  return static_cast<int>(sInt);
}

void cmd::area(std::vector<tretyak::Polygon> &value, const std::string str)
{
  int data = 0;
  int maxDivisor = std::numeric_limits<int>::max();
  size_t vSize = value.size();
  data = validStringToInt(str);
  auto calcArea = [](int divisor, int remains, double initial, const tretyak::Polygon &elem)
    {
      double rez = initial;
      return rez + (elem.points.size() % divisor == static_cast<size_t>(remains) || remains == -1 ? elem.area() : 0);
    };

  if (data == -1)
  {
    if (str == "EVEN")
    {
      std::cout << std::fixed << std::setprecision(1) << std::accumulate(value.begin(), value.end(), 0.0,
                   std::bind(calcArea, 2, 0, std::placeholders::_1, std::placeholders::_2)) << "\n";
    }
    else if (str == "ODD")
    {
      
      std::cout << std::fixed << std::setprecision(1) << std::accumulate(value.begin(), value.end(), 0.0,
                   std::bind(calcArea, 2, 1, std::placeholders::_1, std::placeholders::_2)) << "\n";
    }
    else if (str == "MEAN" && value.size() != 0)
    {
      std::cout << std::fixed << std::setprecision(1) << std::accumulate(value.begin(), value.end(), 0.0,
                   std::bind(calcArea, 2, -1, std::placeholders::_1, std::placeholders::_2)) / vSize << "\n";
    }
    else
    {
      throw I_C;
    }
  }
  else if (data > 2)
  {
    std::cout << std::fixed << std::setprecision(1) << std::accumulate(value.begin(), value.end(), 0.0,
                 std::bind(calcArea, maxDivisor, data, std::placeholders::_1, std::placeholders::_2)) << "\n";
  }
  else
  {
    throw I_C;
  }
}

void cmd::max(std::vector<tretyak::Polygon> &value, const std::string str)
{
  if (value.empty())
  {
    throw I_C;
  }
  if (str == "AREA")
  {
    auto maxArea = *std::max_element(value.begin(), value.end(),
                   [](const tretyak::Polygon &p1, const tretyak::Polygon &p2)
    {
      return p1.area() < p2.area();
    });
    std::cout << maxArea.area() << "\n";
  }
  else if (str == "VERTEXES")
  {
    auto maxVertexes = *std::max_element(value.begin(), value.end(),
                       [](const tretyak::Polygon &p1, const tretyak::Polygon &p2)
      {
        return p1.points.size() < p2.points.size();
      });
    std::cout << maxVertexes.points.size() << "\n";
  }
  else
  {
    throw I_C;
  }
}

void cmd::min(std::vector<tretyak::Polygon> &value, const std::string str)
{
  if (value.empty())
  {
    throw I_C;
  }
  if (str == "AREA")
  {
    auto minArea = *std::min_element(value.begin(), value.end(),
                   [](const tretyak::Polygon &p1, const tretyak::Polygon &p2)
    {
      return p1.area() < p2.area();
    });
    std::cout << minArea.area() << "\n";
  }
  else if (str == "VERTEXES")
  {
    auto minVertexes = *std::min_element(value.begin(), value.end(),
                       [](const tretyak::Polygon &p1, const tretyak::Polygon &p2)
      {
        return p1.points.size() < p2.points.size();
      });
    std::cout << minVertexes.points.size() << "\n";
  }
  else
  {
    throw I_C;
  }
}

void cmd::count(std::vector<tretyak::Polygon> &value, const std::string str)
{
  int data = 0;
  int maxDivisor = std::numeric_limits<int>::max();
  data = validStringToInt(str);
  auto calcConcur = [](int divisor, int remains, const tretyak::Polygon &elem)
    {
      return (elem.points.size() % divisor == static_cast<size_t>(remains) || remains == -1);
    };

  if (data == -1)
  {
    if (str == "EVEN")
    {
      std::cout << std::count_if(value.begin(), value.end(),
                                 std::bind(calcConcur, 2, 0, std::placeholders::_1)) << "\n";
    }
    else if (str == "ODD")
    {
      std::cout << std::count_if(value.begin(), value.end(),
                                 std::bind(calcConcur, 2, 1, std::placeholders::_1)) << "\n";
    }
  }
  else if (data > 2)
  {
    std::cout << std::count_if(value.begin(), value.end(),
                               std::bind(calcConcur, maxDivisor, data, std::placeholders::_1)) << "\n";
  }
  else
  {
    throw I_C;
  }
}

void cmd::lessArea(std::vector<tretyak::Polygon> &value)
{
  if (value.empty())
  {
    throw I_C;
  }

  tretyak::Polygon mainEl, otherEl;
  std::cin >> mainEl;
  int prov = std::cin.get();
  for (;;)
  {
    if (prov == int('\n') || prov == std::iostream::traits_type::eof())
    {
      break;
    }
    if (!isspace(prov))
    {
      std::cin.setstate(std::ios_base::failbit);
      break;
    }
    prov = std::cin.get();
  }

  if (std::cin.fail())
  {
    std::cin.clear();
    throw I_C;
  }

  auto calcConcur = [&](const tretyak::Polygon tPolygon)
    {
      otherEl = tPolygon;
      bool rez = mainEl.area() > otherEl.area();
      return rez;
    };
    std::cout << std::count_if(value.begin(), value.end(), calcConcur) << "\n";
}

void cmd::maxSeq(std::vector<tretyak::Polygon> &value)
{
  if (value.empty())
  {
    throw I_C;
  }

  tretyak::Polygon mainEl;
  std::cin >> mainEl;
  int prov = std::cin.get();
  for (;;)
  {
    if (prov == int('\n') || prov == std::iostream::traits_type::eof())
    {
      break;
    }
    if (!isspace(prov))
    {
      std::cin.setstate(std::ios_base::failbit);
      break;
    }
    prov = std::cin.get();
  }

  if (std::cin.fail())
  {
    std::cin.clear();
    throw I_C;
  }

  int maxCount = 0;
  int currentCount = 0;

  auto counter = [&](const tretyak::Polygon tPolygon)
    {
      if (mainEl == tPolygon)
      {
        currentCount++;
      }
      else
      {
        maxCount = std::max(maxCount, currentCount);
        currentCount = 0;
        return false;
      }
      return true;
    };
  currentCount = std::count_if(value.begin(), value.end(), counter);
  maxCount = std::max(maxCount, currentCount);
  std::cout << maxCount << "\n";
}
