#ifndef _DATA_STRUCT_H
#define _DATA_STRUCT_H

#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <iterator>

namespace madyarov
{
  struct DataStruct
  {
    unsigned long long key1;
    std::complex<double> key2;
    std::string key3;
    bool reg;
  };

  struct HexIO
  {
    unsigned long long& data;
  };

  struct ComplexIO
  {
    std::complex<double>& data;
  };

  struct StringIO
  {
    std::string& data;
  };

  struct DelimiterIO
  {
    char symbol;
  };

  bool compareDataStruct(const DataStruct& a, const DataStruct& b);

  std::istream& operator>>(std::istream& in, DataStruct& ds);
  std::istream& operator>>(std::istream& in, HexIO&& ds);
  std::istream& operator>>(std::istream& in, ComplexIO&& ds);
  std::istream& operator>>(std::istream& in, StringIO&& ds);
  std::istream& operator>>(std::istream& in, DelimiterIO&& ds);
  std::ostream& operator<<(std::ostream& out, const DataStruct& ds);
}
#endif
