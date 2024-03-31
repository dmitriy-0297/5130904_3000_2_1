#include "io.h"

std::istringstream& sevostyanova::operator>>(std::istringstream& input, Data& ds)
{
  std::string str;
  std::getline(input, str, ' ');
  ds.key1_ = stoull(str);
  std::getline(input, str, ' ');
  ds.key2_ = stoull(str);
  std::getline(input, ds.key3_);
  return input;
};

std::ostream& sevostyanova::operator<<(std::ostream& out, const Data& ds)
{
  out << "(:key1 " << ds.key1_ << "ull" << ":key2 " << "0b" << std::bitset<8>{ds.key2_} << ":key3 " << ds.key3_ << ":)" << std::endl;;
  return out;
};

std::pair<std::string, std::string> sevostyanova::getPair(std::string& str)
{
  size_t length = str.length() - str.substr(0, str.find(" ")).length() - 1;//find the length of second substring 
  return std::make_pair(str.substr(0, str.find(" ")), str.substr(str.find(" ") + 1, length));
}

bool sevostyanova::isULLLIFT(const std::string& str)
{
  std::regex regular1("\\d+ull");
  std::regex regular2("\\d+ULL");
  return std::regex_match(str, regular1) || std::regex_match(str, regular2);
}

bool sevostyanova::isULLBIN(const std::string& str)
{
  std::regex regular1("0b[0-1]+");
  std::regex regular2("0B[0-1]+");
  return std::regex_match(str, regular1) || std::regex_match(str, regular2);
}

bool sevostyanova::isString(const std::string& str)
{
  std::regex regular("\".*\"");
  return std::regex_match(str, regular);
}

bool sevostyanova::isCorrectTypes(std::string& input)
{
  input.erase(0, input.find_first_of('(') + 1);// remove first '('
  input.erase(input.find_last_of(')'), input.find_last_of(')') + 1);//remove last ')'
  input = input.substr(0, input.find_last_of(':'));//remove last ':'
  std::string result[3] = { "" };
  while (input.find(':') != std::string::npos)
  {
    input.erase(0, input.find_first_of(':') + 1);//remove first ':' in each substring
    std::string str = input.substr(0, input.find(':'));
    input.erase(0, str.length());

    if (getPair(str).first == "key1" && !isULLLIFT(getPair(str).second))
      return false;
    if (getPair(str).first == "key2" && !isULLBIN(getPair(str).second))
      return false;
    if (getPair(str).first == "key3" && !isString(getPair(str).second))
      return false;

    //put keys in order as in the struct data 
    if (getPair(str).first == "key1")
      result[0] = getPair(str).second;
    if (getPair(str).first == "key2")
    {
      std::string str1 = getPair(str).second;
      str1.erase(0, str1.find('b') + 1);
      result[1] = std::to_string(stoull(str1, nullptr, 2));
    }
    if (getPair(str).first == "key3")
      result[2] = getPair(str).second;
  }
  for (std::string el : result)
    input += el + " ";
  input = input.substr(0, input.length() - 1);
  return true;
};
