#ifndef __COMMAND_H_
#define __COMMAND_H_

#include <vector>

#include "fig.hpp"

namespace command
{
    int is_a_num(const std::string& str);
    void area(const std::vector<konovalova::Polygon>& data);
    void max(const std::vector<konovalova::Polygon>& data);
    void min(const std::vector<konovalova::Polygon>& data);
    void count(const std::vector<konovalova::Polygon>& data);
    void rmecho(std::vector<konovalova::Polygon>& data);
    void same(std::vector<konovalova::Polygon>& data);
}

#endif
