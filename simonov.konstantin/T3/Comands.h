#ifndef _COMMANDS_H
#define _COMMANDS_H
#include "Polygons.h"
#include <vector>

void area(const std::vector<simonov::Polygon>& poly);
void min(const std::vector<simonov::Polygon>& poly);
void max(const std::vector<simonov::Polygon>& poly);
void count(const std::vector<simonov::Polygon>& poly);
void echo(std::vector<simonov::Polygon>& data);
void rightShapes(const std::vector<simonov::Polygon>& poly);

#endif
