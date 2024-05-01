#include "poly.h"

std::istream & usikov::operator >>( std::istream &stream, Sep &&res )
{
  std::istream::sentry sentry(stream);

  if (!sentry)
    return stream;

  char ch;

  stream >> ch;
  if (!stream || ch != res.exp)
    stream.setstate(std::ios::failbit);

  return stream;
}

std::istream & usikov::operator >>( std::istream &stream, Point &res )
{
  std::istream::sentry sentry(stream);

  if (!sentry)
    return stream;

  stream >> Sep('(') >> res.x >> Sep(';') >> res.y >> Sep(')');

  return stream;
}

std::istream & usikov::operator >>( std::istream &stream, Polygon &res )
{
  std::istream::sentry sentry(stream);

  if (!sentry)
    return stream;

  size_t size;

  stream >> size;

  if (size < 3)
  {
    stream.setstate(std::istream::failbit);
    return stream;
  }

  res.points.clear();
  res.points.resize(size);

  for (auto &p : res.points)
    stream >> p;

  return stream;
}

std::ostream & usikov::operator <<( std::ostream &stream, const Point &pnt )
{
  std::ostream::sentry sentry(stream);

  if (!sentry)
    return stream;

  std::cout << '(' << pnt.x << "; " << pnt.y << ")";
  return stream;
}

std::ostream & usikov::operator <<( std::ostream &stream, const Polygon &poly )
{
  std::ostream::sentry sentry(stream);

  if (!sentry)
    return stream;

  stream << poly.points.size() << ' ';

  for (const auto &p : poly.points)
    stream << p << ' ';

  return stream;
}
