#include "DataStruct.h"
#include <iomanip>
#include "Delimiter.h"
#include "ScopeGuard.h"

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
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  double key1 = 0.0;
  unsigned long long key2 = 0;
  std::string key3;

  char c = 0;
  std::string temp;

  // Проверяем открывающуюся скобку
  if (!(in >> c) || c != '(')
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  int key_count = 0;
  while (key_count < 3)
  {
    // Читаем имя ключа
    if (!(in >> temp) || temp != ":key")
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    // Читаем номер ключа
    if (!(in >> c) || (c < '1' || c > '3'))
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    switch (c)
    {
    case '1':
      if (!(in >> key1))
      {
        in.setstate(std::ios::failbit);
        return in;
      }

      // Проверяем суффикс d или D
      if (!(in >> temp) || (temp != "d" && temp != "D"))
      {
        in.setstate(std::ios::failbit);
        return in;
      }
      break;

    case '2':
      if (!(in >> std::hex >> temp) || (temp.size() < 2 || temp.substr(0, 2) != "0x"))
      {
        in.setstate(std::ios::failbit);
        return in;
      }

      // Преобразуем шестнадцатеричное значение в беззнаковое long long
      try
      {
        key2 = std::stoull(temp.substr(2), nullptr, 16);
      }
      catch (const std::exception&)
      {
        in.setstate(std::ios::failbit);
        return in;
      }
      break;

    case '3':
      if (!(in >> c) || c != '"')
      {
        in.setstate(std::ios::failbit);
        return in;
      }

      // Читаем строку в кавычках
      std::getline(in, key3, '"');
      break;
    }

    ++key_count;
  }

  // Проверяем закрывающуюся скобку
  if (!(in >> c) || c != ')')
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  data = DataStruct{ key1, key2, key3 };
  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  ScopeGuard scopeGuard(out);

  out << std::fixed << std::setprecision(1) << "(:key1 " << data.key1 << "d";
  out << std::hex << std::uppercase << ":key2 " << "0x" << data.key2;
  out << ":key3 \"" << data.key3 << "\":)";
  return out;
};
