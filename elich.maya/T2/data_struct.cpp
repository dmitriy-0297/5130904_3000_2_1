#include "data_struct.h"

#include <iostream>
#include <iomanip>

#include "fmtguard.h"
#include "io_keys.h"

void ParseToken(std::string& token, std::string& key, std::string& value) {
    token.erase(0, token.find(':') + 1);
    key = token.substr(0, 4);
    token.erase(0, 5);
    value = token.substr(0, token.find(':'));
    token.erase(0, value.size());
}

std::istream& elich::operator>>(std::istream& in, Data& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    dest.valid = true;
    in >> DelimiterIO{ '(' };
    std::string token = "", key = "", value = "";
    getline(in, token, ')');
    for (auto i = 0; i < 3 && in; i++)
    {
        ParseToken(token, key, value);
        if (key == "key1")
        {
            if (!IsScientificDoubleIO(value)) {
                dest.valid = false;
            }
            else {
                dest.key1 = stof(value);
            }

        }
        else if (key == "key2")
        {
            if (!IsCharIO(value)) {
                dest.valid = false;
            }
            else {
                dest.key2 = value[1];
            }
        }
        else if (key == "key3")
        {
            if (!IsStringIO(value)) {
                dest.valid = false;
            }
            else {
                dest.key3 = value;
            }
        }
    }
    return in;
}

std::ostream& elich::operator<<(std::ostream& out, const Data& src)
{
    std::ostream::sentry sentry(out);
    if (!sentry || !src.valid)
    {
        return out;
    }
    Data tmp = src;
    iofmtguard fmtguard(out);
    out << "(:key1 " << ScientificDoubleIO{ tmp.key1 };
    out << ":key2 " << CharIO{ tmp.key2 };
    out << ":key3 " << StringIO{ tmp.key3 } << ":)\n";
    return out;
}

bool elich::operator<(const Data& a, const Data& b)
{
    if (a.key1 != b.key1)
    {
        return a.key1 < b.key1;
    }
    if (a.key2 != b.key2)
    {
        return a.key2 < b.key2;
    }
    return a.key3.length() < b.key3.length();
}
