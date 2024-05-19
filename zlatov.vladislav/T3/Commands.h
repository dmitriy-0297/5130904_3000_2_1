#ifndef COMMANDS_H
#define COMMANDS_H

#include "Polygon.h"
#include <string>
#include <functional>

namespace zlatov
{
  void Area(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in);
  void AreaEvenPolygons(const std::vector<Polygon>& polygons, std::ostream& out);
  void AreaOddPolygons(const std::vector<Polygon>& polygons, std::ostream& out);
  void AreaAverage(const std::vector<Polygon>& polygons, std::ostream& out);
  void AreaByVertexCount(std::size_t vertexes, const std::vector<Polygon>& polygons, std::ostream& out);
  double CalculateTotalArea(const std::vector<Polygon>& polygons);
  double ComputeArea(const Polygon& polygon);

  void Max(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in);
  void MaxAreaPolygon(const std::vector<Polygon>& polygons, std::ostream& out);
  void MaxVertexCountPolygon(const std::vector<Polygon>& polygons, std::ostream& out);

  void Min(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in);
  void MinAreaPolygon(const std::vector<Polygon>& polygons, std::ostream& out);
  void MinVertexCountPolygon(const std::vector<Polygon>& polygons, std::ostream& out);

  void Count(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in);
  void CountEvenPolygons(const std::vector<Polygon>& polygons, std::ostream& out);
  void CountOddPolygons(const std::vector<Polygon>& polygons, std::ostream& out);
  void CountPolygonsByVertex(std::size_t vertexes, const std::vector<Polygon>& polygons, std::ostream& out);

  void Perms(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in);
  bool ArePermutations(const Polygon& left, const Polygon& right);
  bool VerifyPoints(const Polygon& polygon, const Point& point);

  void Rightshapes(const std::vector<Polygon>& polygons, std::ostream& out);
  bool isRightAngle(const Polygon& polygon);
  Point CreateVector(const Point& firstPoint, const Point& secondPoint);
  double CalculateCosine(const Point& firstPoint, const Point& secondPoint);

  void OutputMessage(std::ostream& out, const std::string& message);
}

#endif
