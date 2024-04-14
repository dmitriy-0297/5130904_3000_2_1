#ifndef _IO_H
#define _IO_H

#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <iomanip>

namespace berdyanskij
{
  bool is_double(const std::string& str);
  bool is_long(const std::string& str);
  bool is_string(const std::string& str);

  struct DataStruct
  {
    double key1;  // DBL SCI 5.45e-2
    long long key2;  // SLL LIT 2ll
    std::string key3;
    bool valid;
  };

  std::istream& operator>>(std::istream& in, DataStruct& ds);
  std::ostream& operator<<(std::ostream& out, const DataStruct& ds);

  std::string get_scientific(double x);
  std::pair<std::string, std::string> get_next_pair(std::string& s);

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
}
#endif
