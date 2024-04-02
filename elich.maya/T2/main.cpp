#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

#include "data_struct.hpp"

int main()
{
    std::vector< elich::Data > datas;
    std::istringstream iss("( :key1 6.0e2:key2 'A':key3 \"test1\":)(:key2 'c':key3 \"test2\":key1 5.4e-2:)(:key3 \"test3\":key1 1.4:key2 '0':)");

    while (!iss.eof())
    {
        std::copy(std::istream_iterator< elich::Data >(iss),
            std::istream_iterator< elich::Data >(),
            std::back_inserter(datas));
    }

    std::sort(datas.begin(), datas.end());

    std::cout << "Data:\n";
    std::copy(datas.begin(), datas.end(), std::ostream_iterator< elich::Data >(std::cout, "\n"));

    return 0;
}



