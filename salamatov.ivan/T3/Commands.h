#ifndef __COMMANDS_H_
#define __COMMANDS_H_

#include <vector>

#include "Structs.h"

namespace command
{
  int is_a_num(const std::string& str);
  void area(const std::vector<salamatov::Polygon>& data);
  void max(const std::vector<salamatov::Polygon>& data);
  void min(const std::vector<salamatov::Polygon>& data);
  void count(const std::vector<salamatov::Polygon>& data);
  void same(std::vector<salamatov::Polygon>& data);
  void rmecho(std::vector<salamatov::Polygon>& data);
}

#endif

