#include "data_struct.h"
#include <iostream>
#include <iomanip>
namespace
{
    class iofmtguard
    {
    public:
        iofmtguard(std::basic_ios< char >& s);
        ~iofmtguard();
    private:
        std::basic_ios< char >& s_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios< char >::fmtflags fmt_;
    };
    iofmtguard::iofmtguard(std::basic_ios< char >& s) :
        s_(s),
        fill_(s.fill()),
        precision_(s.precision()),
        fmt_(s.flags())
    {}
    iofmtguard::~iofmtguard()
    {
        s_.fill(fill_);
        s_.precision(precision_);
        s_.flags(fmt_);
    }
}
std::istream& elich::operator>>(std::istream& in, Data& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    Data input;
    in >> DelimiterIO{ '(' } >> DelimiterIO{ ':' };
    for (auto i = 0; i < 3 && in; i++)
    {
        std::string key = "";
        in >> key;
        if (key == "key1")
        {
            in >> ScientificDoubleIO{ input.key1 };
        }
        else if (key == "key2")
        {
            in >> CharIO{ input.key2 };
        }
        else if (key == "key3")
        {
            in >> StringIO{ input.key3 };
        }
        else
        {
            in.setstate(std::ios::failbit);
        }
        in >> DelimiterIO{ ':' };
    }
    in >> DelimiterIO{ ')' };
    if (in)
    {
        dest = input;
    }
    return in;
}
std::ostream& elich::operator<<(std::ostream& out, const Data& src)
{
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
        return out;
    }
    Data tmp = src;
    iofmtguard fmtguard(out);
    out << "(:key1 " << ScientificDoubleIO{ tmp.key1 };
    out << ":key2 " << CharIO{ tmp.key2 };
    out << ":key3 " << StringIO{ tmp.key3 } << ":)";
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
std::istream& elich::operator>>(std::istream& in, DelimiterIO&& dest)
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
        in.setstate(std::ios::failbit);
    }
    return in;
}
std::istream& elich::operator>>(std::istream& in, CharIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    return in >> DelimiterIO{ '\'' } >> dest.ref >> DelimiterIO{ '\'' };
}
std::istream& elich::operator>>(std::istream& in, StringIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    in >> DelimiterIO{ '"' };
    return std::getline(in, dest.ref, '"');
}
std::istream& elich::operator>>(std::istream& in, ScientificDoubleIO&& dest)
{
    if (!std::istream::sentry(in))
    {
        return in;
    }
    return in >> dest.ref;
}
std::ostream& elich::operator<<(std::ostream& out, const StringIO& data)
{
    if (!std::ostream::sentry(out))
    {
        return out;
    }
    return out << '"' << data.ref << '"';
}
std::ostream& elich::operator<<(std::ostream& out, const ScientificDoubleIO& data)
{
    if (!std::ostream::sentry(out))
    {
        return out;
    }
    int eToThe = 0;
    double numberDouble = data.ref;
    if (numberDouble < 1 && numberDouble != 0)
    {
        for (; numberDouble < 1; eToThe--)
        {
            numberDouble *= 10;
        }
    }
    else
    {
        for (; numberDouble > 9; eToThe++)
        {
            numberDouble /= 10;
        }
    }
    iofmtguard guard(out);
    out << std::fixed << std::setprecision(2);
    out << numberDouble << 'e' << std::showpos << eToThe;
    return out;
}
std::ostream& elich::operator<<(std::ostream& out, const CharIO& data)
{
    if (!std::ostream::sentry(out))
    {
        return out;
    }
    return out << '\'' << data.ref << '\'';
}

