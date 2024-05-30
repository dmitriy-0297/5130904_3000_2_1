#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <limits>
#include "io.h"

using salamatov::DataStruct;

int main() {
  try {
    std::vector<DataStruct> data;

    while (!std::cin.eof()) {
      if (!std::cin) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      std::copy(
        std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(data)
      );
    }

    std::sort(data.begin(), data.end(), salamatov::compareDataStruct);

    std::copy(
      data.begin(),
      data.end(),
      std::ostream_iterator<DataStruct>(std::cout, "\n")
    );
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
