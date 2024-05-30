#include "io.h"

using salamatov::DataStruct;

int main()
{
  try
  {
    std::vector<DataStruct> data;
    while (!std::cin.eof()) {
      std::copy(std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(data));
      if (std::cin.fail()&& !std::cin.eof()) {
        std::cin.clear();
      }
    }
    std::sort(data.begin(), data.end(), salamatov::compareDataStruct);

    std::copy(data.begin(), data.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
  }
  catch (const std::exception& ex)
  {
    std::cerr << ex.what();
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
