#include "polygon.h"

std::istream& panchenko::operator>>(std::istream& input, Point& point) {
    std::regex pointRegex("\\((-?\\d+);(-?\\d+)\\)");
    std::string pointStr;
    std::smatch matches;

    if (std::getline(input, pointStr)) {
        if (std::regex_match(pointStr, matches, pointRegex)) {
            point.x = std::stoi(matches[1]);
            point.y = std::stoi(matches[2]);
        }
        else {
            input.setstate(std::ios_base::failbit);
        }
    }

    return input;
}

std::istream& panchenko::operator>>(std::istream& input, Polygon& polygon) {
    std::regex numVerticesRegex("(\\d+)");
    std::string line;
    std::smatch matches;

    if (std::getline(input, line)) {
        if (std::regex_search(line, matches, numVerticesRegex)) {
            size_t numVertices = std::stoi(matches[1]);
            polygon.points.resize(numVertices);

            std::regex pointRegex("\\((-?\\d+);(-?\\d+)\\)");

            for (size_t i = 0; i < numVertices; ++i) {
                if (std::getline(input, line)) {
                    if (std::regex_match(line, matches, pointRegex)) {
                        polygon.points[i].x = std::stoi(matches[1]);
                        polygon.points[i].y = std::stoi(matches[2]);
                    }
                    else {
                        input.setstate(std::ios_base::failbit);
                        break;
                    }
                }
            }
        }
        else {
            input.setstate(std::ios_base::failbit);
        }
    }

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
