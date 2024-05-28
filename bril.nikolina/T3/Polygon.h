#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <string>
#include <iostream>

struct Point {
    int x, y;
    bool operator==(const Point& other) const;
};

struct Polygon {
    std::vector<Point> points;
    bool operator==(const Polygon& other) const;
};

double polygonArea(const Polygon& polygon);
bool isRightAngle(const Point& a, const Point& b, const Point& c);
bool hasRightAngle(const Polygon& polygon);
std::vector<Polygon> readPolygonsFromFile(const std::string& filename);
void executeCommand(const std::string& command, std::vector<Polygon>& polygons);
void printAreaResult(double result);

#endif
