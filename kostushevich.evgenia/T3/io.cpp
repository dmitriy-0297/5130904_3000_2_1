#include "io.h"

bool kostushevich::isPoint(const std::string &str)
{
  std::regex pattern("\\(-?[0-9]+;-?[0-9]+\\)");
  return std::regex_match(str, pattern);
}

std::ostream & kostushevich::operator<<(std::ostream &out, const kostushevich::Point &point)
{
  return (out << '(' << point.x << ';' << point.y << ')');
}

std::ostream & kostushevich::operator<<(std::ostream &out, const kostushevich::Polygon &polygon)
{
  out << polygon.points.size();
  for (auto &p : polygon.points)
    out << ' ' << p;
  return (out << '\n');
}

std::istream & kostushevich::operator>>(std::istream &in, kostushevich::Point &point)  // (1;1)
{
  std::istream::sentry sentry(in);

  if (!sentry)
    return in;

  std::string str;
  in >> str;
  if (!kostushevich::isPoint(str))
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  char ch;
  std::stringstream ss(str);
  ss >> ch >> point.x >> ch >> point.y >> ch;
  return in;
}


std::istream & kostushevich::operator>>(std::istream &in, kostushevich::Polygon &polygon)  // 3 (1;2) (0;0) (0;3)
{
  std::istream::sentry sentry(in);
  if (!sentry)
    return in;

  polygon.points.clear();
  std::size_t n;
  in >> n;
  if (in.fail() || n < 3)
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  polygon.points.resize(n);

  for (auto &p : polygon.points)
  {
    if (in.peek() == '\n')
    {
      in.setstate(std::ios_base::failbit);
      return in;
    }
    in >> p;
  }
  if (in.peek() != '\n')
    in.setstate(std::ios_base::failbit);
  return in;
}
