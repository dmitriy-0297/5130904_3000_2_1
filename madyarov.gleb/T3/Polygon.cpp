#include "Polygon.h"

namespace madyarov {
  double Polygon::area() const {
    int n = points.size();
    double a = 0;
    for (int i = 0; i < n; ++i) {
      int j = (i + 1) % n;
      a += points[i].x * points[j].y - points[j].x * points[i].y;
    }
    return std::abs(a) / 2.0;
  }

  bool Polygon::hasEvenVertices() const {
    return points.size() % 2 == 0;
  }

  bool Polygon::hasOddVertices() const {
    return points.size() % 2 != 0;
  }

  std::vector<Polygon> readPolygons(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<Polygon> polygons;
    std::string line;

    while (std::getline(file, line)) {
      std::istringstream iss(line);
      size_t num_vertices;
      if (!(iss >> num_vertices) || num_vertices < 3) continue;

      Polygon poly;
      std::vector<Point> points;
      char ignore;
      int x, y;

      while (iss >> ignore >> x >> ignore >> y >> ignore) {
        points.push_back({ x, y });
      }
      if (points.size() == num_vertices) {
        poly.points = points;
        polygons.push_back(poly);
      }
    }
    return polygons;
  }

  void processCommands(const std::vector<Polygon>& polygons) {
    std::string command;
    while (std::cin >> command) {
      if (command == "AREA") {
        std::string type;
        std::cin >> type;
        if (type == "EVEN") {
          double sum = polygons.empty() ? 0.0 : std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double total, const Polygon& p) {
              return total + (p.hasEvenVertices() ? p.area() : 0);
            });
          std::cout << std::fixed << std::setprecision(1) << sum << '\n';
        }
        else if (type == "ODD") {
          double sum = polygons.empty() ? 0.0 : std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double total, const Polygon& p) {
              return total + (p.hasOddVertices() ? p.area() : 0);
            });
          std::cout << std::fixed << std::setprecision(1) << sum << '\n';
        }
        else if (type == "MEAN") {
          if (polygons.empty()) {
            std::cout << "<INVALID COMMAND>\n";
          }
          else {
            double mean = std::accumulate(polygons.begin(), polygons.end(), 0.0,
              [](double total, const Polygon& p) {
                return total + p.area();
              }) / polygons.size();
              std::cout << std::fixed << std::setprecision(1) << mean << '\n';
          }
        }
        else {
          size_t num_vertices;
          try {
            num_vertices = std::stoi(type);
            if (num_vertices < 3) throw std::invalid_argument("invalid number of vertices");
          }
          catch (...) {
            std::cout << "<INVALID COMMAND>\n";
            std::string dummy;
            std::getline(std::cin, dummy);
            continue;
          }
          double sum = polygons.empty() ? 0.0 : std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [num_vertices](double total, const Polygon& p) {
              return total + (p.points.size() == num_vertices ? p.area() : 0);
            });
          std::cout << std::fixed << std::setprecision(1) << sum << '\n';
        }
      }
      else if (command == "MAX") {
        std::string type;
        std::cin >> type;
        if (polygons.empty()) {
          std::cout << "<INVALID COMMAND>\n";
        }
        else if (type == "AREA") {
          double max_area = std::max_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
              return a.area() < b.area();
            })->area();
            std::cout << std::fixed << std::setprecision(1) << max_area << '\n';
        }
        else if (type == "VERTEXES") {
          int max_vertexes = std::max_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
              return a.points.size() < b.points.size();
            })->points.size();
            std::cout << max_vertexes << '\n';
        }
        else {
          std::cout << "<INVALID COMMAND>\n";
        }
      }
      else if (command == "MIN") {
        std::string type;
        std::cin >> type;
        if (polygons.empty()) {
          std::cout << "<INVALID COMMAND>\n";
        }
        else if (type == "AREA") {
          double min_area = std::min_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
              return a.area() < b.area();
            })->area();
            std::cout << std::fixed << std::setprecision(1) << min_area << '\n';
        }
        else if (type == "VERTEXES") {
          int min_vertexes = std::min_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
              return a.points.size() < b.points.size();
            })->points.size();
            std::cout << min_vertexes << '\n';
        }
        else {
          std::cout << "<INVALID COMMAND>\n";
        }
      }
      else if (command == "COUNT") {
        std::string type;
        std::cin >> type;
        if (type == "EVEN") {
          int count = polygons.empty() ? 0 : std::count_if(polygons.begin(), polygons.end(),
            [](const Polygon& p) {
              return p.hasEvenVertices();
            });
          std::cout << count << '\n';
        }
        else if (type == "ODD") {
          int count = polygons.empty() ? 0 : std::count_if(polygons.begin(), polygons.end(),
            [](const Polygon& p) {
              return p.hasOddVertices();
            });
          std::cout << count << '\n';
        }
        else {
          size_t num_vertices;
          try {
            num_vertices = std::stoi(type);
            if (num_vertices < 3) throw std::invalid_argument("invalid number of vertices");
          }
          catch (...) {
            std::cout << "<INVALID COMMAND>\n";
            std::string dummy;
            std::getline(std::cin, dummy);
            continue;
          }
          int count = polygons.empty() ? 0 : std::count_if(polygons.begin(), polygons.end(),
            [num_vertices](const Polygon& p) {
              return p.points.size() == num_vertices;
            });
          std::cout << count << '\n';
        }
      }
      else if (command == "LESSAREA") {
        size_t num_vertices;
        std::cin >> num_vertices;
        if (num_vertices < 3) {
          std::cout << "<INVALID COMMAND>\n";
          std::string dummy;
          std::getline(std::cin, dummy);
          continue;
        }
        Polygon poly;
        std::string line;
        std::getline(std::cin >> std::ws, line);
        std::istringstream iss(line);
        char ignore;
        bool check = true;
        while (iss >> ignore && check == true) {
          int x, y;
          if (!(iss >> x >> ignore >> y >> ignore)) {
            check = false;
            std::cout << "<INVALID COMMAND>\n";
            continue;
          }
          poly.points.push_back({ x, y });
        }
        if (check == true) {
          if (poly.points.size() >= 3 && poly.points.size() == num_vertices) {
            double ref_area = poly.area();
            int count = polygons.empty() ? 0 : std::count_if(polygons.begin(), polygons.end(),
              [ref_area](const Polygon& p) {
                return p.area() < ref_area;
              });
            std::cout << count << '\n';
          }
          else {
            std::cout << "<INVALID COMMAND>\n";
          }
        }
      }
      else if (command == "INTERSECTIONS") {
        size_t num_vertices;
        std::cin >> num_vertices;
        if (num_vertices < 3) {
          std::cout << "<INVALID COMMAND>\n";
          std::string dummy;
          std::getline(std::cin, dummy);
          continue;
        }
        Polygon poly;
        std::string line;
        std::getline(std::cin >> std::ws, line);
        std::istringstream iss(line);
        char ignore;
        bool check = true;
        while (iss >> ignore && check == true) {
          int x, y;
          if (!(iss >> x >> ignore >> y >> ignore)) {
            check = false;
            std::cout << "<INVALID COMMAND>\n";
            continue;
          }
          poly.points.push_back({ x, y });
        }
        if (check == true) {
          if (poly.points.size() >= 3 && poly.points.size() == num_vertices) {
            int count = polygons.empty() ? 0 : std::count_if(polygons.begin(), polygons.end(),
              [&poly](const Polygon& p) {
                auto min_x1 = std::min_element(poly.points.begin(), poly.points.end(),
                [](const Point& a, const Point& b) { return a.x < b.x; })->x;
            auto max_x1 = std::max_element(poly.points.begin(), poly.points.end(),
              [](const Point& a, const Point& b) { return a.x < b.x; })->x;
            auto min_y1 = std::min_element(poly.points.begin(), poly.points.end(),
              [](const Point& a, const Point& b) { return a.y < b.y; })->y;
            auto max_y1 = std::max_element(poly.points.begin(), poly.points.end(),
              [](const Point& a, const Point& b) { return a.y < b.y; })->y;

            auto min_x2 = std::min_element(p.points.begin(), p.points.end(),
              [](const Point& a, const Point& b) { return a.x < b.x; })->x;
            auto max_x2 = std::max_element(p.points.begin(), p.points.end(),
              [](const Point& a, const Point& b) { return a.x < b.x; })->x;
            auto min_y2 = std::min_element(p.points.begin(), p.points.end(),
              [](const Point& a, const Point& b) { return a.y < b.y; })->y;
            auto max_y2 = std::max_element(p.points.begin(), p.points.end(),
              [](const Point& a, const Point& b) { return a.y < b.y; })->y;

            return !(min_x1 > max_x2 || max_x1 < min_x2 || min_y1 > max_y2 || max_y1 < min_y2);
              });

            std::cout << count << '\n';
          }
          else {
            std::cout << "<INVALID COMMAND>\n";
          }
        }
      }
      else {
        std::cout << "<INVALID COMMAND>\n";
        std::string dummy;
        std::getline(std::cin, dummy);
      }
    }
  }
}
