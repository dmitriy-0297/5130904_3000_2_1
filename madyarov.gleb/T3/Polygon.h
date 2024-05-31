#ifndef POLYGON_H
#define POLYGON_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <iomanip>

namespace madyarov {
  struct Point {
    int x, y;
  };

  struct Polygon {
    std::vector<Point> points;
    double area() const;
    bool hasEvenVertices() const;
    bool hasOddVertices() const;
  };

  std::vector<Polygon> readPolygons(const std::string& filename);

  void processCommands(const std::vector<Polygon>& polygons);
}

#endif
