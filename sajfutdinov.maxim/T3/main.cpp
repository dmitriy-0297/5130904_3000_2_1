#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <cctype>
#include <iomanip>

namespace sajfutdinov {
  struct Point {
    int x, y;
    Point() : x(0), y(0) {};
    Point(const Point& point) : x(point.x), y(point.y) {};
    bool operator==(const Point& point) const { return x == point.x && y == point.y; }
  };

  struct Polygon {
    std::vector<Point> points;
  };

  struct PrintPoint {
    void operator()(const Point& p) const {
      std::cout << "(" << p.x << ";" << p.y << ") ";
    }
  };

  struct PrintPolygon {
    void operator()(const Polygon& poly) const {
      std::for_each(poly.points.begin(), poly.points.end(), PrintPoint());
      std::cout << "\n";
    }
  };

  struct AreaCalculator {
    double operator()(const Polygon& poly) const {
      double area = 0.0;
      size_t n = poly.points.size();
      for (size_t i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += (poly.points[i].x + poly.points[j].x) * (poly.points[i].y - poly.points[j].y);
      }
      return std::abs(area) / 2.0;
    }
  };

  void calculateArea(const std::vector<Polygon>& polygons, const std::string& type) {
    int count = 0;
    double totalArea = 0.0;
    if (type == "0" || type == "1" || type == "2")
    {
      std::cerr << "<INVALID COMMAND>\n";
      return;
    }
    for (const auto& poly : polygons) {
      if (type == "MEAN")
      {
        totalArea += AreaCalculator()(poly);
        count++;
        continue;
      }
      if (std::all_of(type.begin(), type.end(), [](char c) { return std::isdigit(c); }))
      {
        if (poly.points.size() == std::stoul(type))
        {
          totalArea += AreaCalculator()(poly);
          count++;
          continue;
        }
      }
      if ((poly.points.size() % 2 == 0 && type == "EVEN") || (poly.points.size() % 2 != 0 && type == "ODD"))
      {
        totalArea += AreaCalculator()(poly);
        count++;
        continue;
      }
    }
    std::cout << std::fixed << std::setprecision(1) << (type == "MEAN" ? totalArea / count : totalArea) << "\n";
  }

  void calculateMax(const std::vector<Polygon>& polygons, const std::string& type) {
    if ((type != "AREA") && (type != "VERTEXES"))
    {
      std::cerr << "<INVALID COMMMAND>\n";
      return;
    }
    auto maxIt = std::max_element(polygons.begin(), polygons.end(), [&type](const Polygon& a, const Polygon& b) {
      if (type == "AREA") {
        return AreaCalculator()(a) < AreaCalculator()(b);
      }
      else {
        return a.points.size() < b.points.size();
      }
      });
    if (type == "AREA") {
      std::cout << std::fixed << std::setprecision(1) << AreaCalculator()(*maxIt) << "\n";
    }
    else if (type == "VERTEXES") {
      std::cout << std::fixed << std::setprecision(1) << maxIt->points.size() << "\n";
    }
  }

  void calculateMin(const std::vector<Polygon>& polygons, const std::string& type) {
    if ((type != "AREA") && (type != "VERTEXES"))
    {
      std::cerr << "<INVALID COMMMAND>\n";
      return;
    }
    auto minIt = std::min_element(polygons.begin(), polygons.end(), [&type](const Polygon& a, const Polygon& b)
      {
        if (type == "AREA")
        {
          return AreaCalculator()(a) < AreaCalculator()(b);
        }
        else
        {
          return a.points.size() < b.points.size();
        }
      });
    if (type == "AREA") {
      std::cout << std::fixed << std::setprecision(1) << AreaCalculator()(*minIt) << "\n";
    }
    else if (type == "VERTEXES") {
      std::cout << std::fixed << std::setprecision(1) << minIt->points.size() << "\n";
    }
  }

  void countPolygons(const std::vector<Polygon>& polygons, const std::string& type) {
    if (type == "EVEN") {
      auto count = std::count_if(polygons.begin(), polygons.end(), [](const Polygon& poly) {
        return poly.points.size() % 2 == 0;
        });
      std::cout << count << "\n";
    }
    else if (type == "ODD") {
      auto count = std::count_if(polygons.begin(), polygons.end(), [](const Polygon& poly) {
        return poly.points.size() % 2 != 0;
        });
      std::cout << count << "\n";
    }
    else if (std::all_of(type.begin(), type.end(), [](char c) { return std::isdigit(c); })) {
      size_t numpoints = std::stoul(type);
      if (numpoints == 1 || numpoints == 2 || numpoints == 0)
      {
        std::cerr << "<INVALID COMMAND>\n";
        return;
      }
      auto count = std::count_if(polygons.begin(), polygons.end(), [numpoints](const Polygon& poly) {
        return poly.points.size() == numpoints;
        });
      std::cout << count << "\n";
    }
    else
    {
      std::cerr << "<INVALID COMMAND>\n";
      return;
    }
  }

  void lessArea(const std::vector<Polygon>& polygons, const std::string& strPoly)
  {
    Polygon lessAreaPolygon;
    unsigned long int numpoints = strPoly[0] - '0';
    if (numpoints == 1 || numpoints == 2 || numpoints == 0)
    {
      std::cerr << "<INVALID COMMAND>\n";
      return;
    }
    for (size_t i = 1; i < strPoly.length(); i = i + 6)
    {
      Point lessAreaPoint;
      if (strPoly[i] == ' ' && strPoly[i + 1] == '(' && strPoly[i + 3] == ';' && strPoly[i + 5] == ')')
      {
        lessAreaPoint.x = strPoly[i + 2] - '0';
        lessAreaPoint.y = strPoly[i + 4] - '0';
        lessAreaPolygon.points.push_back(lessAreaPoint);
      }
      else if (strPoly[i] == ' ' && strPoly[i + 1] == '(' && strPoly[i + 2] == '-')
      {
        lessAreaPoint.x = (strPoly[i + 3] - '0') * (-1);
        if (strPoly[i + 4] == ';')
        {
          if (strPoly[i + 5] == '-' && strPoly[i + 7] == ')')
          {
            lessAreaPoint.y = (strPoly[i + 6] - '0') * (-1);
            i = i + 2;
          }
          else if (strPoly[i + 6] == ')')
          {
            lessAreaPoint.y = strPoly[i + 5] - '0';
            i = i + 1;
          }
        }
        lessAreaPolygon.points.push_back(lessAreaPoint);
      }
      else if (strPoly[i] == ' ' && strPoly[i + 1] == '(' && strPoly[i + 3] == ';' && strPoly[i + 4] == '-' && strPoly[i + 6] == ')')
      {
        lessAreaPoint.x = strPoly[i + 2] - '0';
        lessAreaPoint.y = (strPoly[i + 5] - '0') * (-1);
        lessAreaPolygon.points.push_back(lessAreaPoint);
        i = i + 1;
      }
    }
    auto lessAreaCount = std::count_if(polygons.begin(), polygons.end(), [lessAreaPolygon](const Polygon& poly) {
      return AreaCalculator()(poly) < AreaCalculator()(lessAreaPolygon);
      });
    std::cout << std::fixed << std::setprecision(1) << lessAreaCount << "\n";
  }

  bool doIntersect(const Point& p1, const Point& q1, const Point& p2, const Point& q2) {
    int o1 = (q1.y - p1.y) * (p2.x - p1.x) - (q1.x - p1.x) * (p2.y - p1.y);
    int o2 = (q1.y - p1.y) * (q2.x - p1.x) - (q1.x - p1.x) * (q2.y - p1.y);
    int o3 = (q2.y - p2.y) * (p1.x - p2.x) - (q2.x - p2.x) * (p1.y - p2.y);
    int o4 = (q2.y - p2.y) * (q1.x - p2.x) - (q2.x - p2.x) * (q1.y - p2.y);

    if ((o1 * o2 < 0) && (o3 * o4 < 0)) {
      return true;
    }
    return false;
  }

  bool isInside(const Polygon& polygon, const Point& p) {
    int n = polygon.points.size();
    int count = 0;
    for (int i = 0; i < n; i++) {
      int j = (i + 1) % n;
      sajfutdinov::Point iP = polygon.points[i];
      sajfutdinov::Point jP = polygon.points[j];
      if ((iP.y > p.y) != (jP.y > p.y) && (p.x < (jP.x - iP.x) * (p.y - iP.y) / (jP.y - iP.y) + iP.x)) {
        count++;
      }
    }
    return count % 2 == 1;
  }

  bool isPolygonIntersecting(const Polygon& polygon1, const Polygon& polygon2) {
    size_t n = polygon1.points.size();
    size_t m = polygon2.points.size();

    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < m; j++) {
        if (doIntersect(polygon1.points[i], polygon1.points[(i + 1) % n], polygon2.points[j], polygon2.points[(j + 1) % m])) {
          return true;
        }
      }
    }

    if (isInside(polygon1, polygon2.points[0]) || isInside(polygon2, polygon1.points[0])) {
      return true;
    }

    return false;
  }

  void intersections(const std::vector<Polygon>& polygons, const std::string& strPoly)
  {
    //std::for_each(polygons.begin(), polygons.end(), PrintPolygon());
    Polygon intrscPoly;
    unsigned long int numpoints = strPoly[0] - '0';
    for (size_t i = 1; i < strPoly.length(); i = i + 6)
    {
      Point intersectionsPoint;
      if (strPoly[i] == ' ' && strPoly[i + 1] == '(' && strPoly[i + 3] == ';' && strPoly[i + 5] == ')')
      {
        intersectionsPoint.x = strPoly[i + 2] - '0';
        intersectionsPoint.y = strPoly[i + 4] - '0';
        intrscPoly.points.push_back(intersectionsPoint);
      }
      else if (strPoly[i] == ' ' && strPoly[i + 1] == '(' && strPoly[i + 2] == '-')
      {
        intersectionsPoint.x = (strPoly[i + 3] - '0') * (-1);
        if (strPoly[i + 4] == ';')
        {
          if (strPoly[i + 5] == '-' && strPoly[i + 7] == ')')
          {
            intersectionsPoint.y = (strPoly[i + 6] - '0') * (-1);
            i = i + 2;
          }
          else if (strPoly[i + 6] == ')')
          {
            intersectionsPoint.y = strPoly[i + 5] - '0';
            i = i + 1;
          }
        }
        intrscPoly.points.push_back(intersectionsPoint);
      }
      else if (strPoly[i] == ' ' && strPoly[i + 1] == '(' && strPoly[i + 3] == ';' && strPoly[i + 4] == '-' && strPoly[i + 6] == ')')
      {
        intersectionsPoint.x = strPoly[i + 2] - '0';
        intersectionsPoint.y = (strPoly[i + 5] - '0') * (-1);
        intrscPoly.points.push_back(intersectionsPoint);
        i = i + 1;
      }
      //sajfutdinov::PrintPolygon()(intrscPoly);
    }
    if (intrscPoly.points.size() != numpoints)
    {
      std::cerr << "<INVALID COMMAND>\n";
      return;
    }

    auto count = std::count_if(polygons.begin(), polygons.end(), [intrscPoly](const Polygon& poly) {
      return isPolygonIntersecting(intrscPoly, poly);
      });
    std::cout << count << "\n";
  }
}

int main(int argc, char* argv[]) {
  if (argc != 2)
  {
    std::cerr << "Bye";
    return 1;
  }

  std::vector<sajfutdinov::Polygon> polygons;
  std::ifstream input(argv[1]);
  if (!input.is_open())
  {
    std::cerr << "No file!";
    return 1;
  }

  std::string line = "";
  while (std::getline(input, line))
  {
    sajfutdinov::Polygon poly;
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
    if (numpoints != 0)
    {
      for (size_t i = 1; i < 6 * numpoints - 1; i = i + 6)
      {
        if (line.length() != (numpoints * 6 + 1)) break;
        if (line[i] == ' ' && line[i + 1] == '(' && line[i + 3] == ';' && line[i + 5] == ')')
        {
          sajfutdinov::Point point;
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
    if (line.length() > 4)
    {
      if (line.substr(0, 3) == "MAX")
      {
        std::string type = line.substr(4, line.length() - 1);
        sajfutdinov::calculateMax(polygons, type);
        continue;
      }
      if (line.substr(0, 3) == "MIN")
      {
        std::string type = line.substr(4, line.length() - 1);
        sajfutdinov::calculateMin(polygons, type);
        continue;
      }
    }
    if (line.length() > 5)
    {
      if (line.substr(0, 4) == "AREA")
      {
        std::string type = line.substr(5, line.length() - 1);
        sajfutdinov::calculateArea(polygons, type);
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
          std::cerr << "<INVALID COMMAND>\n";
          continue;
        }
        sajfutdinov::countPolygons(polygons, type);
        continue;
      }
    }
    if (line.length() > 9)
    {
      if (line.substr(0, 8) == "LESSAREA")
      {
        std::string strPoly = line.substr(9, line.length() - 1);
        sajfutdinov::lessArea(polygons, strPoly);
        continue;
      }
    }
    if (line.length() > 14)
    {
      if (line.substr(0, 13) == "INTERSECTIONS")
      {
        std::string strPoly = line.substr(14, line.length() - 1);
        sajfutdinov::intersections(polygons, strPoly);
        continue;
      }
    }
    std::cerr << "<INVALID COMMAND>\n";
  }

  return 0;
}
