﻿#include <algorithm>
#include <climits>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <stdexcept>

#include "commands.h"
#include "figures.h"
#include "io.h"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error: Expected 1 command-line argument, but got " << argc - 1 << ".\n";
    return EXIT_FAILURE;
  }
  std::string fileName = argv[1];
  std::ifstream file(fileName);
  if (!file)
  {
    std::cerr << "Error: file didn't open\n";
    return EXIT_FAILURE;
  }

  std::cout << std::setprecision(1) << std::fixed;
  std::vector< berdyanskij::Polygon > polygons;
  while (!file.eof())
  {
    std::copy(
      std::istream_iterator< berdyanskij::Polygon >(file), std::istream_iterator< berdyanskij::Polygon >(),
      std::back_inserter(polygons)
    );
    if (!file.eof() && file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > commands;
  {
    using namespace std::placeholders;
    commands["AREA"] = std::bind(berdyanskij::area, std::cref(polygons), _1, _2);
    commands["MAX"] = std::bind(berdyanskij::max, std::cref(polygons), _1, _2);
    commands["MIN"] = std::bind(berdyanskij::min, std::cref(polygons), _1, _2);
    commands["COUNT"] = std::bind(berdyanskij::count, std::cref(polygons), _1, _2);
    commands["INFRAME"] = std::bind(berdyanskij::inFrame, std::cref(polygons), _1, _2);
    commands["RMECHO"] = std::bind(berdyanskij::rmecho, std::ref(polygons), _1, _2);
  }
  std::string cmd;
  while (std::cin >> cmd)
  {
    if (std::cin.eof())
    {
      break;
    }
    try
    {
      commands.at(cmd)(std::cin, std::cout);
    }
    catch (const std::out_of_range&)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(INT_MAX, '\n');
    }
    catch (const std::invalid_argument& e)
    {
      std::cout << e.what() << '\n';
      std::cin.clear();
      std::cin.ignore(INT_MAX, '\n');
    }
  }
  return 0;
}
