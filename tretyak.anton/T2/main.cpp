#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <iterator>
#include "DataStruct.h"

using namespace tretyak;

int main()
{
  std::vector<Data> data;
  std::string content;
  for(;;)
  {
    std::string line;
    if(getline(std::cin, line, '\n') && !line.empty() && !(std::cin.eof()))
    {
      content += line + '\n';
    }
    else
    {
      break;
    }
  }
  std::istringstream iss(content);
  std::copy_if(
    std::istream_iterator<Data>(iss),
    std::istream_iterator<Data>(),
    std::back_inserter(data),
    [](const Data &tData) {return tData.status;}
  );
  std::sort(data.begin(), data.end(),
    [](const Data &tData1, const Data &tData2)
    {
      if(tData1.key1 != tData2.key1)
      {
        return tData1.key1 <tData2.key1;
      }
      else if((tData1.key2.real() != tData2.key2.real()) || (tData1.key2.imag() != tData2.key2.imag()))
      {
        return abs(sqrt(pow(tData1.key2.real(), 2)+pow(tData1.key2.imag(), 2))) <
               abs(sqrt(pow(tData2.key2.real(), 2)+pow(tData2.key2.imag(), 2)));
      }
      else
      {
        return tData1.key3.length() < tData2.key3.length();
      }
    }
  );
  std::copy(data.begin(), data.end(), std::ostream_iterator<Data>(std::cout, "\n"));
  return EXIT_SUCCESS;
}
