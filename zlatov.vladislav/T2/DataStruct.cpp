#include "DataStruct.h"
#include "Delimiter.h"
#include "ScopeGuard.h"
#include <sstream>
#include <iomanip>

bool DataStruct::operator<(const DataStruct& rhs) const {
  if (key1 == rhs.key1) {
    if (key2 == rhs.key2) {
      return key3.size() < rhs.key3.size();
    }
    return key2 < rhs.key2;
  }
  return key1 < rhs.key1;
}

std::istream& operator>>(std::istream& in, DataStruct& data) {
  ScopeGuard guard(in);

  std::string line;
  if (std::getline(in, line)) {
    std::istringstream iss(line);

    char delimiter = 0;
    if (!(iss >> DelimiterString{ "(:" } >> delimiter)) {
      in.setstate(std::ios::failbit);
      return in;
    }

    std::string key;
    if (!(iss >> key)) {
      in.setstate(std::ios::failbit);
      return in;
    }

    if (key == "key1") {
      if (!(iss >> data.key1)) {
        in.setstate(std::ios::failbit);
        return in;
      }
    }
    else if (key == "key2") {
      unsigned long long temp = 0;
      if (!(iss >> std::hex >> temp)) {
        in.setstate(std::ios::failbit);
        return in;
      }
      data.key2 = temp;
    }
    else if (key == "key3") {
      if (!(iss >> std::quoted(data.key3))) {
        in.setstate(std::ios::failbit);
        return in;
      }
    }
    else {
      in.setstate(std::ios::failbit);
      return in;
    }

    while (iss >> key) {
      if (key == "key1") {
        if (!(iss >> data.key1)) {
          in.setstate(std::ios::failbit);
          return in;
        }
      }
      else if (key == "key2") {
        unsigned long long temp = 0;
        if (!(iss >> std::hex >> temp)) {
          in.setstate(std::ios::failbit);
          return in;
        }
        data.key2 = temp;
      }
      else if (key == "key3") {
        if (!(iss >> std::quoted(data.key3))) {
          in.setstate(std::ios::failbit);
          return in;
        }
      }
      else {
        in.setstate(std::ios::failbit);
        return in;
      }
    }

    if (!(iss >> DelimiterString{ ":)" })) {
      in.setstate(std::ios::failbit);
      return in;
    }
  }
  else {
    in.setstate(std::ios::failbit);
  }

  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
  out << "(:key1 " << std::fixed << std::setprecision(1) << data.key1 << "d:key2 " << std::hex << std::uppercase << data.key2 << ":key3 \"" << data.key3 << "\":)";
  return out;
}
