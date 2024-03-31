#include "Delimiter.h"

std::istream& operator>>(std::istream& in, const DelimiterChar& exp) {
  char c = 0;
  in >> c;
  if (c != exp.delimiter) {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& operator>>(std::istream& in, DelimiterString&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  size_t i = 0;
  while (exp.delimiter[i] != '\0')
  {
    in >> DelimiterChar{ exp.delimiter[i] };
    ++i;
  }
  return in;
}
