#ifndef IO_H
#define IO_H

#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include "figures.h"

namespace berdyanskij
{
  std::istream& operator>>(std::istream& in, berdyanskij::Point& poly);
  std::istream& operator>>(std::istream& in, berdyanskij::Polygon& poly);
  std::ostream& operator<<(std::ostream& out, const berdyanskij::Point& point);
  bool isPoint(std::string& str);
}
#endif
