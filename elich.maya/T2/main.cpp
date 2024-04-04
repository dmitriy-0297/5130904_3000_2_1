#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

#include "data_struct.h"

int main()
{
    std::vector< elich::Data > datas;
    std::istringstream iss("(:key1 1.0e-1:key2 'A':key3 \"Data\":)(:key1 3.0e-1:key2 'c':key3 \"Data\":)(:key1 2.0e-1:key2 '8':key3 \"Data\":)");

    std::copy(std::istream_iterator< elich::Data >(std::cin),
        std::istream_iterator< elich::Data >(),
        std::back_inserter(datas));
    std::sort(datas.begin(), datas.end());

    std::copy(datas.begin(), datas.end(), std::ostream_iterator< elich::Data >(std::cout));

    return 0;
}