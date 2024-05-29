#ifndef COMMANDS_H
#define COMMANDS_H
#include "polygon.h"
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>
const std::string ERROR_OF_COMMAND_MSG = "<INVALID COMMAND>";

namespace panchenko {
    void area(const std::vector<Polygon>& polygons, const std::string& param);
    void min(const std::vector<Polygon>& polygons, const std::string& param);
    void max(const std::vector<Polygon>& polygons, const std::string& param);
    void count(const std::vector<Polygon>& polygons, const std::string& param);
    void lessArea(std::istream& in, std::ostream& out, const std::vector<Polygon>& polygons);
    void same(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons);
}

#endif
