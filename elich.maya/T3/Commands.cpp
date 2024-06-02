#include "Commands.h"
#include <iomanip>
#include <string>
#include <algorithm>
#include <numeric>
#include "iofmtguard.h"
#include "data_struct.h"
#include "polygonPredicats.h"
namespace
{
  bool checkEndArgs(elich::istream_t & in)
  {
    elich::iofmtguard guard(in);
    in >> std::noskipws >> elich::DelimeterIO{ '\n' };
    return static_cast< bool >(in);
  }
  bool isNumber(const std::string & str)
  {
    return std::all_of(str.begin(), str.end(), ::isdigit);
  }
  template < typename Compare >
  struct AreaCmp
  {
    bool operator()(const elich::Polygon & first, const elich::Polygon & second)
    {
      return Compare()(elich::getPolygonArea(first), elich::getPolygonArea(second));
    }
  };
  template < typename Compare >
  struct VertexesCmp
  {
    bool operator()(const elich::Polygon & first, const elich::Polygon & second)
    {
      return Compare()(elich::getPolygonVertexes(first), elich::getPolygonVertexes(second));
    }
  };
}
bool elich::getArea(istream_t & in, polygons_t & polygones, std::ostream & out)
{
  std::string arg = "";
  in >> arg;
  if (!checkEndArgs(in))
  {
    return false;
  }
  double area = 0.f;
  try
  {
    if (arg == "ODD")
    {
      area = areaOdd(polygones);
    }
    else if (arg == "EVEN")
    {
      area = areaEven(polygones);
    }
    else if (arg == "MEAN")
    {
      area = areaMean(polygones);
    }
    else if (isNumber(arg))
    {
      area = areaNum(std::stoul(arg), polygones);
    }
    else
    {
      throw std::logic_error("Bad args");
    }
  }
  catch (const std::logic_error &)
  {
    return false;
  }
  iofmtguard guard(out);
  out << std::setprecision(1) << std::fixed;
  out << area;
  return true;
}
bool elich::getMax(istream_t & in, polygons_t & polygones, std::ostream & out)
{
  if (polygones.empty())
  {
    return false;
  }
  std::string arg = "";
  in >> arg;
  if (!checkEndArgs(in))
  {
    return false;
  }
  if (arg == "AREA")
  {
    iofmtguard guard(out);
    out << std::setprecision(1) << std::fixed;
    out << getMaxArea(polygones);
  }
  else if (arg == "VERTEXES")
  {
    out << getMaxVertexes(polygones);
  }
  else
  {
    return false;
  }
  return true;
}
bool elich::getMin(istream_t & in, polygons_t & polygones, std::ostream & out)
{
  if (polygones.empty())
  {
    return false;
  }
  std::string arg = "";
  in >> arg;
  if (!checkEndArgs(in))
  {
    return false;
  }
  if (arg == "AREA")
  {
    iofmtguard guard(out);
    out << std::setprecision(1) << std::fixed;
    out << getMinArea(polygones);
  }
  else if (arg == "VERTEXES")
  {
    out << getMinVertexes(polygones);
  }
  else
  {
    return false;
  }
  return true;
}
bool elich::getCount(istream_t & in, polygons_t & polygones, std::ostream & out)
{
  std::string arg = "";
  in >> arg;
  if (!checkEndArgs(in))
  {
    return false;
  }
  size_t count = 0;
  try
  {
    if (arg == "EVEN")
    {
      count = countEven(polygones);
    }
    else if (arg == "ODD")
    {
      count = countOdd(polygones);
    }
    else if (isNumber(arg))
    {
      count = countNum(std::stoul(arg), polygones);
    }
    else
    {
      throw std::logic_error("Bad args");
    }
  }
  catch (const std::logic_error &)
  {
    return false;
  }
  out << count;
  return true;
}
bool elich::getEcho(istream_t & in, polygons_t & polygones, std::ostream & out)
{
  Polygon poly;
  in >> poly;
  if (!in)
  {
    return false;
  }
  polygons_t tmp_vec;
  tmp_vec.reserve(polygones.size());
  size_t count = 0;
  std::transform(polygones.begin(),
   polygones.end(),
   std::back_inserter(tmp_vec),
   [&](auto p)
   {
     if (p == poly)
     {
       tmp_vec.push_back(poly);
       ++count;
     }
     return p;
   });
  polygones = std::move(tmp_vec);
  out << count;
  return true;
}
bool elich::getMaxSeq(istream_t & in, polygons_t & polygones, std::ostream & out)
{
  Polygon poly;
  in >> poly;
  if (!in)
  {
    return false;
  }
  using pair_t = std::pair< size_t, size_t >;
  pair_t init{ 0, 0 };
  auto result = std::accumulate(polygones.begin(),
   polygones.end(),
   init,
   [&poly](const pair_t & res, const Polygon & p) -> pair_t
   {
     if (p == poly)
     {
       return { res.first, res.second + 1 };
     }
     return { std::max(res.first, res.second), 0 };
   });
  out << result.first;
  return true;
}
double elich::areaOdd(polygons_t & polygones)
{
  return std::accumulate(polygones.begin(),
   polygones.end(),
   0.f,
   [](double area, const Polygon & polygon) -> double
   {
     if (elich::isOddVertexes(polygon))
     {
       return area + elich::getPolygonArea(polygon);
     }
     return area;
   });
}
double elich::areaEven(polygons_t & polygones)
{
  return std::accumulate(polygones.begin(),
   polygones.end(),
   0.f,
   [](double area, const Polygon & polygon) -> double
   {
     if (elich::isEvenVertexes(polygon))
     {
       return area + elich::getPolygonArea(polygon);
     }
     return area;
   });
}
double elich::areaMean(polygons_t & polygones)
{
  if (polygones.empty())
  {
    throw std::logic_error("Not enough shapes");
  }
  return std::accumulate(polygones.begin(),
          polygones.end(),
          0.f,
          [](double area, const Polygon & polygon) -> double
          {
            return area + elich::getPolygonArea(polygon);
          }) /
         polygones.size();
}
double elich::areaNum(size_t num, polygons_t & polygones)
{
  if (num < 3)
  {
    throw std::logic_error("Bad number of vertexes");
  }
  return std::accumulate(polygones.begin(),
   polygones.end(),
   0.f,
   [=](double area, const Polygon & polygon) -> double
   {
     if (elich::getPolygonVertexes(polygon) == num)
     {
       return area + elich::getPolygonArea(polygon);
     }
     return area;
   });
}
double elich::getMaxArea(polygons_t & polygones)
{
  elich::Polygon & poly =
   *std::max_element(polygones.begin(), polygones.end(), AreaCmp< std::less< double > >());
  return elich::getPolygonArea(poly);
}
size_t elich::getMaxVertexes(polygons_t & polygones)
{
  elich::Polygon & poly =
   *std::max_element(polygones.begin(), polygones.end(), VertexesCmp< std::less< double > >());
  return elich::getPolygonVertexes(poly);
}
double elich::getMinArea(polygons_t & polygones)
{
  elich::Polygon & poly =
   *std::min_element(polygones.begin(), polygones.end(), AreaCmp< std::less< double > >());
  return elich::getPolygonArea(poly);
}
size_t elich::getMinVertexes(polygons_t & polygones)
{
  elich::Polygon & poly =
   *std::min_element(polygones.begin(), polygones.end(), VertexesCmp< std::less< double > >());
  return elich::getPolygonVertexes(poly);
}
size_t elich::countEven(polygons_t & polygones)
{
  return std::count_if(polygones.begin(), polygones.end(), elich::isEvenVertexes);
}
size_t elich::countOdd(polygons_t & polygones)
{
  return std::count_if(polygones.begin(), polygones.end(), elich::isOddVertexes);
}
size_t elich::countNum(size_t num, polygons_t & polygones)
{
  if (num < 3)
  {
    throw std::logic_error("Bad number of vertexes");
  }
  return std::count_if(polygones.begin(),
   polygones.end(),
   [=](const Polygon & polygon) -> bool
   {
     return elich::getPolygonVertexes(polygon) == num;
   });
}

