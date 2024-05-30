#include "Polygon.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <cstddef>

bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}

bool Polygon::operator==(const Polygon& other) const {
    return points == other.points;
}

double polygonArea(const Polygon& polygon) {
    double area = 0.0;
    int n = polygon.points.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += polygon.points[i].x * polygon.points[j].y;
        area -= polygon.points[j].x * polygon.points[i].y;
    }
    return std::abs(area) / 2.0;
}

bool isRightAngle(const Point& a, const Point& b, const Point& c) {
    int dx1 = b.x - a.x;
    int dy1 = b.y - a.y;
    int dx2 = c.x - b.x;
    int dy2 = c.y - b.y;
    return dx1 * dx2 + dy1 * dy2 == 0;
}

bool hasRightAngle(const Polygon& polygon) {
    int n = polygon.points.size();
    for (int i = 0; i < n; ++i) {
        if (isRightAngle(polygon.points[i], polygon.points[(i + 1) % n], polygon.points[(i + 2) % n])) {
            return true;
        }
    }
    return false;
}

std::vector<Polygon> readPolygonsFromFile(const std::string& filename) {
    std::vector<Polygon> polygons;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        size_t numPoints;
        if (!(iss >> numPoints)) {
            continue;
        }

        Polygon polygon;
        for (size_t i = 0; i < numPoints; ++i) {
            char sep1, sep2, sep3;
            Point p;
            if (!(iss >> sep1 >> p.x >> sep2 >> p.y >> sep3) || sep1 != '(' || sep2 != ';' || sep3 != ')') {
                polygon.points.clear();
                break;
            }
            std::string extra;
            if (std::getline(iss, extra) and !extra.empty()) {
                iss.clear();
                iss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else {
                polygon.points.push_back(p);
            }
        }

        if (!polygon.points.empty() && polygon.points.size() == numPoints) {
            polygons.push_back(polygon);
        }
    }

    return polygons;
}

void printAreaResult(double result) {
    std::cout << std::fixed << std::setprecision(1) << result << "\n";
}

void executeCommand(const std::string& command, std::vector<Polygon>& polygons) {
    std::istringstream iss(command);
    std::string cmd;
    iss >> cmd;

    if (cmd == "AREA") {
        std::string type;
        iss >> type;

        if (type == "ODD") {
            auto isOdd = [](const Polygon& p) { return p.points.size() % 2 == 1; };
            double sumArea = std::accumulate(polygons.begin(), polygons.end(), 0.0, [&](double acc, const Polygon& p) {
                return isOdd(p) ? acc + polygonArea(p) : acc;
                });
            printAreaResult(sumArea);
        }
        else if (type == "EVEN") {
            auto isEven = [](const Polygon& p) { return p.points.size() % 2 == 0; };
            double sumArea = std::accumulate(polygons.begin(), polygons.end(), 0.0, [&](double acc, const Polygon& p) {
                return isEven(p) ? acc + polygonArea(p) : acc;
                });
            printAreaResult(sumArea);
        }
        else if (type == "MEAN") {
            if (polygons.empty()) {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            double meanArea = std::accumulate(polygons.begin(), polygons.end(), 0.0, [&](double acc, const Polygon& p) {
                return acc + polygonArea(p);
                }) / polygons.size();
                printAreaResult(meanArea);
        }
        else {
            size_t numVertices;
            try {
                numVertices = std::stoi(type);
            }
            catch (...) {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            if (numVertices <= 2) {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            double sumArea = std::accumulate(polygons.begin(), polygons.end(), 0.0, [&](double acc, const Polygon& p) {
                return p.points.size() == numVertices ? acc + polygonArea(p) : acc;
                });
            printAreaResult(sumArea);
        }
    }
    else if (cmd == "MAX") {
        std::string type;
        iss >> type;

        if (type == "AREA") {
            if (polygons.empty()) {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            double maxArea = polygonArea(*std::max_element(polygons.begin(), polygons.end(), [&](const Polygon& a, const Polygon& b) {
                return polygonArea(a) < polygonArea(b);
                }));
            printAreaResult(maxArea);
        }
        else if (type == "VERTEXES") {
            if (polygons.empty()) {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            int maxVertices = std::max_element(polygons.begin(), polygons.end(), [&](const Polygon& a, const Polygon& b) {
                return a.points.size() < b.points.size();
                })->points.size();
                std::cout << maxVertices << "\n";
        }
        else {
            std::cout << "<INVALID COMMAND>\n";
        }
    }
    else if (cmd == "COUNT") {
        std::string type;
        iss >> type;
        if (type == "EVEN") {
            auto isEven = [](const Polygon& p) { return p.points.size() % 2 == 0; };
            int count = std::count_if(polygons.begin(), polygons.end(), isEven);
            std::cout << count;
        }
        else if (type == "ODD") {
            auto isOdd = [](const Polygon& p) { return p.points.size() % 2 == 1; };
            int count = std::count_if(polygons.begin(), polygons.end(), isOdd);
            std::cout << count;
        }
        else {
            size_t numVertices;
            try {
                numVertices = std::stoi(type);
            }
            catch (...) {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            if (numVertices <= 2) {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            int count = std::count_if(polygons.begin(), polygons.end(), [&](const Polygon& p) {
                return p.points.size() == numVertices;
                });
            std::cout << count;
        }
        std::cout << '\n';
    }
    else if (cmd == "ECHO") {
        std::string polyStr;
        getline(iss, polyStr);
        polyStr = polyStr.substr(1);

        std::istringstream polyIss(polyStr);
        int numPoints;
        polyIss >> numPoints;

        Polygon targetPolygon;
        for (int i = 0; i < numPoints; ++i) {
            char sep1, sep2, sep3;
            Point p;
            if (!(polyIss >> sep1 >> p.x >> sep2 >> p.y >> sep3) || sep1 != '(' || sep2 != ';' || sep3 != ')') {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            targetPolygon.points.push_back(p);
        }

        int count = 0;
        auto it = polygons.begin();
        while (it != polygons.end()) {
            if (*it == targetPolygon) {
                it = polygons.insert(it + 1, targetPolygon);
                ++count;
                ++it;
            }
            ++it;
        }
        std::cout << count << "\n";
    }
    else if (cmd == "RIGHTSHAPES") {
        int count = std::count_if(polygons.begin(), polygons.end(), hasRightAngle);
        std::cout << count << "\n";
    }
    else {
        std::cout << "<INVALID COMMAND>\n";
    }
}
