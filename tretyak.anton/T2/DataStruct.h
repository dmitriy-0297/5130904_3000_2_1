#ifndef _DATASTRUCT_H_
#define _DATASTRUCT_H_

#include <iostream>
#include <vector>
#include <complex>

namespace tretyak
{
  struct Data
  {
    unsigned long long key1;
    std::complex<double> key2;
    std::string key3;
    bool status = true;
  };

  struct HexIO
  {
    unsigned long long &ref;
  };

  struct ComplexIO
  {
    std::complex<double> &ref;
  };

  struct StringIO
  {
    std::string &ref;
  };

  struct LabelIO
  {
    std::string exp;
  };

  struct DelimIO
  {
    std::vector<std::string> delim;
  };

  class ResourceGard
  {
  public:
    ResourceGard(std::basic_ios<char> &strm);
    ~ResourceGard();
  private:
    std::basic_ios<char> &strm_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags fmtFlags_;
  };

  std::istream& operator>>(std::istream &in, DelimIO &&elem);
  std::istream& operator>>(std::istream &in, HexIO &&elem);
  std::istream& operator>>(std::istream &in, ComplexIO &&elem);
  std::istream& operator>>(std::istream &in, StringIO &&elem);
  std::istream& operator>>(std::istream &in, Data &elem);
  std::ostream& operator<<(std::ostream &op, const Data &elem);
}

#endif // _DATASTRUCT_H_
