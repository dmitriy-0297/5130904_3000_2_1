#include <functional>
#include <algorithm>
#include <numeric>
#include <limits>
#include <string>

#include "Commands.h"

using namespace std::placeholders;

namespace command
{
  int is_a_num(const std::string& str)
  {
    try
    {
      return std::stoi(str);
    }
    catch (std::invalid_argument const& ex)
    {
      return -1;
    }
  }

  void area(const std::vector<salamatov::Polygon>& data)
  {
    std::string arg;
    std::cin >> arg;
    int num = is_a_num(arg);
    auto countFunc = [](double ac, const salamatov::Polygon& plg, int div, int mod)
      {
        double result = ac;
        if (div == -1)
        {
          if (static_cast<int>(plg.points.size()) == mod)
          {
            result += plg.area();
          }
        }
        else if (static_cast<int>(plg.points.size()) % div == mod || mod == -1)
        {
          result += plg.area();
        }
        return result;
      };
    if (num == -1)
    {
      if (arg == "EVEN")
      {
        std::cout << std::accumulate(data.begin(), data.end(), 0.0,
          std::bind(countFunc, _1, _2, 2, 0)) << std::endl;
      }
      else if (arg == "ODD")
      {
        std::cout << std::accumulate(data.begin(), data.end(), 0.0,
          std::bind(countFunc, _1, _2, 2, 1)) << std::endl;
      }
      else if (arg == "MEAN")
      {
        if (data.size() == 0)
        {
          throw "<INVALID COMMAND>";
        }
        std::cout << std::accumulate(data.begin(), data.end(), 0.0,
          std::bind(countFunc, _1, _2, 2, -1)) / data.size() << std::endl;
      }
      else
      {
        throw "<INVALID COMMAND>";
      }
    }
    else if (num > 2)
    {
      std::cout << std::accumulate(data.begin(), data.end(), 0.0,
        std::bind(countFunc, _1, _2, -1, num)) << std::endl;
    }
    else
    {
      throw "<INVALID COMMAND>";
    }
  }

  void max(const std::vector<salamatov::Polygon>& data)
  {
    std::string arg;
    std::cin >> arg;
    if (data.size() == 0)
    {
      throw "<INVALID COMMAND>";
    }
    if (arg == "AREA")
    {
      std::cout << std::max_element(data.begin(), data.end())->area() << std::endl;
    }
    else if (arg == "VERTEXES")
    {
      std::vector<size_t> sizeVec(data.size());
      std::transform(data.begin(), data.end(), sizeVec.begin(),
        [](const salamatov::Polygon& plg) {return plg.points.size(); });
      std::cout << *std::max_element(sizeVec.begin(), sizeVec.end()) << std::endl;
    }
    else
    {
      throw "<INVALID COMMAND>";
    }
  }

  void min(const std::vector<salamatov::Polygon>& data)
  {
    std::string arg;
    std::cin >> arg;
    if (data.size() == 0)
    {
      throw "<INVALID COMMAND>";
    }
    if (arg == "AREA")
    {
      std::cout << std::min_element(data.begin(), data.end())->area() << std::endl;
    }
    else if (arg == "VERTEXES")
    {
      std::vector<size_t> sizeVec(data.size());
      std::transform(data.begin(), data.end(), sizeVec.begin(),
        [](const salamatov::Polygon& plg) {return plg.points.size(); });
      std::cout << *std::min_element(sizeVec.begin(), sizeVec.end()) << std::endl;
    }
    else
    {
      throw "<INVALID COMMAND>";
    }
  }

  void count(const std::vector<salamatov::Polygon>& data)
  {
    std::string arg;
    std::cin >> arg;
    int num = is_a_num(arg);
    auto countFunc = [](int ac, const salamatov::Polygon& plg, int div, int mod)
      {
        int result = ac;
        if (static_cast<int>(plg.points.size()) % div == mod || mod == -1)
        {
          result += 1;
        }
        return result;
      };
    if (num == -1)
    {
      if (arg == "EVEN")
      {
        std::cout << std::accumulate(data.begin(), data.end(), 0,
          std::bind(countFunc, _1, _2, 2, 0)) << std::endl;
      }
      else if (arg == "ODD")
      {
        std::cout << std::accumulate(data.begin(), data.end(), 0,
          std::bind(countFunc, _1, _2, 2, 1)) << std::endl;
      }
      else
      {
        throw "<INVALID COMMAND>";
      }
    }
    else if (num > 2)
    {
      std::cout << std::accumulate(data.begin(), data.end(), 0,
        std::bind(countFunc, _1, _2, num, 0)) << std::endl;
    }
    else
    {
      throw "<INVALID COMMAND>";
    }
  }

  void same(std::vector<salamatov::Polygon>& data)
  {
    salamatov::Polygon target;
    std::cin >> target;

    if (!std::cin)
    {
      throw "<INVALID COMMAND>";
    }
    else
    {
      std::sort(target.points.begin(), target.points.end());
      auto countFunc = [&target](const salamatov::Polygon& plg)
        {
          return plg.is_overlay_compatible(target);
        };
      std::cout << std::count_if(data.begin(), data.end(), countFunc) << std::endl;
    }
  }

  void rmecho(std::vector<salamatov::Polygon>& data)
  {
    salamatov::Polygon target, prev;
    std::cin >> target;
    prev = data[0];
    int count = 0;
    auto removeCond = [&target, &prev, &count](const salamatov::Polygon& plg) {
      bool result = plg == prev && plg == target;
      prev = plg;
      if (result)
      {
        count++;
      }
      return result;
      };
    auto removeFunc = std::remove_if(data.begin() + 1, data.end(), removeCond);
    data.erase(removeFunc, data.end());
    std::cout << count << std::endl;
  }
}
