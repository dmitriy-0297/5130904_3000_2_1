#include <fstream>
#include <cctype>
#include <iomanip>
#include "functions.h"

using namespace sajfutdinov;

int main(int argc, char* argv[]) {
  if (argc != 2)
  {
    std::cout << "Bye";
    return 1;
  }

  std::vector<Polygon> polygons;
  std::ifstream input(argv[1]);
  if (!input.is_open())
  {
    std::cout << "No file!";
    return 1;
  }

  std::string line = "";
  while (std::getline(input, line))
  {
    Polygon poly;
    char c = line[0];
    unsigned long int numpoints = 0;
    for (char a : "123456789")
    {
      if (c == a)
      {
        numpoints = c - '0';
        break;
      }
    }
    if (numpoints > 2)
    {
      for (size_t i = 1; i < 6 * numpoints - 1; i = i + 6)
      {
        if (line.length() != (numpoints * 6 + 1)) break;
        if (line[i] == ' ' && line[i + 1] == '(' && line[i + 3] == ';' && line[i + 5] == ')')
        {
          Point point;
          point.x = line[i + 2] - '0';
          point.y = line[i + 4] - '0';
          poly.points.push_back(point);
        }
      }
      if (poly.points.size() == numpoints) polygons.push_back(poly);
    }
  }

  while (std::getline(std::cin, line))
  {
    if (line.length() == 0) continue;
    if (line.length() > 4 && polygons.size() > 0)
    {
      if (line.substr(0, 3) == "MAX")
      {
        std::string type = line.substr(4, line.length() - 1);
        calculateMax(polygons, type);
        continue;
      }
      if (line.substr(0, 3) == "MIN")
      {
        std::string type = line.substr(4, line.length() - 1);
        calculateMin(polygons, type);
        continue;
      }
    }
    if (line.length() > 5)
    {
      if (line.substr(0, 4) == "AREA")
      {
        std::string type = line.substr(5, line.length() - 1);
        calculateArea(polygons, type);
        continue;
      }
    }
    if (line.length() > 6)
    {
      if (line.substr(0, 5) == "COUNT")
      {
        std::string type = line.substr(6, line.length() - 1);
        if (type == "0" || type == "1" || type == "2")
        {
          std::cout << INVALID_COMMAND;
          continue;
        }
        countPolygons(polygons, type);
        continue;
      }
    }
    if (line.length() > 9)
    {
      if (line.substr(0, 8) == "LESSAREA")
      {
        std::string strPoly = line.substr(9, line.length() - 1);
        lessArea(polygons, strPoly);
        continue;
      }
    }
    if (line.length() > 14)
    {
      if (line.substr(0, 13) == "INTERSECTIONS")
      {
        std::string strPoly = line.substr(14, line.length() - 1);
        intersections(polygons, strPoly);
        continue;
      }
    }
    std::cout << INVALID_COMMAND;
  }

  return 0;
}
