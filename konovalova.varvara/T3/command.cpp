#include <functional>
#include <algorithm>
#include <numeric>
#include <limits>

#include "command.hpp"

using namespace std::placeholders;

int command::is_a_num(const std::string& str)
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

void command::area(const std::vector<konovalova::Polygon>& data)
{
    std::string arg;
    std::cin >> arg;
    int num = is_a_num(arg);
    auto countFunc = [] (double ac, const konovalova::Polygon& plg, int div, int mod)
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

void command::max(const std::vector<konovalova::Polygon>& data)
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
        [](const konovalova::Polygon& plg){return plg.points.size();});
        std::cout << *std::max_element(sizeVec.begin(), sizeVec.end()) << std::endl;
    }
    else
    {
        throw "<INVALID COMMAND>";
    }
}

void command::min(const std::vector<konovalova::Polygon>& data)
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
        [](const konovalova::Polygon& plg){return plg.points.size();});
        std::cout << *std::min_element(sizeVec.begin(), sizeVec.end()) << std::endl;
    }
    else
    {
        throw "<INVALID COMMAND>";
    }
}

void command::count(const std::vector<konovalova::Polygon>& data)
{
    std::string arg;
    std::cin >> arg;
    int num = is_a_num(arg);
    auto countFunc = [](int ac, const konovalova::Polygon& plg, int div, int mod)
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

void command::rmecho(std::vector<konovalova::Polygon>& data)
{
    konovalova::Polygon target, prev;
    std::cin >> target;
    prev = data[0];
    int count = 0;
    auto removeCond = [&target, &prev, &count](const konovalova::Polygon& plg) {
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

void command::same(std::vector<konovalova::Polygon>& data)
{
    konovalova::Polygon target;
    std::cin >> target;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw "<INVALID COMMAND>";
    }
    else if (std::cin.get() != '\n')
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw "<INVALID COMMAND>";
    }
    else
    {
        std::sort(target.points.begin(), target.points.end());
        auto countFunc = [&target] (const konovalova::Polygon& plg)
        {
            return plg.is_overlay_compatible(target);
        };
        std::cout << std::count_if(data.begin(), data.end(), countFunc) << std::endl;
    }
}
