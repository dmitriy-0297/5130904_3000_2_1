#pragma once

#include <iostream>
#include <vector>

namespace usikov
{
  struct Data
  {
    uint64_t key1_;
    uint64_t key2_;
    std::string key3_;
    bool isFail_ = false;
  };

  struct ULLInput
  {
    uint64_t &val_;
  };

  struct HexInput
  {
    uint64_t &val_;
  };

  struct StrInput
  {
    std::string &val_;
  };

  struct Delim
  {
    std::vector<std::string> valid_;
    int length_;

    Delim( const std::vector<std::string> &ref, const int len ) :
      valid_(ref), length_(len)
    {
    }
  };

  struct Separator : public Delim
  {
    Separator( const char ch ) : Delim({std::string({ch})}, 1)
    {
    }
  };

  class StreamGuard
  {
    std::basic_ios<char> &strm_;
    char fill_;
    std::streamsize prec_;
    std::basic_ios<char>::fmtflags flags_;

  public:
    StreamGuard( std::basic_ios<char> &ref );
    ~StreamGuard( void );
  };

  std::istream & operator >>( std::istream &stream, Delim &&res );
  std::istream & operator >>( std::istream &stream, ULLInput &&res );
  std::istream & operator >>( std::istream &stream, HexInput &&res );
  std::istream & operator >>( std::istream &stream, StrInput &&res );
  std::istream & operator >>( std::istream &stream, Data &res );
  std::ostream & operator <<( std::ostream &stream, const Data &data );
}
