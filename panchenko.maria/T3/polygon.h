#ifndef POLYGON_H
#define POLYGON_H
#include <vector>
#include <iostream>

namespace panchenko {
	struct Point
	{
		int x, y;

	};

	struct Polygon
	{
		std::vector<Point> points;
	};

	std::istream& operator>>(std::istream& input, Point& point);
	std::ostream& operator<<(std::ostream& output, const Point& point);
	bool comparePoints(const Point&, const Point&);

	std::istream& operator>>(std::istream& input, Polygon& polygon);
	std::ostream& operator<<(std::ostream& output, const Polygon& polygon);
	double getArea(const Polygon& polygon);
}

#endif
