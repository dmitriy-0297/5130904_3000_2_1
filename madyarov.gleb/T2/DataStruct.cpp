#include "DataStruct.h"

std::istream& madyarov::operator>>(std::istream& in, HexIO&& ds)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> std::hex >> ds.data;
  return in;
}

std::istream& madyarov::operator>>(std::istream& in, ComplexIO&& ds)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  double real, imag;
  in >> real >> std::noskipws >> c >> imag;
  ds.data = std::complex<double>(real, imag);
  return in;
}

std::istream& madyarov::operator>>(std::istream& in, StringIO&& ds)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::string value;
  in >> std::quoted(value);
  ds.data = value;
  return in;
}

std::istream& madyarov::operator>>(std::istream& in, DelimiterIO&& ds)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> std::noskipws >> c;
  if (in && (c != ds.symbol))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& madyarov::operator>>(std::istream& in, DataStruct& ds)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterIO{ '(' };

  for (int i = 0; i < 3; i++)
  {
    std::string key;
    in >> DelimiterIO{ ':' };
    in >> key;

    if (key == "key1")
    {
      in >> DelimiterIO{ ' ' };
      in >> DelimiterIO{ '0' };
      if (in.peek() == 'x')
      {
        in >> DelimiterIO{ 'x' };
        ds.reg = true;
      }
      else
      {
        in >> DelimiterIO{ 'X' };
        ds.reg = false;
      }
      in >> HexIO{ ds.key1 };
    }
    else if (key == "key2")
    {
      in >> DelimiterIO{ ' ' };
      in >> DelimiterIO{ '#' };
      in >> DelimiterIO{ 'c' };
      in >> DelimiterIO{ '(' };
      in >> ComplexIO{ ds.key2 };
      in >> DelimiterIO{ ')' };
    }
    else if (key == "key3")
    {
      in >> DelimiterIO{ ' ' };
      in >> StringIO{ ds.key3 };
    }
  }
  in >> DelimiterIO{ ':' };
  in >> DelimiterIO{ ')' };
  return in;
}

std::ostream& madyarov::operator<<(std::ostream& out, const DataStruct& ds)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  if (ds.reg == true)
  {
    out << "(:key1 0x" << std::uppercase << std::hex << toupper(ds.key1) <<
      ":key2 " << "#c(" << std::fixed << std::setprecision(1) << ds.key2.real() << " " <<
      std::fixed << std::setprecision(1) << ds.key2.imag() << ")" << ":key3 " << std::quoted(ds.key3) << ":)";
  }
  else
  {
    out << "(:key1 0X" << std::hex << tolower(ds.key1) <<
      ":key2 " << "#c(" << std::fixed << std::setprecision(1) << ds.key2.real() << " " <<
      std::fixed << std::setprecision(1) << ds.key2.imag() << ")" << ":key3 " << std::quoted(ds.key3) << ":)";
  }
  return out;
}

bool madyarov::compareDataStruct(const DataStruct& a, const DataStruct& b) {
  if (a.key1 != b.key1)
    return a.key1 < b.key1;
  if (a.key2 != b.key2)
    return abs(a.key2) < abs(b.key2);
  return a.key3.size() < b.key3.size();
}
