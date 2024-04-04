#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <iosfwd>
#include <string>

namespace elich
{
  struct Data
  {
    double key1;
    char key2;
    std::string key3;
    bool valid;
  };
  std::istream & operator>>(std::istream &, Data &);
  std::ostream & operator<<(std::ostream &, const Data &);
  bool operator<(const Data &, const Data &);
}

#endif
