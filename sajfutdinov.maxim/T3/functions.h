#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include <iomanip>

const std::string INVALID_COMMAND = "<INVALID COMMAND>\n";

namespace sajfutdinov {
	struct Point {
		int x, y;
		Point() : x(0), y(0) {};
		Point(int x_, int y_) : x(x_), y(y_) {};
		Point(const Point& point) : x(point.x), y(point.y) {};
		bool operator==(const Point& point) const { return x == point.x && y == point.y; }
	};

	struct Polygon {
		std::vector<Point> points;
	};

	struct AreaCalculator {
		double operator()(const Polygon& poly) const;
	};

	void calculateArea(const std::vector<Polygon>& polygons, const std::string& type);

	void calculateMax(const std::vector<Polygon>& polygons, const std::string& type);

	void calculateMin(const std::vector<Polygon>& polygons, const std::string& type);

	void countPolygons(const std::vector<Polygon>& polygons, const std::string& type);

	void lessArea(const std::vector<Polygon>& polygons, const std::string& strPoly);

	double cross(const Point& O, const Point& A, const Point& B);

	bool isPointOnSegment(const Point& p, const Point& a, const Point& b);

	bool doSegmentsIntersect(const Point& p1, const Point& p2, const Point& q1, const Point& q2);

	bool isPointInsidePolygon(const Point& p, const Polygon& poly);

	bool doPolygonsIntersect(const Polygon& poly1, const Polygon& poly2);


	void intersections(const std::vector<Polygon>& polygons, const std::string& strPoly);
}

#endif
