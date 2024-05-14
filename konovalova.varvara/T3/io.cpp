#include "fig.hpp"

std::istream & konovalova::operator >> (std::istream &in, Point &pnt)
{
    std::istream::sentry guard(in);
    if (!guard) {
        return in;
    }

    in >> Delimeter{'('} >> pnt.x >> Delimeter{';'} >> pnt.y >> Delimeter{')'};
    return in;
}

std::ostream & konovalova::operator << (std::ostream &out, const Point &pnt)
{
    std::ostream::sentry guard(out);
    if (!guard) {
        return out;
    }

    out << "(" << pnt.x << "; " << pnt.y << ")";
    return out;
}

std::istream & konovalova::operator >> (std::istream &in, Polygon &poly)
{
    std::istream::sentry guard(in);
    if (!guard) {
        return in;
    }

    size_t size;
    in >> size;

    if (size < 3)
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    poly.points.clear();
    poly.points.resize(size);

    for (auto &p : poly.points) {
        in >> p;
    }

    return in;
}

std::ostream & konovalova::operator << (std::ostream &out, const Polygon &poly)
{
    std::ostream::sentry guard(out);
    if (!guard) {
        return out;
    }

    out << poly.points.size() << " ";

    for (const auto &p : poly.points) {
        out << p << " ";
    }
    return out;
}

std::istream & konovalova::operator >> (std::istream &in, Delimeter &&del)
{
    std::istream::sentry guard(in);
    if (!guard) {
        return in;
    }

    char c;
    in >> c;
    if (c != del.expected) {
        in.setstate(std::ios::failbit);
    }
    return in;
}