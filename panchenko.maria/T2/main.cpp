#include <iostream>
#include <vector>
#include <algorithm>
#include "DataStruct.h"

int main() {
    std::vector<panchenko::DataStruct> dataVector;

    panchenko::DataStruct data;
    while ((std::cin >> data) || (!std::cin.eof() && std::cin.fail())) {
        if (std::cin.fail()) {
            std::cin.clear(); 
            continue; 
        }
        dataVector.push_back(data);
    }

    std::sort(dataVector.begin(), dataVector.end(), panchenko::compareDataStruct);

    for (const auto& data : dataVector) {
        std::cout << data << std::endl;
    }

    return EXIT_SUCCESS;
}
