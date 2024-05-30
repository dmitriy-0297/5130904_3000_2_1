#include <iostream>
#include <string>
#include <vector>
#include "Polygon.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " filename\n";
        return 1;
    }

    std::string filename = argv[1];
    std::vector<Polygon> polygons = readPolygonsFromFile(filename);
    std::string command;
    while (std::getline(std::cin, command)) {
        executeCommand(command, polygons);
    }

    return 0;
}
