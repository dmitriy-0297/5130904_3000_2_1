#ifndef _IO_H
#define _IO_H

#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include "geometry.h"

namespace shmonov
{
  std::istream & operator>>(std::istream &in, Point &point);
  std::istream & operator>>(std::istream &in, Polygon &polygon);
  bool isPoint(const std::string &str);
}
#endif
