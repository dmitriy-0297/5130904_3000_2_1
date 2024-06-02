#include "data_struct.h"
#include <iostream>
std::istream & elich::operator>>(std::istream & in, DelimeterIO && dest)
{
  if (!std::istream::sentry(in))
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (c != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

