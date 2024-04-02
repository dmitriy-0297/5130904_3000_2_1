#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <iomanip>
#include <algorithm>


struct DataStruct
{
  char key1;
  std::pair<long long, unsigned long long> key2;
  std::string key3;
};

struct DelimiterIO
{
  char exp;
};

struct RationalIO
{
  std::pair<long long, unsigned long long> &ref;
};

struct StringIO
{
  std::string &ref;
};

struct LabelIO
{
  std::string exp;
};

class iofmtguard
{
public:
  iofmtguard(std::basic_ios< char > &s);
  ~iofmtguard();
private:
  std::basic_ios< char > &s_;
  char fill_;
  std::streamsize precision_;
  std::basic_ios< char >::fmtflags fmt_;
};


std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
std::istream &operator>>(std::istream &in, RationalIO &&dest);
std::istream &operator>>(std::istream &in, StringIO &&dest);
std::istream &operator>>(std::istream &in, LabelIO &&dest);
std::istream &operator>>(std::istream &in, DataStruct &dest);
std::ostream &operator<<(std::ostream &out, const DataStruct &dest);
bool compareData(const DataStruct &a, const DataStruct &b);

int main()
{
  std::vector< DataStruct > data;
  std::string input = "";
  std::getline(std::cin, input);
  std::istringstream iss(input);

  std::copy(
    std::istream_iterator< DataStruct >(iss),
    std::istream_iterator< DataStruct >(),
    std::back_inserter(data)
  );

  std::sort(data.begin(), data.end(), compareData);

  std::cout << "Data:\n";
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator< DataStruct >(std::cout, "\n")
  );

  return 0;
}



std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
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

std::istream &operator>>(std::istream &in, LabelIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::string data = "";
  if ((in >> StringIO{ data }) && (data != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream &operator>>(std::istream &in, RationalIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  long long numerator;
  unsigned long long denominator;
  in >> LabelIO{ "(:N " } >> numerator >> DelimiterIO{ ':' } >> LabelIO{ "D " } >> denominator >> LabelIO{ ":):" };
  dest.ref = std::make_pair(numerator, denominator);

  return in;
};

std::istream &operator>>(std::istream &in, StringIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}

std::istream &operator>>(std::istream &in, DataStruct &dest)
{
  using delimiter = DelimiterIO;
  using key = StringIO;
  in >> delimiter{ '(' };

  while (true)
  {
    std::string key;
    in >> delimiter{ ':' };
    in >> key;

    if (key == "key1")
    {
      in >> delimiter{ ' ' };
      in >> dest.key1;
    }
    else if (key == "key2")
    {
      in >> delimiter{ ' ' };
      using rational = RationalIO;
      in >> rational{ dest.key2 };
    }
    else if (key == "key3")
    {
      using text = StringIO;
      in >> delimiter{ ' ' };
      in >> text{ dest.key3 };
    }
  }

  in >> delimiter{ ')' };
  return in;
}

std::ostream &operator<<(std::ostream &out, const DataStruct &src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  out << "{ ";
  out << "\"key1\": " << std::fixed << std::setprecision(1) << src.key1 << "d, ";
  out << "\"key2\": " << src.key2.first << " " << src.key2.second;
  out << " }";
  return out;
}

iofmtguard::iofmtguard(std::basic_ios< char > &s) :
  s_(s),
  fill_(s.fill()),
  precision_(s.precision()),
  fmt_(s.flags())
{}

iofmtguard::~iofmtguard()
{
  s_.fill(fill_);
  s_.precision(precision_);
  s_.flags(fmt_);
}

bool compareData(const DataStruct& a, const DataStruct& b)
{
  if (a.key1 != b.key1) {
      return a.key1 < b.key1;
  }
  if (a.key2 != b.key2) {
      return a.key2 < b.key2;
  }
  return a.key3.size() < b.key3.size();
}
