#include "polygonPredicats.h"
bool elich::isOddVertexes(const Polygon & polygon)
{
  return getPolygonVertexes(polygon) % 2 == 1;
}
bool elich::isEvenVertexes(const Polygon & polygon)
{
  return getPolygonVertexes(polygon) % 2 == 0;
}

