#include <iostream>
#include <vector>
#include <algorithm>
#include "DataStruct.h"
#include "Delimiter.h"
#include "ScopeGuard.h"

int main() {
  std::vector<DataStruct> data;
  DataStruct temp;

  while (std::cin >> temp) {
    data.push_back(temp);
  }

  std::sort(data.begin(), data.end());

  for (const auto& item : data) {
    std::cout << item << '\n';
  }

  return 0;
}
