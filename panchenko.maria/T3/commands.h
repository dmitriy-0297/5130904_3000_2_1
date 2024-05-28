#ifndef COMMANDS_H
#define COMMANDS_H
#include "polygon.h"
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <cmath>
#include <string>
const std::string ERROR_OF_COMMAND_MSG = "<INVALID COMMAND>";

namespace panchenko {
    void area(const std::vector<panchenko::Polygon>& polygons, const std::string& param);
    void min(const std::vector<panchenko::Polygon>& polygons);
    void max(const std::vector<panchenko::Polygon>& polygons);
    void count(const std::vector<panchenko::Polygon>& polygons, const std::string& param);
    void lessArea(const std::vector<panchenko::Polygon>& polygons, const panchenko::Polygon& polygon);
    void same(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons);
}

#endif
