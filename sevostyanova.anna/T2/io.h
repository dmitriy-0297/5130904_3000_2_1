#ifndef IO_H
#define IO_H

#include <iostream>
#include<string>
#include <sstream>
#include<algorithm>
#include<regex>
#include<bitset>


namespace sevostyanova
{
  struct Data
  {
    unsigned long long key1_;
    unsigned long long key2_;
    std::string key3_;
    friend std::istringstream& operator>>(std::istringstream& input, Data& ds);
    friend std::ostream& operator<<(std::ostream& out, const Data& ds);		
  };

  std::pair<std::string, std::string> getPair(std::string& str);
  bool isULLLIFT(const std::string& str);
  bool isULLBIN(const std::string& str);
  bool isString(const std::string& str);
  bool isCorrectTypes(std::string& input);

}
#endif
