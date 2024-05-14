#include <functional>
#include <algorithm>
#include <numeric>

#include "fig.hpp"

using namespace std::placeholders;

bool konovalova::Point::operator==(const Point &other) const
{
    return x == other.x && y == other.y;
}

bool konovalova::Point::operator!=(const Point &other) const
{
    return x != other.x || y != other.y;
}

bool konovalova::Point::operator<(const Point &other) const
{
    if (x == other.x) return y < other.y;
    return x < other.x;
}

bool konovalova::Polygon::operator==(const Polygon &other) const
{
    if (points.size() != other.points.size()) return false;

    auto other_pnt = other.points.begin();
    auto testFunc = [&other_pnt] (const Point &pnt)
    {
        bool result = pnt == *other_pnt;
        other_pnt++;
        return result;
    };
    return std::all_of(points.begin(), points.end(), testFunc);
}

bool konovalova::Polygon::operator<(const Polygon &other) const
{
    return area() < other.area();
}

double konovalova::Polygon::area(void) const
{
    double res = 0;
    for (int i = 1; i < points.size(); i++) {
        res += points[i - 1].x * points[i].y;
        res -= points[i].x * points[i - 1].y;
    }
    res += (*points.rbegin()).x * (*points.begin()).y;
    res -= (*points.rbegin()).y * (*points.begin()).x;
    return 0.5 * abs(res);
}

bool konovalova::Polygon::is_overlay_compatible(const Polygon &other) const
{
    if (points.size() != other.points.size()) return false;
    
    std::vector<konovalova::Point> sorted_points(points);
    std::sort(sorted_points.begin(), sorted_points.end());

    double x_offset = other.points[0].x - sorted_points[0].x;
    double y_offset = other.points[0].y - sorted_points[0].y;

    auto sorted_pnt = sorted_points.begin();
    auto testFunc = [&sorted_pnt, &x_offset, &y_offset] (const Point &pnt)
    {
        bool result = pnt.x - (*sorted_pnt).x == x_offset
        && pnt.y - (*sorted_pnt).y == y_offset;
        sorted_pnt++;
        return result;
    };
    return std::all_of(other.points.begin(), other.points.end(), testFunc);
}