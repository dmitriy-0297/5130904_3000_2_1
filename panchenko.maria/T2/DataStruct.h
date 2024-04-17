#pragma once
#include <iostream>
#include <string>

namespace panchenko {
    struct DataStruct
    {
        unsigned long long key1;
        unsigned long long key2;
        std::string key3;

        DataStruct() : key1(0), key2(0), key3("") {}
    };

    std::istream& operator>>(std::istream& is, DataStruct& data);
    bool compareDataStruct(const DataStruct& a, const DataStruct& b);
    std::ostream& operator<<(std::ostream& os, const DataStruct& data);
    int decToBin(int num);
}
