#ifndef _IO_H
#define _IO_H

#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <iomanip>

namespace shmonov
{
  bool isDBL_SCI(const std::string& str);
  bool isChar(const std::string& str);
  bool isString(const std::string& str);

  struct DataStruct
  {
    double key1;  // DBL SCI 5.45e-2
    char key2;  // CHR LIT 'c'
    std::string key3;
    bool valid;
  };

  std::istream& operator>>(std::istream& in, DataStruct& ds);
  std::ostream& operator<<(std::ostream& out, const DataStruct& ds);
  std::string myScientific(double x);
  
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
