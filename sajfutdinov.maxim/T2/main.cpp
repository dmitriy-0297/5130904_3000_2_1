#include "DataStruct.h"

int main()
{
  using namespace sajfutdinov;

  std::vector< DataStruct > data;
  std::string input = "";

  while (std::cin.good())
  {
  std::getline(std::cin, input);
  std::istringstream iss(input);
      std::copy(
          std::istream_iterator< DataStruct >(iss),
          std::istream_iterator< DataStruct >(),
          std::back_inserter(data)
      );
  }

  std::sort(data.begin(), data.end(), sajfutdinov::compareData);

  std::copy(
      std::begin(data),
      std::end(data),
      std::ostream_iterator< DataStruct >(std::cout, "\n")
  );

  return 0;
}
