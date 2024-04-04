#ifndef IO_KEYS_H
#define IO_KEYS_H

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
  
  bool IsScientificDoubleIO(std::string data);
  bool IsCharIO(std::string data);
  bool IsStringIO(std::string data);

  std::istream & operator>>(std::istream &, DelimiterIO &&);

  std::ostream & operator<<(std::ostream &, const ScientificDoubleIO &);
  std::ostream & operator<<(std::ostream &, const StringIO &);
  std::ostream & operator<<(std::ostream &, const CharIO &);
}

#endif
