#include "delimeter.hpp"

#include <iostream>
#include <string>

std::istream& konovalova::operator>>(std::istream& in, delimeter_char&& expected)
{
  std::istream::sentry guard(in);
  if(!guard)
  {
    return in;
  }
  char c;
  in >> c;
  if(c != expected.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& konovalova::operator>>(std::istream& in, delimeter_string&& str)
{
  std::istream::sentry guard(in);
  if(!guard)
  {
    return in;
  }
  char c;
  for (size_t i = 0; i < str.text.size(); i++)
  {
    in >> c;
    if(c != str.text[i])
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}
