#include <list>
#include <iostream>
#include <limits>
#include <iterator>
#include "DataStruct.h"
#include "Delimiter.h"
#include "ScopeGuard.h"

int main()
{
  using inputItT = std::istream_iterator< DataStruct >;

  std::list< DataStruct > data{};

  while (!std::cin.eof())
  {
    std::copy(inputItT{ std::cin }, inputItT{}, std::back_inserter(data));
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  data.sort();
  using outputItT = std::ostream_iterator< DataStruct >;
  std::copy(data.cbegin(), data.cend(), outputItT{ std::cout, "\n" });
}
