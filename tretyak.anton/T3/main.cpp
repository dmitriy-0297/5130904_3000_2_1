#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <exception>
#include <string>
#include <sstream>
#include "Command.h"
#include "Geometry.h"

const std::string I_CMD = "<INVALID COMMAND>";

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Misapplication" << "\n";
    std::cout << "Application: main <filename>" << "\n";
    return EXIT_FAILURE;
  }
  std::string fileName = argv[1];
  std::ifstream file(fileName);
  if(!file)
  {
    std::cerr << "Error: file didn't open" << "\n";
    return EXIT_FAILURE;
  }
  std::vector<tretyak::Polygon> value;
  while (file.peek() != EOF)
  {
    std::transform(std::istream_iterator<tretyak::Polygon>(file),
                   std::istream_iterator<tretyak::Polygon>(),
                   std::back_inserter(value), [](const tretyak::Polygon &poly)
      {
        return poly;
      });
    if (file.peek() != EOF && file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  try
  {
    for(;;)
    {
      std::string str;
      if(std::getline(std::cin, str) && str.empty())
      {
        break;
      }
      std::string comnd1, comnd2;
      std::istringstream iss(str);
      iss >> comnd1 >> comnd2;

      try
      {
        if (comnd1 == "AREA")
        {
          cmd::area(value, comnd2);
        }
        else if (comnd1 == "MAX")
        {
          cmd::max(value, comnd2);
        }
        else if (comnd1 == "MIN")
        {
          cmd::min(value, comnd2);
        }
        else if (comnd1 == "COUNT")
        {
          cmd::count(value, comnd2);
        }
        else if (comnd1 == "MAXSEQ")
        {
          cmd::maxSeq(value);
        }
        else if (comnd1 == "LESSAREA")
        {
          cmd::lessArea(value);
        }
        else if (comnd1 != "")
        {
          throw I_CMD;
        }
      }
      catch (const std::string k)
      {
        std::cerr << k << "\n";
      }
    }
    return EXIT_SUCCESS;
  }
  catch (...)
  {
    std::cerr << "wrong" << "\n";
    return EXIT_FAILURE;
  }
}
