#include <functional>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <numeric>
#include <fstream>
#include <limits>
#include <map>

#include "poly.h"

using namespace usikov;
using namespace std::placeholders;

int main( int argC, char *argV[] )
{
  if (argC != 2)
  {
    std::cerr << "Incorrect usage!" << std::endl;
    std::cout << "Usage: T02POLY <filename>" << std::endl;
    return EXIT_FAILURE;
  }

  std::string fileName = argV[1];

  std::ifstream file(fileName);

  if (!file)
  {
    std::cerr << "File not found!" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << std::setprecision(1) << std::fixed;

  std::vector<Polygon> data;

  while (!file.eof())
  {
    std::copy(std::istream_iterator<Polygon>(file),
              std::istream_iterator<Polygon>(),
              std::back_inserter(data));
    if (!file.eof() && file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  auto ifInputNumber = []
  ( const std::string &str )
  {
    char *end;
    int res = strtol(str.c_str(), &end, 10);

    if (*end != 0)
      return -1;
    return res;
  };

  auto commandArea = [&]
  ( void )
  {
    std::string arg;
    int num;

    std::cin >> arg;
    num = ifInputNumber(arg);

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
    else if (num > 0)
    {
      std::cout << std::accumulate(data.begin(), data.end(), 0.0,
                   std::bind(cntFunc, _1, _2, 0x7FFFFFFF, num)) << std::endl;
    }
    else
    {
      throw "<INVALID COMMAND>";
    }
  };

  auto commandMin = [&]
  ( void )
  {
    std::string arg;

    std::cin >> arg;

    if (arg == "AREA")
      std::cout << data.begin()->area() << std::endl;
    else if (arg == "VERTEXES")
      std::cout << data.begin()->points.size() << std::endl;
    else
      throw "<INVALID COMMAND>";
  };

  auto commandMax = [&]
  ( void )
  {
    std::string arg;

    std::cin >> arg;

    auto poly = std::max_element(data.begin(), data.end());

    if (arg == "AREA")
      std::cout << poly->area() << std::endl;
    else if (arg == "VERTEXES")
      std::cout << poly->points.size() << std::endl;
    else
      throw "<INVALID COMMAND>";
  };

  auto commandCount = [&]
  ( void )
  {
    std::string arg;
    int num;

    std::cin >> arg;
    num = ifInputNumber(arg);

    auto cntFunc = [num]
    ( int ac, const Polygon &el, int div, int rest )
    {
      if (el.points.size() % div == static_cast<size_t>(rest) || rest == -1)
        ac++;
      return ac;
    };

    if (num == -1)
    {
      if (arg == "EVEN")
      {
        std::cout << std::accumulate(data.begin(), data.end(), 0,
                     std::bind(cntFunc, _1, _2, 2, 0)) << std::endl;
      }
      else if (arg == "ODD")
      {
        std::cout << std::accumulate(data.begin(), data.end(), 0,
                     std::bind(cntFunc, _1, _2, 2, 1)) << std::endl;
      }
      else
      {
        throw "<INVALID COMMAND>";
      }
    }
    else if (num > 0)
    {
      std::cout << std::accumulate(data.begin(), data.end(), 0,
                   std::bind(cntFunc, _1, _2, 0x7FFFFFFF, num)) << std::endl;
    }
    else
    {
      throw "<INVALID COMMAND>";
    }
  };

  auto commandRmecho = [&]
  ( void )
  {
    Polygon trg, prev;

    std::cin >> trg;

    if (data.size() == 0)
      throw "<INVALID COMMAND>";

    prev = data[0];

    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
  };

  auto commandIntersect = [&]
  ( void )
  {
    Polygon trg;

    std::cin >> trg;
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      throw "<INVALID COMMAND>";
    }

    auto cntFunc = [&trg]
    ( int ac, const Polygon &poly )
    {
      return ac + poly.isIntersect(trg);
    };

    std::cout << std::accumulate(data.begin(), data.end(), 0, cntFunc) << std::endl;
  };

  try
  {
    while (!std::cin.eof())
    {
      std::string cmd;

      std::cin >> cmd;

      try
      {
        if (cmd == "AREA")
          commandArea();
        else if (cmd == "MIN")
          commandMin();
        else if (cmd == "MAX")
          commandMax();
        else if (cmd == "COUNT")
          commandCount();
        else if (cmd == "RMECHO")
          commandRmecho();
        else if (cmd == "INTERSECTIONS")
          commandIntersect();
        else if (cmd != "")
          throw "<INVALID COMMAND>";
      }
      catch ( const char *err )
      {
        std::cout << err << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    }

    return EXIT_SUCCESS;
  }
  catch (...)
  {
    std::cerr << "Smt goes wrong..." << std::endl;
    return EXIT_FAILURE;
  }
}
