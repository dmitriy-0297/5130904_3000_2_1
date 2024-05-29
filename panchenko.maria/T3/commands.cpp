#include "commands.h"

void panchenko::area(const std::vector<panchenko::Polygon>& polygons, const std::string& param) {
    if (param == "ODD") {
        double sum = 0.0;
        for (const auto& polygon : polygons) {
            if (polygon.points.size() % 2 == 1) {
                sum += getArea(polygon);
            }
        }
        std::cout << std::fixed << std::setprecision(1) << sum << std::endl;
    }
    else if (param == "EVEN") {
        double sum = 0.0;
        for (const auto& polygon : polygons) {
            if (polygon.points.size() % 2 == 0) {
                sum += getArea(polygon);
            }
        }
        std::cout << std::fixed << std::setprecision(1) << sum << std::endl;
    }
    else if (param == "MEAN") {
        if (polygons.empty()) {
            std::cout << "<INVALID COMMAND>" << std::endl;
            return;
        }
        double sum = 0.0;
        for (const auto& polygon : polygons) {
            sum += getArea(polygon);
        }
        std::cout << std::fixed << std::setprecision(1) << sum / polygons.size() << std::endl;
    }
    else {
        unsigned long int numVertices = std::stoi(param);
        if (numVertices < 3) {
            std::cout << "<INVALID COMMAND>" << std::endl;
            return;
        }
        double sum = 0.0;
        for (const auto& polygon : polygons) {
            if (polygon.points.size() == numVertices) {
                sum += getArea(polygon);
            }
        }
        std::cout << std::fixed << std::setprecision(1) << sum << std::endl;
    }
}

void panchenko::min(const std::vector<panchenko::Polygon>& polygons, const std::string& param) {
    if (polygons.empty()) {
        std::cout << "<INVALID COMMAND>" << std::endl;
        return;
    }
    if (param == "AREA") {
        auto minAreaPolygon = std::min_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b) {
            return getArea(a) < getArea(b);
            });
        std::cout << std::fixed << std::setprecision(1) << getArea(*minAreaPolygon) << std::endl;
    }
    else if (param == "VERTEXES") {
        auto minVertexPolygon = std::min_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b) {
            return a.points.size() < b.points.size();
            });
        std::cout << minVertexPolygon->points.size() << std::endl;
    }
    else {
        std::cout << "<INVALID COMMAND>" << std::endl;
        return;
    }
}

void panchenko::max(const std::vector<panchenko::Polygon>& polygons, const std::string& param) {
    if (polygons.empty()) {
        std::cout << "<INVALID COMMAND>" << std::endl;
        return;
    }
    if (param == "AREA") {
        auto maxAreaPolygon = std::max_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b) {
            return getArea(a) < getArea(b);
            });
        std::cout << std::fixed << std::setprecision(1) << getArea(*maxAreaPolygon) << std::endl;
    }
    else if (param == "VERTEXES") {
        auto maxVertexPolygon = std::max_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b) {
            return a.points.size() < b.points.size();
            });
        std::cout << maxVertexPolygon->points.size() << std::endl;
    }
    else {
        std::cout << "<INVALID COMMAND>" << std::endl;
        return;
    }
}

void panchenko::count(const std::vector<panchenko::Polygon>& polygons, const std::string& param) {
    if (param == "EVEN") {
        int count = std::count_if(polygons.begin(), polygons.end(), [](const Polygon& polygon) {
            return polygon.points.size() % 2 == 0;
            });
        std::cout << count << std::endl;
    }
    else if (param == "ODD") {
        int count = std::count_if(polygons.begin(), polygons.end(), [](const Polygon& polygon) {
            return polygon.points.size() % 2 == 1;
            });
        std::cout << count << std::endl;
    }
    else {
        unsigned long int numVertices = std::stoi(param);
        if (numVertices < 3) {
            std::cout << "<INVALID COMMAND>" << std::endl;
            return;
        }
        int count = std::count_if(polygons.begin(), polygons.end(), [numVertices](const Polygon& polygon) {
            return polygon.points.size() == numVertices;
            });
        std::cout << count << std::endl;
    }
}

void panchenko::lessArea(std::istream& in, std::ostream& out, const std::vector<panchenko::Polygon>& polygons) {
    Polygon polygon;
    in >> polygon;
    if (!in || in.peek() != '\n')
    {
        std::cout << "<INVALID COMMAND>" << std::endl;
        return;
    }
    double area = getArea(polygon);
    int count = std::count_if(polygons.begin(), polygons.end(), [area](const Polygon& p) {
        return getArea(p) < area;
        });
    out << count;
    std::cout << "\n";
}

bool hasSamePoints(const panchenko::Point& delta, const panchenko::Point& point, const panchenko::Polygon& polygon)
{
    panchenko::Point dest = { point.x + delta.x, point.y + delta.y };

    using namespace std::placeholders;
    auto accSamePoints = std::bind(panchenko::comparePoints, dest, _1);
    return std::find_if(polygon.points.cbegin(), polygon.points.cend(), accSamePoints) != polygon.points.cend();
}

bool areSame(const panchenko::Polygon& polygon1, const panchenko::Polygon& polygon2)
{
    if (polygon1.points.size() != polygon2.points.size())
    {
        return false;
    }

    int dx = polygon2.points[0].x - polygon1.points[0].x;
    int dy = polygon2.points[0].y - polygon1.points[0].y;
    panchenko::Point delta = { dx, dy };

    using namespace std::placeholders;
    std::function< bool(const panchenko::Point&) > accSamePoints = std::bind(hasSamePoints, delta, _1, polygon2);

    int numberOfPoints = std::distance(polygon1.points.cbegin(), polygon1.points.cend());
    return std::count_if(polygon1.points.cbegin(), polygon1.points.cend(), accSamePoints) == numberOfPoints;
}

void panchenko::same(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
{
    Polygon polygonToCompare;
    in >> polygonToCompare;
    if (!in || in.peek() != '\n')
    {
        std::cout << "<INVALID COMMAND>" << std::endl;
        return;
    }

    using namespace std::placeholders;
    std::function< bool(const Polygon&) > accSame = std::bind(areSame, _1, polygonToCompare);

    out << std::count_if(polygons.cbegin(), polygons.cend(), accSame);
    std::cout << "\n";
}
