#include <algorithm>
#include <functional>
#include <iomanip>
#include "Geometry.h"

std::istream& tretyak::operator>>(std::istream &in, tretyak::Point &elem)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimIO("(") >> elem.x_ >> DelimIO(";") >> elem.y_ >> DelimIO(")");
  return in;
}

std::istream& tretyak::operator>>(std::istream &in, tretyak::Polygon &elem)
{
    std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  int tSize = 0;
  in >> tSize;
  if (tSize >= 3)
  {
    elem.points.clear();
    elem.points.resize(tSize);
    for (int i = 0; i < tSize; i++)
    {
      in >> elem.points[i];
    }
  }
  else
  {
    in.setstate(std::ios_base::failbit);
  }
  return in;
}

std::istream& tretyak::operator>>(std::istream &in, tretyak::DelimIO &&elem)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::string del;
  in >> std::setw(1) >> del;
  if (!in || del != elem.delim_)
  {
    in.setstate(std::ios_base::failbit);
  }
  return in;
}

std::ostream& tretyak::operator<<(std::ostream &op, const Polygon &elem)
{
  std::ostream::sentry sentry(op);
  if (!sentry)
  {
    return op;
  }
  op << elem.points.size() << " ";
  for (int i = 0; i < elem.points.size(); i++)
  {
    op << elem.points[i] << " ";
  }
  return op;
}

std::ostream& tretyak::operator<<(std::ostream &op, const Point &elem)
{
  std::ostream::sentry sentry(op);
  if (!sentry)
  {
    return op;
  }
  op << "(" << elem.x_ << ";" << elem.y_ << ")";
  return op;
}

double tretyak::Polygon::area() const
{
  double accum = 0.0;
  for (int i = 0; i < points.size(); i++)
  {
    const auto &current = points[i];
    const auto &next = points[(i + 1) % points.size()];
    accum += (current.x_ * next.y_ - next.x_ * current.y_);
  }

  return std::fabs(accum * 0.5);
}

bool tretyak::Point::operator!=(const Point &otherEl) const
{
  if (this->x_ != otherEl.x_ || this->y_ != otherEl.y_)
  {
    return true;
  }
  return false;
}

bool tretyak::Polygon::operator==(const Polygon &otherEl) const
{
  if(this->points.size() != otherEl.points.size())
  {
    return false;
  }
  for (int i = 0; i < this->points.size(); i++)
  {
    if (this->points[i] != otherEl.points[i])
    {
      return false;
    }
  }
  return true;
}
