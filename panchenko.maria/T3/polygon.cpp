#include "polygon.h"

std::istream& panchenko::operator>>(std::istream& input, Point& point) {
    char openParen, semicolon, closeParen;
    int x, y;

    if (input >> openParen >> x >> semicolon >> y >> closeParen) {
        if (openParen == '(' && semicolon == ';' && closeParen == ')') {
            point.x = x;
            point.y = y;
        } else {
            input.setstate(std::ios_base::failbit);
        }
    } else {
        input.setstate(std::ios_base::failbit);
    }

    return input;
}

std::istream& panchenko::operator>>(std::istream& input, Polygon& polygon) {
    size_t numVertices;
    std::vector<Point> points;

    if (!(input >> numVertices)) {
        input.setstate(std::ios_base::failbit);
    }
    if (numVertices < 2) {
        input.setstate(std::ios_base::failbit);
    }
    points.resize(numVertices);

    for (size_t i = 0; i < numVertices; ++i) {
        if (!(input >> points[i])) {
            input.setstate(std::ios_base::failbit);
        }
    }

    if (points.size() != numVertices) {
        input.setstate(std::ios_base::failbit);
    }

    polygon.points = points;

    return input;
}

std::ostream& panchenko::operator<<(std::ostream& output, const Point& point) {
    output << "(" << point.x << ";" << point.y << ")";
    return output;
}
bool panchenko::comparePoints(const Point& point1, const Point& point2)
{
    return (point1.x == point2.x) && (point1.y == point2.y);
}

std::ostream& panchenko::operator<<(std::ostream& output, const Polygon& polygon) {
    output << polygon.points.size();
    for (const auto& point : polygon.points) {
        output << " " << point;
    }
    return output;
}
double panchenko::getArea(const Polygon& polygon) {
    double area = 0.0;
    size_t n = polygon.points.size();

    for (size_t i = 0; i < n; ++i) {
        const Point& p1 = polygon.points[i];
        const Point& p2 = polygon.points[(i + 1) % n];
        area += (p1.x * p2.y - p2.x * p1.y);
    }

    return std::abs(area) / 2.0;
}
