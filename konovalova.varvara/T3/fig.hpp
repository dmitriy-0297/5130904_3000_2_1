#ifndef __FIG_H_
#define __FIG_H_

#include <iostream>
#include <vector>

namespace konovalova
{
    struct Point
    {
        int x, y;

        bool operator==(const Point &other) const;
        bool operator!=(const Point &other) const;
        bool operator<(const Point &other) const;
    };
    std::istream & operator >> (std::istream & in, Point &pnt);
    std::ostream & operator << (std::ostream & out, const Point &pnt);

    struct Polygon
    {
        std::vector<Point> points;

        bool operator==(const Polygon &other) const;
        bool operator<(const Polygon &other) const;
        double area(void) const;
    };
    std::istream & operator >> (std::istream & in, Polygon &poly);
    std::ostream & operator << (std::ostream & out, const Polygon &poly);

    struct Delimeter
    {
        char expected;
    };
    std::istream & operator >> (std::istream &in, Delimeter &&del);
}

#endif