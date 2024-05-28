#include "polygon.h"
#include "commands.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./program filename" << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<panchenko::Polygon> polygons;
    panchenko::Polygon polygon;
    while (file >> polygon) {
        if (!file.fail()) {
            polygons.push_back(polygon);
        } else {
            std::cerr << "Error reading polygon from file" << std::endl;
            return EXIT_FAILURE;
        }
    }

    try {
        std::string command;
        while (std::cin >> command) {
            if (command == "AREA") {
                std::string param;
                std::cin >> param;
                panchenko::area(polygons, param);
            } else if (command == "MIN") {
                std::string param;
                std::cin >> param;
                panchenko::min(polygons, param);
            } else if (command == "MAX") {
                std::string param;
                std::cin >> param;
                panchenko::max(polygons, param);
            } else if (command == "COUNT") {
                std::string param;
                std::cin >> param;
                panchenko::count(polygons, param);
            } else if (command == "LESSAREA") {
                panchenko::Polygon inputPolygon;
                std::cin >> inputPolygon;
                panchenko::lessArea(polygons, inputPolygon);
            } else if (command == "SAME") {
                panchenko::same(std::cin, std::cout, polygons);
            } else {
                std::cout << "<INVALID COMMAND>" << std::endl;
                std::string dummy;
                std::getline(std::cin, dummy);
            }
        }
    } catch (const std::exception&) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
