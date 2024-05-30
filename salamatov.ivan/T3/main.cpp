#include <iostream>
#include <iterator>
#include <iomanip>
#include <fstream>
#include <limits>

#include "Structs.h"
#include "Commands.h"

namespace salamatov
{
  int main(int argc, char* argv[])
  {
    if (argc != 2)
    {
      std::cerr << "Not enough arguments" << std::endl;
      std::cout << "Usage: <bin> <filename>" << std::endl;
      return 1;
    }
    std::string filename = argv[1];
    std::ifstream file(filename);
    if (!file)
    {
      std::cerr << "File not found!" << std::endl;
      return 1;
    }
    std::cout << std::setprecision(1) << std::fixed;
    std::vector<salamatov::Polygon> data;
    using input_it_t = std::istream_iterator<salamatov::Polygon>;
    while (!file.eof())
    {
      std::copy(input_it_t{ file }, input_it_t{}, std::back_inserter(data));
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
        std::string cmd;
        std::cin >> cmd;
        try
        {
          if (cmd == "AREA")
          {
            command::area(data);
          }
          else if (cmd == "MAX")
          {
            command::max(data);
          }
          else if (cmd == "MIN")
          {
            command::min(data);
          }
          else if (cmd == "COUNT")
          {
            command::count(data);
          }
          else if (cmd == "RMECHO")
          {
            command::rmecho(data);
          }
          else if (cmd == "SAME")
          {
            command::same(data);
          }
          else if (cmd != "")
          {
            throw "<INVALID COMMAND>";
          }
        }
        catch (const char* err)
        {
          std::cout << err << std::endl;
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
      }
      return 0;
    }
    catch (...)
    {
      std::cerr << "Something went wrong..." << std::endl;
      return 1;
    }
  }
}

int main(int argc, char* argv[])
{
  return salamatov::main(argc, argv);
}
