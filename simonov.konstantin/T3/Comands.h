#ifndef _COMMANDS_H
#define _COMMANDS_H
#include "Polygons.h"
#include <vector>

int stringIsInt(std::string str);
void area(const std::vector<simonov::Polygon>& poly, const std::string str);
void min(const std::vector<simonov::Polygon>& poly, const std::string str);
void max(const std::vector<simonov::Polygon>& poly, const std::string str);
void count(const std::vector<simonov::Polygon>& poly, const std::string str);
void echo(std::vector<simonov::Polygon>& data, const std::string str, const simonov::Polygon& poly);
void rightShapes(const std::vector<simonov::Polygon>& poly, const std::string str);

#endif
