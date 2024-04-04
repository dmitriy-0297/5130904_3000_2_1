#include "io_keys.h"
#include <iostream>
#include <iomanip>
#include <regex>
#include "fmtguard.h"

std::istream & elich::operator>>(std::istream & in, DelimiterIO && dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (c != dest.exp))
  {
      in.setstate(std::ios::failbit);
  }
  return in;
}

bool elich::IsCharIO(std::string data) {
    std::regex pattern("'.'");
    if (std::regex_match(data, pattern))
        return true;
    else
        return false;
}

bool elich::IsStringIO(std::string data) {
    std::regex pattern("\".*\"");
    if (std::regex_match(data, pattern))
        return true;
    else
        return false;
}

bool elich::IsScientificDoubleIO(std::string data) {

    std::regex pattern("^[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)$");
    if (std::regex_match(data, pattern))
        return true;
    else
        return false;
}

std::ostream & elich::operator<<(std::ostream & out, const StringIO & data)
{
  if (!std::ostream::sentry(out))
  {
    return out;
  }

  return out << data.ref;
}

std::ostream & elich::operator<<(std::ostream & out, const ScientificDoubleIO & data)
{
  if (!std::ostream::sentry(out))
  {
    return out;
  }

  int eToThe = 0;
  double numberDouble = data.ref;
  if (numberDouble < 1 && numberDouble != 0)
  {
    for (; numberDouble < 1; eToThe--)
    {
      numberDouble *= 10;
    }
  }
  else
  {
    for (; numberDouble > 9; eToThe++)
    {
      numberDouble /= 10;
    }
  }

  iofmtguard guard(out);
  out << std::fixed << std::setprecision(2);
  out << numberDouble << 'e' << std::showpos << eToThe;
  return out;
}

std::ostream & elich::operator<<(std::ostream & out, const CharIO & data)
{
  if (!std::ostream::sentry(out))
  {
    return out;
  }

  return out << '\'' << data.ref << '\'';
}
