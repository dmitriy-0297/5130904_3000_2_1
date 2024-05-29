#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <exception>
#include <string>
#include <sstream>
#include <iterator>
#include "Comands.h"


const std::string INVALID_COMAND = "<INVALID COMMAND>";

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Try again incorrect usage" << "\n";
    std::cout << "Usage: program_name <filename>" << "\n";
    return EXIT_FAILURE;
  }
  std::string fileName = argv[1];
  std::ifstream file(fileName);
  if (!file)
  {
    std::cerr << "I can`t open file" << "\n";
    return EXIT_FAILURE;
  }
  std::vector<simonov::Polygon> value;
  while (!file.eof())
  {
    std::transform(std::istream_iterator<simonov::Polygon>(file),
      std::istream_iterator<simonov::Polygon>(),
      std::back_inserter(value), [](const simonov::Polygon& poly)
      {
        return poly;
      });
    if (!file.eof() && file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  try
  {
    while (!std::cin.eof())
    {
      std::cin.clear();
      std::string comand1, comand2;
      std::cin >> comand1;
      if (comand1 == "ECHO")
      {
        simonov::Polygon temp;
        std::cin >> temp;
        echo(value, comand1, temp);
        continue;
      }
      else if (comand1 == "RIGHTSHAPES")
      {
        rightShapes(value, comand1);
        continue;
      }
      else
      {
        std::cin >> comand2;
      }

      try
      {
        if (comand1 == "AREA")
        {
          area(value, comand2);
        }
        else if (comand1 == "MAX")
        {
          max(value, comand2);
        }
        else if (comand1 == "MIN")
        {
          min(value, comand2);
        }
        else if (comand1 == "COUNT")
        {
          count(value, comand2);
        }
        else if (comand1 != "")
        {
          throw INVALID_COMAND;
        }
      }
      catch (const std::string ex)
      {
        std::cout << ex << "\n";
      }
    }
    return EXIT_SUCCESS;
  }
  catch (...)
  {
    std::cerr << "Wrong something?!" << "\n";
    return EXIT_FAILURE;
  }
}
