#include <functional>
#include <algorithm>
#include <numeric>

#include "command.h"

using namespace usikov;
using namespace std::placeholders;

int command::isInputNumber( const std::string &str )
{
  char *end;
  int res = strtol(str.c_str(), &end, 10);

  if (*end != 0)
    return -1;
  return res;
}

void command::area( const std::vector<Polygon> &data )
{
  std::string arg;
  int num;

  std::cin >> arg;
  num = isInputNumber(arg);

  // Lambda in lambda lmao
  auto cntFunc = [num]
  ( double ac, const Polygon &el, int div, int rest )
  {
    double res = ac;

    if (el.points.size() % div == static_cast<size_t>(rest) || rest == -1)
      res += el.area();
    return res;
  };

  if (num == -1)
  {
    if (arg == "EVEN")
    {
      std::cout << std::accumulate(data.begin(), data.end(), 0.0,
                   std::bind(cntFunc, _1, _2, 2, 0)) << std::endl;
    }
    else if (arg == "ODD")
    {
      std::cout << std::accumulate(data.begin(), data.end(), 0.0,
                   std::bind(cntFunc, _1, _2, 2, 1)) << std::endl;
    }
    else if (arg == "MEAN" && data.size() != 0)
    {
      std::cout << std::accumulate(data.begin(), data.end(), 0.0,
                   std::bind(cntFunc, _1, _2, 2, -1)) / data.size() << std::endl;
    }
    else
    {
      throw "<INVALID COMMAND>";
    }
  }
  else if (num > 2)
  {
    std::cout << std::accumulate(data.begin(), data.end(), 0.0,
                 std::bind(cntFunc, _1, _2, 0x7FFFFFFF, num)) << std::endl;
  }
  else
  {
    throw "<INVALID COMMAND>";
  }
}

void command::min( const std::vector<usikov::Polygon> &data )
{
  std::string arg;

  std::cin >> arg;

  if (data.size() == 0)
    throw "<INVALID COMMAND>";

  std::vector<size_t> sizeVec(data.size());

  std::transform(data.begin(), data.end(), sizeVec.begin(),
                 []( const Polygon &poly ) { return poly.points.size(); });
  auto poly = std::min_element(data.begin(), data.end());
  auto minSize = std::min_element(sizeVec.begin(), sizeVec.end());

  if (arg == "AREA")
    std::cout << poly->area() << std::endl;
  else if (arg == "VERTEXES")
    std::cout << *minSize << std::endl;
  else
    throw "<INVALID COMMAND>";
}

void command::max( const std::vector<usikov::Polygon> &data )
{
  std::string arg;

  std::cin >> arg;

  if (data.size() == 0)
    throw "<INVALID COMMAND>";

  std::vector<size_t> sizeVec(data.size());

  std::transform(data.begin(), data.end(), sizeVec.begin(),
                 []( const Polygon &poly ) { return poly.points.size(); });
  auto poly = std::max_element(data.begin(), data.end());
  auto maxSize = std::max_element(sizeVec.begin(), sizeVec.end());

  if (arg == "AREA")
    std::cout << poly->area() << std::endl;
  else if (arg == "VERTEXES")
    std::cout << *maxSize << std::endl;
  else
    throw "<INVALID COMMAND>";
}

void command::count( const std::vector<usikov::Polygon> &data )
{
  std::string arg;
  int num;

  std::cin >> arg;
  num = isInputNumber(arg);

  auto cntFunc = [num]
  ( const Polygon &el, int div, int rest )
  {
    return (el.points.size() % div == static_cast<size_t>(rest) || rest == -1);
  };

  if (num == -1)
  {
    if (arg == "EVEN")
    {
      std::cout << std::count_if(data.begin(), data.end(),
                                 std::bind(cntFunc, _1, 2, 0)) << std::endl;
    }
    else if (arg == "ODD")
    {
      std::cout << std::count_if(data.begin(), data.end(),
                                 std::bind(cntFunc, _1, 2, 1)) << std::endl;
    }
    else
    {
      throw "<INVALID COMMAND>";
    }
  }
  else if (num > 2)
  {
    std::cout << std::count_if(data.begin(), data.end(),
                               std::bind(cntFunc, _1, 0x7FFFFFFF, num)) << std::endl;
  }
  else
  {
    throw "<INVALID COMMAND>";
  }
}

void command::rmecho( std::vector<usikov::Polygon> &data )
{
  Polygon trg, prev;

  std::cin >> trg;

  // Final check (kind of kostyl, but sorry)
  int ch = std::cin.get();

  while (ch != int('\n') && ch != EOF)
  {
    if (!isspace(ch))
    {
      std::cin.setstate(std::istream::failbit);
      break;
    }
    ch = std::cin.get();
  }

  if (data.size() == 0)
    throw "<INVALID COMMAND>";

  prev = data[0];

  if (!std::cin)
  {
    std::cin.clear();
    throw "<INVALID COMMAND>";
  }

  auto removeCond = [&trg, &prev]
  ( const Polygon &poly )
  {
    bool res = poly == prev && poly == trg;

    prev = poly;
    return res;
  };

  auto ri = std::remove_if(data.begin() + 1, data.end(), removeCond);
  data.erase(ri, data.end());
}

void command::intersections( const std::vector<usikov::Polygon> &data )
{
  Polygon trg;

  std::cin >> trg;

  int ch = std::cin.get();

  while (ch != int('\n') && ch != EOF)
  {
    if (!isspace(ch))
    {
      std::cin.setstate(std::istream::failbit);
      break;
    }
    ch = std::cin.get();
  }

  if (!std::cin)
  {
    std::cin.clear();
    throw "<INVALID COMMAND>";
  }

  auto cntFunc = [&trg]
  ( const Polygon &poly )
  {
    return poly.isIntersect(trg);
  };

  std::cout << std::count_if(data.begin(), data.end(), cntFunc) << std::endl;
}
