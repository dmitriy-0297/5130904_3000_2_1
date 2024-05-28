#include "commands.h"

void panchenko::area(const std::vector<panchenko::Polygon>& polygons, const std::string& param) {
    if (param == "ODD") {
        double sum = 0.0;
        for (const auto& polygon : polygons) {
            if (polygon.points.size() % 2 == 1) {
                sum += getArea(polygon);
            }
        }
        std::cout << std::fixed << sum << std::endl;
    }
    else if (param == "EVEN") {
        double sum = 0.0;
        for (const auto& polygon : polygons) {
            if (polygon.points.size() % 2 == 0) {
                sum += getArea(polygon);
            }
        }
        std::cout << std::fixed << sum << std::endl;
    }
    else if (param == "MEAN") {
        if (polygons.empty()) {
            std::cout << "0.0" << std::endl;
            return;
        }
        double sum = 0.0;
        for (const auto& polygon : polygons) {
            sum += getArea(polygon);
        }
        std::cout << std::fixed << sum / polygons.size() << std::endl;
    }
    else {
        unsigned long int numVertices = std::stoi(param);
        double sum = 0.0;
        for (const auto& polygon : polygons) {
            if (polygon.points.size() == numVertices) {
                sum += getArea(polygon);
            }
        }
        std::cout << std::fixed << sum << std::endl;
    }
}

void panchenko::min(const std::vector<panchenko::Polygon>& polygons) {
    if (polygons.empty()) {
        throw std::invalid_argument(ERROR_OF_COMMAND_MSG);
        return;
    }
    auto minAreaPolygon = std::min_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b) {
        return getArea(a) < getArea(b);
        });
    std::cout << std::fixed << getArea(*minAreaPolygon) << std::endl;
}

void panchenko::max(const std::vector<panchenko::Polygon>& polygons) {
    if (polygons.empty()) {
        throw std::invalid_argument(ERROR_OF_COMMAND_MSG);
        return;
    }
    auto maxAreaPolygon = std::max_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b) {
        return getArea(a) < getArea(b);
        });
    std::cout << std::fixed << getArea(*maxAreaPolygon) << std::endl;
}

void panchenko::count(const std::vector<panchenko::Polygon>& polygons, const std::string& param) {
    if (param == "EVEN") {
        __int64 count = std::count_if(polygons.begin(), polygons.end(), [](const Polygon& polygon) {
            return polygon.points.size() % 2 == 0;
            });
        std::cout << count << std::endl;
    }
    else if (param == "ODD") {
        __int64 count = std::count_if(polygons.begin(), polygons.end(), [](const Polygon& polygon) {
            return polygon.points.size() % 2 == 1;
            });
        std::cout << count << std::endl;
    }
    else {
        unsigned long int numVertices = std::stoi(param);
        __int64 count = std::count_if(polygons.begin(), polygons.end(), [numVertices](const Polygon& polygon) {
            return polygon.points.size() == numVertices;
            });
        std::cout << count << std::endl;
    }
}

void panchenko::lessArea(const std::vector<panchenko::Polygon>& polygons, const Polygon& polygon) {
    double area = getArea(polygon);
    __int64 count = std::count_if(polygons.begin(), polygons.end(), [area](const Polygon& p) {
        return getArea(p) < area;
        });
    std::cout << count << std::endl;
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

    __int64 numberOfPoints = std::distance(polygon1.points.cbegin(), polygon1.points.cend());
    return std::count_if(polygon1.points.cbegin(), polygon1.points.cend(), accSamePoints) == numberOfPoints;
}

void panchenko::same(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
{
    Polygon polygonToCompare;
    in >> polygonToCompare;

    if (!in || in.peek() != '\n')
    {
        throw std::invalid_argument(ERROR_OF_COMMAND_MSG);
    }

    using namespace std::placeholders;
    std::function< bool(const Polygon&) > accSame = std::bind(areSame, _1, polygonToCompare);

    out << std::count_if(polygons.cbegin(), polygons.cend(), accSame);
}
