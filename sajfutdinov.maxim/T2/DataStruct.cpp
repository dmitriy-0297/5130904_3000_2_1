#include "DataStruct.h"

std::istream& sajfutdinov::operator>>(std::istream& in, DelimiterIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    char c;
    in >> c;
    if (in && (c != dest.exp))
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& sajfutdinov::operator>>(std::istream& in, LabelIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    std::string data = "";
    if ((in >> data ) && (data != dest.exp))
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& sajfutdinov::operator>>(std::istream& in, RationalIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    long long numerator;
    unsigned long long denominator;
    in >> LabelIO{ "(:N" } >> numerator >> DelimiterIO{ ':' } >> LabelIO{ "D" } >> denominator >> DelimiterIO{ ':' } >> DelimiterIO{ ')' };
    dest.ref = std::make_pair(numerator, denominator);

    return in;
};

std::istream& sajfutdinov::operator>>(std::istream& in, StringIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}

std::istream& sajfutdinov::operator>>(std::istream& in, DataStruct& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    using delimiter = DelimiterIO;
    in >> delimiter{ '(' };

    for (int i = 0; i < 3; i++)
    {
        std::string key;
        in >> delimiter{ ':' };
        in >> key;

        if (key == "key1")
        {
            in >> delimiter{ '\'' };
            char temp;
            in >> temp;
            in >> delimiter{ '\'' };
            dest.key1 = temp;
        }
        else if (key == "key2")
        {
            using rational = RationalIO;
            in >> rational{ dest.key2 };
        }
        else if (key == "key3")
        {
            using text = StringIO;
            in >> text{ dest.key3 };
        }
    }

    in >> delimiter{ ':' };
    in >> delimiter{ ')' };
    return in;
}

std::ostream& sajfutdinov::operator<<(std::ostream& out, const DataStruct& src)
{
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
        return out;
    }
    iofmtguard fmtguard(out);
    out << "(:key1 \'" << std::fixed << std::setprecision(1) << src.key1 << "\':";
    out << "key2 (:N " << src.key2.first << ":D " << src.key2.second << ":):";
    out << "key3 \"" << src.key3 << "\":)";
    return out;
}

sajfutdinov::iofmtguard::iofmtguard(std::basic_ios< char >& s) :
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
{}

sajfutdinov::iofmtguard::~iofmtguard()
{
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
}

bool sajfutdinov::compareData(const DataStruct& a, const DataStruct& b)
{
    if (a.key1 != b.key1) {
        return a.key1 < b.key1;
    }
    if (a.key2 != b.key2) {
        return a.key2 < b.key2;
    }
    return a.key3.size() < b.key3.size();
}
