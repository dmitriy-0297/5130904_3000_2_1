#include "io.h"

std::pair<std::string, std::string> shmonov::getNextPair(std::string &s)
{
  s.erase(0, s.find(':') + 1); // remove ':' from the beginning of string
  std::string key = s.substr(0, 4);
  s.erase(0, 5);
  std::string value;
  if (key == "key3")
  {
    value = s.substr(0, s.find('"', 1) + 1);
    s.erase(0, value.size());
  }
  else
  {
    value = s.substr(0, s.find(':'));
    s.erase(0, value.size());
  }
  return std::make_pair(key, value); // key, value
}
std::istream & shmonov::operator>>(std::istream &in, shmonov::DataStruct &ds)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  ds.valid = true;
  std::string token;
  getline(in, token);
  while (!token.empty())
  {
    std::pair<std::string, std::string> pair = shmonov::getNextPair(token);
    if (pair.first == "key1")
    {
      if (!shmonov::isDBL_SCI(pair.second))
      {
        ds.valid = false;
        break;
      }
      ds.key1 = std::stod(pair.second);
    }
    else if (pair.first == "key2")
    {
      if (!shmonov::isChar(pair.second)) {
        ds.valid = false;
        break;
      }
      ds.key2 = pair.second[1];
    }
    else if (pair.first == "key3")
    {
      if (!shmonov::isString(pair.second))
      {
        ds.valid = false;
        break;
      }
      ds.key3 = pair.second.substr(1, pair.second.size() - 2);
    }
  }
  return in;
}
std::string shmonov::myScientific(double x)
{
  std::stringstream ss;
  ss << std::scientific << x;
  std::string out = ss.str();
  size_t i = std::min(out.find('E'), out.find('e'));
  while (out[i - 1] == '0' && out[i - 2] != '.')
  {
    out.erase(i - 1, 1);
    i = std::min(out.find('E'), out.find('e'));
  }
  while (out[i + 2] == '0')
  {
    out.erase(i + 2, 1);
    i = std::min(out.find('E'), out.find('e'));
  }
  return out;
}
std::ostream & shmonov::operator<<(std::ostream &out, const shmonov::DataStruct &ds) {
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  out << "(:key1 " << myScientific(ds.key1) << ":key2 '" << ds.key2 << "':key3 \"" << ds.key3 << "\":)";
  return out;
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
