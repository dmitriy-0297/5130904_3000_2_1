#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H
#include <iosfwd>
namespace elich
{
  struct DelimeterIO
  {
    char exp;
  };
  std::istream & operator>>(std::istream &, DelimeterIO &&);
}
#endif

