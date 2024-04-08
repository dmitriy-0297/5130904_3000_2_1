#include <vector>
#include <algorithm>
#include <iterator>

#include "io.h"

using namespace berdyanskiy;

int main() {
  std::vector<DataStruct> data;
  std::copy(std::istream_iterator<DataStruct>(std::cin),
    std::istream_iterator<DataStruct>(),
    std::back_inserter(data));

  std::sort(data.begin(), data.end(), [](const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.size() < b.key3.size();
  });

  std::copy(data.begin(), data.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
  return 0;
}

//(:key1 3.14e0:key2 42: key3 "example1":)
//(:key1 3.14e0:key2 42: key3 "example111":)
//(:key1 3.14e0:key2 42: key3 "example1":)
//(:key1 3.14e0:key2 42: key3 "example11":)
//^Z
