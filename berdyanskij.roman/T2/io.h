// struct.hpp
#ifndef IO__CPP
#define IO_H

#include <iostream>
#include <string>

namespace berdyanskij {
  struct DataStruct {
    double key1; // DBL SCI
    long long key2; // SLL LIT
    std::string key3;
  };

  std::istream& operator>>(std::istream& is, DataStruct& ds);
  std::ostream& operator<<(std::ostream& os, const DataStruct& ds);
}
#endif // IO_H
