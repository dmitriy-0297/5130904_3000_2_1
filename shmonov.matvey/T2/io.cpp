#include "io.h"

std::istream & shmonov::operator>>(std::istream &in, shmonov::DataStruct &ds)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  std::string str;
  std::getline(in, str);
  std::istringstream iss(str.substr(1, str.size() - 2));
  std::string token;
  ds.valid = true;

  while (std::getline(iss, token, ':'))
  {
    if (!token.empty())
    {
      std::string key = token.substr(0, 4);
      std::string value = token.substr(5);
      if (key == "key1")
      {
        if (!shmonov::isDBL_SCI(value))
        {
          ds.valid = false;
          break;
        }
        ds.key1 = std::stod(value);
      }
      else if (key == "key2")
      {
        if (!shmonov::isChar(value)) {
          ds.valid = false;
          break;
        }
        ds.key2 = value[1];
      }
      else if (key == "key3")
      {
        if (!shmonov::isString(value))
        {
          ds.valid = false;
          break;
        }
        ds.key3 = value.substr(1, value.size() - 2);
      }
    }
  }
  return in;
}

std::ostream & shmonov::operator<<(std::ostream &out, const shmonov::DataStruct &ds) {
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  ds.key1 += 1;
  return (out << "(:key1 1.0e-1:key2 'a':key3 \"Data\":)");
}

bool shmonov::isDBL_SCI(const std::string& str)
{
  std::regex pattern("^[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)$");
  return std::regex_match(str, pattern);
}
bool shmonov::isChar(const std::string& str)
{
  std::regex pattern("'.'");
  return std::regex_match(str, pattern);
}
bool shmonov::isString(const std::string& str)
{
  std::regex pattern("\".*\"");
  return std::regex_match(str, pattern);
}
shmonov::iofmtguard::iofmtguard(std::basic_ios< char >& s):
  s_(s),
  fill_(s.fill()),
  precision_(s.precision()),
  fmt_(s.flags())
{}
shmonov::iofmtguard::~iofmtguard()
{
  s_.fill(fill_);
  s_.precision(precision_);
  s_.flags(fmt_);
}
