#ifndef IO_KEYS_HPP
#define IO_KEYS_HPP

#include <iosfwd>
#include <string>

namespace elich
{
  struct DelimiterIO
  {
    char exp;
  };

  struct CharIO
  {
    char & ref;
  };

  struct StringIO
  {
    std::string & ref;
  };

  struct ScientificDoubleIO
  {
    double & ref;
  };

  std::istream & operator>>(std::istream &, DelimiterIO &&);
  std::istream & operator>>(std::istream &, CharIO &&);
  std::istream & operator>>(std::istream &, StringIO &&);
  std::istream & operator>>(std::istream &, ScientificDoubleIO &&);

  std::ostream & operator<<(std::ostream &, const ScientificDoubleIO &);
  std::ostream & operator<<(std::ostream &, const StringIO &);
  std::ostream & operator<<(std::ostream &, const CharIO &);
}

#endif
