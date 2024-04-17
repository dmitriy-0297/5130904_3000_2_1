#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <iosfwd>
#include <string>

namespace elich
{
    struct Data
    {
        double key1;
        char key2;
        std::string key3;
    };

    struct DelimiterIO
    {
        char exp;
    };

    struct CharIO
    {
        char& ref;
    };

    struct StringIO
    {
        std::string& ref;
    };

    struct ScientificDoubleIO
    {
        double& ref;
    };

    std::istream& operator>>(std::istream&, Data&);
    std::ostream& operator<<(std::ostream&, const Data&);
    bool operator<(const Data&, const Data&);

    std::istream& operator>>(std::istream&, DelimiterIO&&);
    std::istream& operator>>(std::istream&, CharIO&&);
    std::istream& operator>>(std::istream&, StringIO&&);
    std::istream& operator>>(std::istream&, ScientificDoubleIO&&);

    std::ostream& operator<<(std::ostream&, const ScientificDoubleIO&);
    std::ostream& operator<<(std::ostream&, const StringIO&);
    std::ostream& operator<<(std::ostream&, const CharIO&);
}

#endif

