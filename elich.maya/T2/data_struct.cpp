#include "data_struct.hpp"

#include <iostream>
#include <iomanip>

#include "fmtguard.hpp"
#include "io_keys.hpp"

std::istream & elich::operator>>(std::istream & in, Data & dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Data input;
  in >> DelimiterIO{ '(' } >> DelimiterIO{ ':' };
  for (auto i = 0; i < 3 && in; i++)
  {
    std::string key = "";

    in >> key;
    if (key == "key1")
    {
      in >> ScientificDoubleIO{ input.key1 };
    }
    else if (key == "key2")
    {
      in >> CharIO{ input.key2 };
    }
    else if (key == "key3")
    {
      in >> StringIO{ input.key3 };
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
    in >> DelimiterIO{ ':' };
  }
  in >> DelimiterIO{ ')' };

  if (in)
  {
    dest = input;
  }
  return in;
}

std::ostream & elich::operator<<(std::ostream & out, const Data & src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  Data tmp = src;
  iofmtguard fmtguard(out);
  out << "(:key1 " << ScientificDoubleIO{ tmp.key1 };
  out << ":key2 " << CharIO{ tmp.key2 };
  out << ":key3 " << StringIO{ tmp.key3 } << ":)";
  return out;
}

bool elich::operator<(const Data & a, const Data & b)
{
  if (a.key1 != b.key1)
  {
    return a.key1 < b.key1;
  }
  if (a.key2 != b.key2)
  {
    return a.key2 < b.key2;
  }
  return a.key3.length() < b.key3.length();
}
