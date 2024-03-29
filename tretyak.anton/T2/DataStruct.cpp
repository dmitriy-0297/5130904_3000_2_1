#include <iomanip>
#include <iostream>
#include <string>
#include "DataStruct.h"

tretyak::ResourceGard::ResourceGard(std::basic_ios<char> &strm):
 strm_(strm), 
 fill_(strm.fill()),
 precision_(strm.precision()),
 fmtFlags_(strm.flags())
{}

tretyak::ResourceGard::~ResourceGard()
{
  strm_.fill(fill_);
  strm_.precision(precision_);
  strm_.flags(fmtFlags_);
}

std::istream& tretyak::operator>>(std::istream& in, tretyak::DelimIO &&elem)
{
  std::istream::sentry sentry(in);
  if(!sentry)
  {
    return in;
  }
  std::string del;
  bool found = false;
  int tSize = elem.delim[0].size();
  in >> std::setw(tSize) >> del;
  if(!in)
  {
    return in;
  }
  for(const auto &str : elem.delim)
  {
    if(str == del)
    {
      found = true;
      break;
    }
  }
  if(!found)
  {
    in.setstate(std::ios_base::failbit);
  }
  return in;
}

std::istream& tretyak::operator>>(std::istream &in, tretyak::HexIO &&elem)
{
  std::istream::sentry sentry(in);
  ResourceGard rGard(in);
  if(!sentry)
  {
    return in;
  }
  if(!(in >> DelimIO{{"0x","0X"}}))
  { 
    return in;
  }
  if(!(in >> std::hex >> elem.ref))
  {
    return in;
  }
  return in;
}

std::istream& tretyak::operator>>(std::istream &in, tretyak::ComplexIO &&elem)
{
  std::istream::sentry sentry(in);
  if(!sentry)
  {
    return in;
  }
  std::string del;
  double real, imag;
  if(!(in >> DelimIO{{"#c("}}))
  {
    return in;
  }
  if(!(in >> real >> imag))
  {
    return in;
  }
  if(!(in >> DelimIO{{")"}}))
  {
    return in;
  }
  elem.ref = std::complex<double>(real, imag);
  return in;
}

std::istream& tretyak::operator>>(std::istream &in, tretyak::StringIO &&elem)
{
  std::istream::sentry sentry(in);
  if(!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimIO{{"\""}}, elem.ref, '"');
}

std::istream& tretyak::operator>>(std::istream &in, tretyak::Data &elem)
{
  std::istream::sentry sentry(in);
  if(!sentry)
  {
    return in;
  }

  in >> DelimIO{{"(:"}};
  if(!in)
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }

  for(int i = 0; i < 3; i++)
  {
    std::string key;
    if(!(in >> key))
    {
      in.setstate(std::ios_base::failbit);
      return in;
    }
    if(key == "key1")
    {
      in >> HexIO{elem.key1};
    }
    else if(key == "key2")
    {
      in >> ComplexIO{elem.key2};
    }
    else if(key == "key3")
    {
      in >> StringIO{elem.key3};
    }
    else
    {
      in.setstate(std::ios_base::failbit);
      return in;
    }
    in >> DelimIO{{":"}};
    if(!in)
    {
      in.setstate(std::ios_base::failbit);
      return in;
    }
  }
  in >> DelimIO{{")"}};
  if(!in)
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  if(!in)
  {
    elem.status = false;
    in.clear();
    while (in.get() != '\n' && in.peek() != EOF) {}
  }
  return in;
}

std::ostream& tretyak::operator<<(std::ostream &op, const tretyak::Data &elem)
{
  std::ostream::sentry sentry(op);
  if(!sentry)
  {
    return op;
  }
  ResourceGard rGard(op);

  op << "(:key1 " << std::uppercase << std::hex << "0x" << elem.key1 <<
        ":key2 " << "#e" << elem.key2 <<
        ":key3 \"" << elem.key3 << "\":)";
  return op;
}
