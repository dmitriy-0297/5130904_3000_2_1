include "commands.h"


using namespace std;
using namespace panchenko;

vector<Polygon> polygons;

void panchenko::area(const string& param) {
    if (param == "ODD") {
        double sum = 0.0;
        for (const auto& polygon : polygons) {
            if (polygon.points.size() % 2 == 1) {
                sum += getArea(polygon);
            }
        }
        cout << fixed << sum << endl;
    }
    else if (param == "EVEN") {
        double sum = 0.0;
        for (const auto& polygon : polygons) {
            if (polygon.points.size() % 2 == 0) {
                sum += getArea(polygon);
            }
        }
        cout << fixed << sum << endl;
    }
    else if (param == "MEAN") {
        if (polygons.empty()) {
            cout << "0.0" << endl;
            return;
        }
        double sum = 0.0;
        for (const auto& polygon : polygons) {
            sum += getArea(polygon);
        }
        cout << fixed << sum / polygons.size() << endl;
    }
    else {
        int numVertices = stoi(param);
        double sum = 0.0;
        for (const auto& polygon : polygons) {
            if (polygon.points.size() == numVertices) {
                sum += getArea(polygon);
            }
        }
        cout << fixed << sum << endl;
    }
}

void panchenko::min() {
    if (polygons.empty()) {
        cout << "<INVALID COMMAND>" << endl;
        return;
    }
    auto minAreaPolygon = min_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b) {
        return getArea(a) < getArea(b);
        });
    cout << fixed << getArea(*minAreaPolygon) << endl;
}

void panchenko::max() {
    if (polygons.empty()) {
        cout << "<INVALID COMMAND>" << endl;
        return;
    }
    auto maxAreaPolygon = max_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b) {
        return getArea(a) < getArea(b);
        });
    cout << fixed << getArea(*maxAreaPolygon) << endl;
}

void panchenko::count(const string& param) {
    if (param == "EVEN") {
        int count = count_if(polygons.begin(), polygons.end(), [](const Polygon& polygon) {
            return polygon.points.size() % 2 == 0;
            });
        cout << count << endl;
    }
    else if (param == "ODD") {
        int count = count_if(polygons.begin(), polygons.end(), [](const Polygon& polygon) {
            return polygon.points.size() % 2 == 1;
            });
        cout << count << endl;
    }
    else {
        int numVertices = stoi(param);
        int count = count_if(polygons.begin(), polygons.end(), [numVertices](const Polygon& polygon) {
            return polygon.points.size() == numVertices;
            });
        cout << count << endl;
    }
}

void panchenko::lessArea(const Polygon& polygon) {
    double area = getArea(polygon);
    int count = count_if(polygons.begin(), polygons.end(), [area](const Polygon& p) {
        return getArea(p) < area;
        });
    cout << count << endl;
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
        throw std::invalid_argument("<INVALID COMMAND>");
    }

    using namespace std::placeholders;
    std::function< bool(const Polygon&) > accSame = std::bind(areSame, _1, polygonToCompare);

    out << count_if(polygons.cbegin(), polygons.cend(), accSame);
}
