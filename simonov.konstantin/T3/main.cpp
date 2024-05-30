#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <exception>
#include <string>
#include <sstream>
#include <iterator>
#include <iomanip>
#include "Comands.h"


const std::string INVALID_COMAND = "<INVALID COMMAND>";

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Try again incorrect usage\n";
    std::cerr << "Usage: program_name <filename>" << "\n";
    return EXIT_FAILURE;
  }
  std::string fileName = argv[1];
  std::ifstream file(fileName);
  if (!file)
  {
    std::cerr << "I can`t open file\n";
    return EXIT_FAILURE;
  }

  std::cout << std::setprecision(1) << std::fixed;
  std::vector<simonov::Polygon> vec;
  while (!file.eof())
  {
    std::copy(
      std::istream_iterator<simonov::Polygon>(file),
      std::istream_iterator<simonov::Polygon>(),
      std::back_inserter(vec)
    );
    if (!file.eof() && file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  while (!std::cin.eof())
  {
    std::cin.clear();
    std::string comand;
    std::cin >> comand;
    try
    {
      if (comand == "AREA")
        area(vec);
      else if (comand == "MIN")
        min(vec);
      else if (comand == "MAX")
        max(vec);
      else if (comand == "COUNT")
        count(vec);
      else if (comand == "ECHO")
        echo(vec);
      else if (comand == "RIGHTSHAPES")
        rightShapes(vec);
      else if (!std::cin.eof())
      {
        throw INVALID_COMAND;
      }
    }
    catch (const std::string ex)
    {
      std::cout << ex << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}
