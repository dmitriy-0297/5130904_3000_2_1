#include "io_keys.hpp"
#include <iostream>
#include <iomanip>
#include "fmtguard.hpp"

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

std::istream & elich::operator>>(std::istream & in, CharIO && dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> DelimiterIO{ '\'' } >> dest.ref >> DelimiterIO{ '\'' };
}

std::istream & elich::operator>>(std::istream & in, StringIO && dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterIO{ '"' };
  return std::getline(in, dest.ref, '"');
}

std::istream & elich::operator>>(std::istream & in, ScientificDoubleIO && dest)
{
  if (!std::istream::sentry(in))
  {
    return in;
  }

  return in >> dest.ref;
}

std::ostream & elich::operator<<(std::ostream & out, const StringIO & data)
{
  if (!std::ostream::sentry(out))
  {
    return out;
  }

  return out << '"' << data.ref << '"';
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
