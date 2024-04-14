#ifndef DELIMITER_H
#define DELIMITER_H

#include <istream>

struct DelimiterChar {
  char delimiter;
};

std::istream& operator>>(std::istream& in, const DelimiterChar& exp);

struct DelimiterString {
  const char* delimiter;
};

std::istream& operator>>(std::istream& in, DelimiterString&& exp);

#endif
