#include "DataStruct.h"


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
    std::istream& operator>>(std::istream& in, StringIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
    }
    std::istream& operator>>(std::istream& in, DataStruct& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        DataStruct input;
        {
            using sep = DelimiterIO;
            using dbl = Raitional;
            using str = StringIO;
            in >> sep{ '(' } >> sep{ ':' };
            std::string key;
            for (int i = 0; i < 3; i++) {
                in >> key;
                if (key == "key1") {
                    in >> sep{ '\'' } >> input.key1 >> sep{ '\'' };
                }
                else if (key == "key2") {
                    in >> dbl{ input.key2 };
                }
                else if (key == "key3") {
                    in >> str{ input.key3 };
                }
                else {
                    in.setstate(std::ios::failbit);
                }

                in >> sep{ ':' };
            }
            in >> sep{ ')' };
        }
        if (in)
        {
            dest = input;
        }
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& src)
    {
        std::ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }
        iofmtguard fmtguard(out);
        out << "(:key1 \'" << src.key1 << "\':key2 (:N " << src.key2.first << ":D " << src.key2.second << ":):key3 \"" << src.key3 << "\":)";
        return out;
    }

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