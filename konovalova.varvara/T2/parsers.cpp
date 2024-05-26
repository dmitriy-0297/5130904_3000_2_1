#include "parsers.hpp"
#include "delimeter.hpp"

#include <iostream>
#include <iomanip>
#include <string>

std::istream& konovalova::operator>>(std::istream& in, cmpType&& cmp)
{
  std::istream::sentry guard(in);
  if(!guard)
  {
    return in;
  }
  double real, imag;
  in >> std::fixed >> delimeter_string{"#c("} >> real >> imag >> delimeter_string{")"};
  cmp.data = std::complex<double>(real, imag);
  return in;
}

std::ostream& konovalova::operator<<(std::ostream& out, cmpType&& cmp)
{
  std::ostream::sentry guard(out);
  if(!guard)
  {
    return out;
  }
  out << std::fixed << std::setprecision(1);
  out << "#c(" << cmp.data.real() << " " << cmp.data.imag() << ")";
  return out;
}

std::istream& konovalova::operator>>(std::istream& in, strType&& str)
{
  std::istream::sentry guard(in);
  if(!guard)
  {
    return in;
  }
  in >> delimeter_char{'"'};
  std::getline(in, str.data, '"');
  return in;
}

std::ostream& konovalova::operator<<(std::ostream& out, strType&& str)
{
  std::ostream::sentry guard(out);
  if(!guard)
  {
    return out;
  }
  out << "\"" << str.data << "\"";
  return out;
}

std::istream& konovalova::operator>>(std::istream& in, ullOctType&& ullOct)
{
  std::istream::sentry guard(in);
  if(!guard)
  {
    return in;
  }
  in >> delimeter_char{'0'} >> std::oct >> ullOct.data;
  return in;
}

std::ostream& konovalova::operator<<(std::ostream& out, ullOctType&& ullOct)
{
  std::ostream::sentry guard(out);
  if(!guard)
  {
    return out;
  }
  out << "0" << std::oct << ullOct.data;
  return out;
}
