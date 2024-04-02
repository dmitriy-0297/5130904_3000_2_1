#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <iomanip>
#include <algorithm>

namespace nspace {
    struct DataStruct {
        char key1;
        std::pair<long long, unsigned long long> key2;
        std::string key3;
    };
    struct DelimiterIO
    {
        char exp;
    };
    struct Raitional
    {
        std::pair<long long, unsigned long long>& ref;
    };
    struct StringIO
    {
        std::string& ref;
    };
    class iofmtguard {
    public:
        iofmtguard(std::basic_ios< char >& s);
        ~iofmtguard();
    private:
        std::basic_ios< char >& s_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios< char >::fmtflags fmt_;
    };
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, Raitional&& dest);
    std::istream& operator>>(std::istream& in, StringIO&& dest);
    std::istream& operator>>(std::istream& in, DataStruct& dest);
    std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
}
int main() {
    using nspace::DataStruct;
    std::vector< DataStruct > data;
    while (std::cin.good())
    {
        std::string input;
        std::getline(std::cin, input);
        std::istringstream inputStream(input);
        std::copy(
            std::istream_iterator< DataStruct >(inputStream),
            std::istream_iterator< DataStruct >(),
            std::back_inserter(data)
        );
    }
    std::sort(data.begin(), data.end(), [](const DataStruct& a, const DataStruct& b) {
        if (a.key1 != b.key1)
        {
            return a.key1 < b.key1;
        }
        else if (a.key2 != b.key2)
        {
            return a.key2 < b.key2;
        }
        return a.key3 < b.key3;
        });
    std::copy(
        std::begin(data),
        std::end(data),
        std::ostream_iterator< DataStruct >(std::cout, "\n")
    );
    return 0;
}

namespace nspace
{
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        char c = '0';
        in >> c;
        if (in && (c != dest.exp))
        {
            std::cerr << char(dest.exp);
            in.setstate(std::ios::failbit);
        }
        return in;
    }
    std::istream& operator>>(std::istream& in, Raitional&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> DelimiterIO{ '(' } >> DelimiterIO{ ':' } >> DelimiterIO{ 'N' }
            >> dest.ref.first >> DelimiterIO{ ':' }
            >> DelimiterIO{ 'D' } >> dest.ref.second
            >> DelimiterIO{ ':' } >> DelimiterIO{ ')' };
    }
}
