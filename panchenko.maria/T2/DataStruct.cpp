#include "DataStruct.h"
#include <bitset>
#include <regex>


std::istream& panchenko::operator>>(std::istream& in, DataStruct& data)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    std::string line;

    std::getline(in, line);

    std::regex key1Pattern(R"(:key1\s+(\d+)[uU]{1}[lL]{2})");
    std::regex key2Pattern(R"(:key2\s+0[bB]([01]+))");
    std::regex key3Pattern(R"(:key3\s+\"([^\"]*)\")");
    std::smatch match;

    bool allKeysFound = false;

    int keyCount = 0;
    int NUMKEY = 3;

    if (line.front() == '(' && line.back() == ')')
    {
        line = line.substr(1, line.size() - 2);

        std::vector<bool> keyFound(3, false);

        while (std::regex_search(line, match, key1Pattern) || std::regex_search(line, match, key2Pattern) || std::regex_search(line, match, key3Pattern))
        {
            if (std::regex_search(line, match, key1Pattern))
            {
                unsigned long long num = std::stoull(match[1]);
                data.key1 = num;
                keyFound[0] = true;
                keyCount++;
                line = std::regex_replace(line, key1Pattern, "");
            }
            else if (std::regex_search(line, match, key2Pattern))
            {
                std::string binStr = match[1];
                unsigned long long num = std::stoull(binStr, nullptr, 2);
                data.key2 = num;
                keyFound[1] = true;
                keyCount++;
                line = std::regex_replace(line, key2Pattern, "");
            }
            else if (std::regex_search(line, match, key3Pattern))
            {
                std::string str = match[1];
                data.key3 = str;
                keyFound[2] = true;
                keyCount++;
                line = std::regex_replace(line, key3Pattern, "");
            }
        }

        if (keyCount > NUMKEY)
        {
            in.setstate(std::ios::failbit);
        }

        if (std::all_of(keyFound.begin(), keyFound.end(), [](bool found) { return found; }))
        {
            allKeysFound = true;
        }
    }

    if (!allKeysFound or line != ":")
    {
        in.setstate(std::ios::failbit);
    }

    return in;
}

int panchenko::decToBin(int num)
{
    int bin = 0, k = 1;

    while (num)
    {
        bin += (num % 2) * k;
        k *= 10;
        num /= 2;
    }

    return bin;
}

bool panchenko::compareDataStruct(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) {
        return a.key1 < b.key1;
    }
    else if (a.key2 != b.key2) {
        return a.key2 < b.key2;
    }
    else {
        return a.key3.size() < b.key3.size();
    }
}

std::ostream& panchenko::operator<<(std::ostream& out, const DataStruct& data)
{
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
        return out;
    }
    out << "(:key1 " << data.key1 << "ull";
    out << ":key2 " << "0b" << decToBin(data.key2);
    out << ":key3 " << '"' << data.key3 << '"' << ":)";
    return out;
}
