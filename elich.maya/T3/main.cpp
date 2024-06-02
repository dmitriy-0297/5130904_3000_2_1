#include <iostream>
#include <fstream>
#include <functional>
#include <iterator>
#include <limits>
#include <map>
#include "Commands.h"
namespace
{
  void clearStream(std::istream & s)
  {
    s.clear();
    s.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}
int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cerr << "Incorect count of args\n";
    return 1;
  }
  std::string filename = argv[1];
  std::ifstream fin(filename);
  if (!fin.is_open())
  {
    std::cerr << "File cannot open\n";
    return 1;
  }
  elich::polygons_t polygones;
  using inPolygonIter_t = std::istream_iterator< elich::Polygon >;
  while (!fin.eof())
  {
    fin.clear();
    std::copy(inPolygonIter_t(fin), inPolygonIter_t(), std::back_inserter(polygones));
    if (!fin)
    {
      clearStream(fin);
    }
  }
  fin.close();
  using namespace std::placeholders;
  std::map< std::string, std::function< bool(elich::istream_t &) > > commands({
   { "AREA", std::bind(elich::getArea, _1, std::ref(polygones), std::ref(std::cout)) },
   { "MAX", std::bind(elich::getMax, _1, std::ref(polygones), std::ref(std::cout)) },
   { "MIN", std::bind(elich::getMin, _1, std::ref(polygones), std::ref(std::cout)) },
   { "COUNT", std::bind(elich::getCount, _1, std::ref(polygones), std::ref(std::cout)) },
   { "ECHO", std::bind(elich::getEcho, _1, std::ref(polygones), std::ref(std::cout)) },
   { "MAXSEQ", std::bind(elich::getMaxSeq, _1, std::ref(polygones), std::ref(std::cout)) },
  });
  while (!std::cin.eof())
  {
    std::cin.clear();
    std::string command_name = "";
    std::cin >> command_name;
    if (!command_name.empty())
    {
      auto command_iter = commands.find(command_name);
      if (command_iter != commands.end() && command_iter->second(std::cin))
      {
        std::cout << '\n';
      }
      else
      {
        std::cout << "<INVALID COMMAND>\n";
        if ((std::cin.fail() && !std::cin.eof()) || command_iter == commands.end())
        {
          clearStream(std::cin);
        }
      }
    }
  }
  return 0;
}

