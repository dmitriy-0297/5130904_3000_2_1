#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <string>
#include <iostream>

struct DataStruct {
  double key1;
  unsigned long long key2;
  std::string key3;

  bool operator<(const DataStruct& rhs) const;
};

std::istream& operator>>(std::istream& in, DataStruct& data);
std::ostream& operator<<(std::ostream& out, const DataStruct& data);

#endif
