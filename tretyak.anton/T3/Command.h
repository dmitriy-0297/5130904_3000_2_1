#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include "Geometry.h"

namespace cmd
{
  int validStringToInt(std::string str);
  void area(std::vector<tretyak::Polygon> &value, const std::string str);
  void max(std::vector<tretyak::Polygon> &value, const std::string str);
  void min(std::vector<tretyak::Polygon> &value, const std::string str);
  void count(std::vector<tretyak::Polygon> &value, const std::string str);
  void lessArea(std::vector<tretyak::Polygon> &value);
  void maxSeq(std::vector<tretyak::Polygon> &value);
}

#endif // COMMAND_H
