#include "polygon.h"

std::istream& panchenko::operator>>(std::istream& input, Point& point) {
    char c;
    input >> c; // Считываем '('
    input >> point.x;
    input >> c; // Считываем ';'
    input >> point.y;
    input >> c; // Считываем ')'
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

std::istream& panchenko::operator>>(std::istream& input, Polygon& polygon) {
    size_t numVertices;
    input >> numVertices;

    polygon.points.resize(numVertices);
    for (size_t i = 0; i < numVertices; ++i) {
        input >> polygon.points[i];
    }

    return input;
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
