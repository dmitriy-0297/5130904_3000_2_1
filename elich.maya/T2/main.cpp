#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

#include "data_struct.h"

int main()
{
    std::vector< elich::Data > datas;

    while (!std::cin.eof())
    {
        std::cin.clear();
        std::copy(std::istream_iterator< elich::Data >(std::cin),
            std::istream_iterator< elich::Data >(),
            std::back_inserter(datas));
    }

    std::sort(datas.begin(), datas.end());

    std::copy(datas.begin(), datas.end(), std::ostream_iterator< elich::Data >(std::cout, "\n"));

    return 0;
}