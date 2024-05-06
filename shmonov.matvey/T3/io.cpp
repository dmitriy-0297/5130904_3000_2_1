#include "io.h"

bool shmonov::isPoint(const std::string &str)
{
  std::regex pattern("\\(-?[0-9]+;-?[0-9]+\\)");
  return std::regex_match(str, pattern);
}
std::istream & shmonov::operator>>(std::istream &in, shmonov::Point &point)  // (1;1)
{
  std::istream::sentry sentry(in);

  if (!sentry)
    return in;

  std::string str;
  in >> str;
  if (!shmonov::isPoint(str))
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  char ch;
  std::stringstream ss(str);
  ss >> ch >> point.x >> ch >> point.y >> ch;
  return in;
}


std::istream & shmonov::operator>>(std::istream &in, shmonov::Polygon &polygon)  // 3 (1;2) (0;0) (0;3)
{
  std::istream::sentry sentry(in);

  if (!sentry)
    return in;

  polygon.points.clear();

  std::size_t n;
  in >> n;
  if (in.fail() || n < 3)  // polygon must have at least 3 vertices
  {
    in.setstate(std::ios_base::failbit);  // if n < 3 but in.fail() is false
    return in;
  }
  polygon.points.resize(n);

  std::size_t i = 0;
  while (in.peek() != '\n')
  {
    shmonov::Point p;
    in >> p;
    if (in.fail())
      break;

    if (i == 0 || p != polygon.points[i - 1])
    {
      if (i < n)
      {
        polygon.points[i++] = p;
      }
      else
      {
        in.setstate(std::ios_base::failbit);
        return in;
      }
    }
  }
  if (i != n)
    in.setstate(std::ios_base::failbit);
  return in;
}
