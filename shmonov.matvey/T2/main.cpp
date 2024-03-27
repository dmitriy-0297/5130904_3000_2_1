#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

#include "io.h"

using namespace shmonov;

int main( void )  // (:key1 5.45e-2:key2 'c':key3 "Hello world!")
{
  std::vector<DataStruct> vec;
  std::copy_if(
      std::istream_iterator<DataStruct>(std::cin),
      std::istream_iterator<DataStruct>(),
      std::back_inserter(vec),
      [](const DataStruct &ds) { return ds.valid; }
  );
  std::sort(
      vec.begin(),
      vec.end(),
      [](const DataStruct &lhs, const DataStruct &rhs)
      {
        if (lhs.key1 < rhs.key1)
        {
          return true;
        }
        if (lhs.key2 < rhs.key2)
        {
          return true;
        }
        else
        {
          return lhs.key3 < rhs.key3;
        }
      }
  );
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
}
