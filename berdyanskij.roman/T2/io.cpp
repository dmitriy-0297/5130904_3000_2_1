// io.cpp
#include <sstream>
#include <iomanip>

#include "io.h"

namespace berdyanskiy {
    std::istream& berdyanskiy::operator>>(std::istream& is, berdyanskiy::DataStruct& ds) {
        std::string line;
        if (std::getline(is, line, '(') && std::getline(is, line, ')')) {
            std::istringstream iss(line);
            std::string part;
            while (std::getline(iss, part, ':')) {
                std::string key, value;
                std::istringstream part_stream(part);
                if (part_stream >> key >> value) {
                    if (key == "key1") {
                        ds.key1 = std::stod(value);
                    }
                    else if (key == "key2") {
                        size_t end_pos = value.find_first_not_of("0123456789-");
                        if (end_pos != std::string::npos) {
                            value = value.substr(0, end_pos);
                        }
                        ds.key2 = std::stoll(value);
                    }
                    else if (key == "key3") {
                        ds.key3 = value.substr(1, value.length() - 2);
                    }
                }
            }
        }
        return is;
    }

    std::ostream& berdyanskiy::operator<<(std::ostream& os, const berdyanskiy::DataStruct& ds) {
        os << "(:key1 " << std::scientific << std::nouppercase << ds.key1
            << ":key2 " << ds.key2 << ":key3 \"" << ds.key3 << "\":)";
        return os;
    }
}
