#ifndef COMMANDS_H
#define COMMANDS_H

#include "Polygon.h"
#include <string>
#include <functional>

namespace zlatov
{
  void area(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in);
  void areaEvenPolygons(const std::vector<Polygon>& polygons, std::ostream& out);
  void areaOddPolygons(const std::vector<Polygon>& polygons, std::ostream& out);
  void areaAverage(const std::vector<Polygon>& polygons, std::ostream& out);
  void areaByVertexCount(std::size_t vertexes, const std::vector<Polygon>& polygons, std::ostream& out);
  double calculateTotalArea(const std::vector<Polygon>& polygons);
  double computeArea(const Polygon& polygon);

  void max(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in);
  void maxAreaPolygon(const std::vector<Polygon>& polygons, std::ostream& out);
  void maxVertexCountPolygon(const std::vector<Polygon>& polygons, std::ostream& out);

  void min(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in);
  void minAreaPolygon(const std::vector<Polygon>& polygons, std::ostream& out);
  void minVertexCountPolygon(const std::vector<Polygon>& polygons, std::ostream& out);

  void count(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in);
  void countEvenPolygons(const std::vector<Polygon>& polygons, std::ostream& out);
  void countOddPolygons(const std::vector<Polygon>& polygons, std::ostream& out);
  void countPolygonsByVertex(std::size_t vertexes, const std::vector<Polygon>& polygons, std::ostream& out);

  void perms(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in);
  bool arePermutations(const Polygon& left, const Polygon& right);
  bool verifyPoints(const Polygon& polygon, const Point& point);

  void rightshapes(const std::vector<Polygon>& polygons, std::ostream& out);
  bool isRightAngle(const Polygon& polygon);
  Point createVector(const Point& firstPoint, const Point& secondPoint);
  double calculateCosine(const Point& firstPoint, const Point& secondPoint);

  void outputMessage(std::ostream& out, const std::string& message);
}

#endif
