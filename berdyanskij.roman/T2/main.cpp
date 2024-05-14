#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

#include "io.h"

using namespace berdyanskij;

int main(void)  // (:key1 5.45e-2:key2 2ll:key3 "Hello world!")
{
    std::vector<DataStruct> data;
    std::copy_if(
        std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(data),
        [](const DataStruct& ds) { return ds.valid; }
    );
    std::sort(
        data.begin(),
        data.end(),
        [](const DataStruct& a, const DataStruct& b)
        {
            if (a.key1 != b.key1)
            {
                return a.key1 < b.key1;
            }
            if (a.key2 != b.key2)
            {
                return a.key2 < b.key2;
            }
            return a.key3.size() < b.key3.size();
        });
    std::copy(data.begin(), data.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
}
