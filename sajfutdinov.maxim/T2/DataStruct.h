#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <iomanip>
#include <algorithm>

namespace sajfutdinov
{
  struct DataStruct
  {
      char key1;
      std::pair<long long, unsigned long long> key2;
      std::string key3;
  };

  struct DelimiterIO
  {
      char exp;
  };

  struct RationalIO
  {
      std::pair< long long, unsigned long long >& ref;
  };

  struct StringIO
  {
      std::string& ref;
  };

  struct LabelIO
  {
      std::string exp;
  };

  class iofmtguard
  {
  public:
      iofmtguard(std::basic_ios< char >& s);
      ~iofmtguard();
  private:
      std::basic_ios< char >& s_;
      char fill_;
      std::streamsize precision_;
      std::basic_ios< char >::fmtflags fmt_;
  };


  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, RationalIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
  bool compareData(const DataStruct& a, const DataStruct& b);
}

#endif
