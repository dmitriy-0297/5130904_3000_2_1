#include "DataStruct.h"

using namespace madyarov;

int main() // (:key1 0xFFFA:key2 #c(1.0 -1.0):key3 "data":)
{
  std::vector<DataStruct> data;
  std::string input;
  while (!(std::cin.eof()))
  {
    std::getline(std::cin, input);
    std::istringstream iss(input);
    if (input.empty())
    {
      break;
    }
    std::copy(std::istream_iterator<DataStruct>(iss), std::istream_iterator<DataStruct>(), std::back_inserter(data));
  }

  std::sort(data.begin(), data.end(), compareDataStruct);

  std::copy(std::begin(data), std::end(data), std::ostream_iterator<DataStruct>(std::cout, "\n"));

  return EXIT_SUCCESS;
}
