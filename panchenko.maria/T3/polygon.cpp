#include "polygon.h"
#include "delimiter.h"
#include <algorithm>

std::istream& panchenko::operator>>(std::istream& in, Point& point) {
    std::istream::sentry guard(in);
    if (!guard)
    {
        return in;
    }
    in >> Delimiter{"("} >> point.x >> Delimiter{";"} >> point.y >> Delimiter{")"};
    return in;
}

std::istream& panchenko::operator>>(std::istream& in, Polygon& polygon) {
    std::istream::sentry guard(in);
    if (!guard)
    {
        return in;
    }
    size_t num = 0;
    in >> num;
    if (num < 3)
    {
        in.setstate(std::ios::failbit);
        return in;
    }
    polygon.points.clear();
    std::copy_n(
        std::istream_iterator< Point >(in),
        num,
        std::back_inserter(polygon.points)
    );
    return in;
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
