#ifndef DELIMETER_HPP
#define DELIMETER_HPP

#include <iostream>
#include <string>

namespace konovalova
{
  struct delimeter_char
  {
    char expected;
  };
  struct delimeter_string
  {
    std::string text;
  };
  std::istream& operator>>(std::istream& in, delimeter_char&& expected);
  std::istream& operator>>(std::istream& in, delimeter_string&& str);
}
#endif
