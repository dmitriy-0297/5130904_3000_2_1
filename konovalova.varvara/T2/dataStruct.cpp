#include "dataStruct.hpp"
#include "delimeter.hpp"
#include "parsers.hpp"

#include <iostream>

bool konovalova::DataStruct::operator<(const DataStruct & other) const noexcept
{
    if(key1 == other.key1)
    {
        if(key2 == other.key2)
        {
            return key3.size() < other.key3.length();
        }
        else
        {
            return std::norm(key2) < std::norm(other.key2);
        }
    }
    else
    {
        return key1 < other.key1;
    }
}

std::istream & konovalova::operator>>(std::istream & in, DataStruct & data)
{
    std::istream::sentry guard(in);
    if(!guard)
    {
        return in;
    }

    in >> delimeter_char{'('};
    int key;
    for (int i = 0; i < 3; i++) {
        in >> delimeter_string{":key"} >> key;
        switch(key)
        {
            case 1:
                in >> ullOctType{data.key1};
                break;
            case 2:
                in >> cmpType{data.key2};
                break;
            case 3:
                in >> strType{data.key3};
                break;
        }
    }
    in >> delimeter_string{":)"};
    
    return in;
}

std::ostream & konovalova::operator<<(std::ostream & out, const DataStruct & data)
{
    std::ostream::sentry guard(out);
    if(!guard)
    {
        return out;
    }

    DataStruct structCopy = data;

    out << "(:key1 " << ullOctType{structCopy.key1};
    out << ":key2 " << cmpType{structCopy.key2};
    out << ":key3 " << strType{structCopy.key3} << ":)";

    return out;
}