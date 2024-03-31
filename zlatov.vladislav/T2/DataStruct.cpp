#include "DataStruct.h"
#include "Delimiter.h"
#include "ScopeGuard.h"
#include <sstream>
#include <iomanip>

bool DataStruct::operator<(const DataStruct& rhs) const
{
  if (key1 == rhs.key1)
  {
    if (key2 == rhs.key2)
    {
      return key3.size() < rhs.key3.size();
    }
    return key2 < rhs.key2;
  }
  return key1 < rhs.key1;
}

std::istream& operator>>(std::istream& in, DataStruct& data)
{
  std::string line;
  if (std::getline(in, line, ':'))
  {
    std::istringstream iss(line);
    std::string field;

    while (std::getline(iss, field, ':'))
    {
      std::size_t pos = field.find(' ');
      if (pos != std::string::npos)
      {
        std::string key = field.substr(0, pos);
        std::string value = field.substr(pos + 1);

        if (key == "key1")
        {
          double val;
          if (value.back() == 'd' || value.back() == 'D')
          {
            value.pop_back();
            std::istringstream(value) >> val;
            data.key1 = val;
          }
        }
        else if (key == "key2")
        {
          unsigned long long val = 0;
          if (value.substr(0, 2) == "0x" || value.substr(0, 2) == "0X")
          {
            std::istringstream(value.substr(2)) >> std::hex >> val;
            data.key2 = val;
          }
        }
        else if (key == "key3")
        {
          if (value.front() == '\"' && value.back() == '\"')
          {
            data.key3 = value.substr(1, value.size() - 2);
          }
        }
      }
    }
  }

  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
  out << "(:key1 " << std::fixed << std::setprecision(1) << data.key1 
    << "d:key2 " << std::hex << std::uppercase << data.key2 
    << ":key3 \"" << data.key3 << "\":)";
  return out;
}
