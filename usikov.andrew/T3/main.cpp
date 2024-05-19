#include <iterator>
#include <iomanip>
#include <fstream>
#include <limits>

#include "command.h"

using namespace usikov;

int main( int argC, char *argV[] )
{
  if (argC != 2) // temp, need argc 2 only
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

  try
  {
    while (!std::cin.eof())
    {
      std::string cmd;

      std::cin >> cmd;

      try
      {
        if (cmd == "AREA")
          command::area(data);
        else if (cmd == "MIN")
          command::min(data);
        else if (cmd == "MAX")
          command::max(data);
        else if (cmd == "COUNT")
          command::count(data);
        else if (cmd == "RMECHO")
          command::rmecho(data);
        else if (cmd == "INTERSECTIONS")
          command::intersections(data);
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
