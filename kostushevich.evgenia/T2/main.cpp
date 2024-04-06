#include "IO.h"

using namespace kostushevich;

int main()
{
  std::vector<DataStruct> data;
  std::string input = "";
  while (std::cin.good() && !(std::cin.eof()))
  {
    std::getline(std::cin, input);
    std::istringstream iss(input);
    if (input.empty())
    {
      break;
    }

    std::copy(
      std::istream_iterator<DataStruct>(iss),
      std::istream_iterator<DataStruct>(),
      std::back_inserter(data)
    );
  }

  std::sort(
    data.begin(),
    data.end(),
    [](const DataStruct& a, const DataStruct& b)
    {
      if (a.key1 < b.key1)
      {
        return true;
      }
      if (a.key1 == b.key1)
      {
        if (std::abs(a.key2) < std::abs(b.key2))
        {
          return true;
        }
        if (std::abs(a.key2) == std::abs(b.key2))
        {
          return a.key3.size() < b.key3.size();
        }
      }
      return false;
    }
  );

  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator<DataStruct>(std::cout, "\n")
  );
  return EXIT_SUCCESS;
}
