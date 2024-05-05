#ifndef PARSERS_HPP
#define PARSERS_HPP

#include <iostream>
#include <complex>

namespace konovalova
{
  struct cmpType
  {
    std::complex<double>& data;
  };
  std::istream& operator>>(std::istream& in, cmpType&& cmp);
  std::ostream& operator<<(std::ostream& out, cmpType&& cmp);
  struct strType
  {
    std::string& data;
  };
  std::istream& operator>>(std::istream& in, strType&& str);
  std::ostream& operator<<(std::ostream& out, strType&& str);
  struct ullOctType
  {
    unsigned long long& data;
  };
  std::istream& operator>>(std::istream& in, ullOctType&& ullOct);
  std::ostream& operator<<(std::ostream& out, ullOctType&& ullOct);
}
#endif
