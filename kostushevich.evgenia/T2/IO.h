#pragma once
#include <iostream>
#include <iterator>
#include <complex>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

namespace kostushevich
{
  struct DataStruct
  {
    unsigned long long key1;
    std::complex<double> key2;
    std::string key3;
  };
  struct DelimiterIO
  {
    char exp;
  };
  struct OctIO
  {
    unsigned long long& ref;
  };
  struct ComplexIO
  {
    std::complex<double>& ref;
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
  std::istream& operator>>(std::istream& in, OctIO&& dest);
  std::istream& operator>>(std::istream& in, ComplexIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
}