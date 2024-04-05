#include "IO.h"

namespace kostushevich
{
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        char c = '0';
        in >> std::noskipws >> c;
        if (in && (c != dest.exp))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }
    std::istream& operator>>(std::istream& in, OctIO&& dest)
    {
        std::istream::sentry sentry(in);
        iofmtguard ioGard(in);
        if (!sentry)
        {
            return in;
        }
        in >> std::oct >> dest.ref;
        return in;
    }
    std::istream& operator>>(std::istream& in, ComplexIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        char c = '0';
        double real, imag;
        in >> real >> std::noskipws >> c >> imag;
        dest.ref = std::complex<double>(real, imag);
        return in;
    }
    std::istream& operator>>(std::istream& in, StringIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        std::string value;
        in >> std::quoted(value);
        dest.ref = value;
        return in;
    }
    std::istream& operator>>(std::istream& in, LabelIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        size_t size = dest.exp.size();
        std::string label;
        in >> std::setw(size) >> label;
        if (label != dest.exp)
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }
    std::istream& operator>>(std::istream& in, DataStruct& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        /*in >> DelimiterIO{ '(' };
        in >> LabelIO{ ":key1" } >> DelimiterIO{ ' ' } >> DelimiterIO{ '0' } >> OctIO{ dest.key1 } >> DelimiterIO{ ':' };
        in >> LabelIO{ "key2" } >> DelimiterIO{ ' ' } >> LabelIO{ "#c(" } >> ComplexIO{ dest.key2 } >> LabelIO{ "):" };
        in >> LabelIO{ "key3" } >> DelimiterIO{ ' ' } >> StringIO{ dest.key3 } >> DelimiterIO{ ':' };
        in >> DelimiterIO{ ')' };*/

        in >> DelimiterIO{ '(' };

        for (int i = 0; i < 3; i++)
        {
            std::string key_number;
            in >> DelimiterIO{ ':' };
            in >> key_number;

            if (key_number == "key1")
            {
                in >> DelimiterIO{ ' ' };
                in >> DelimiterIO{ '0' };
                in >> OctIO{ dest.key1 };
            }
            else if (key_number == "key2")
            {
                in >> DelimiterIO{ ' ' };
                in >> LabelIO{ "#c(" };
                in >> ComplexIO{ dest.key2 };
                in >> LabelIO{ ")" };
            }
            else if (key_number == "key3")
            {
                in >> DelimiterIO{ ' ' };
                in >> StringIO{ dest.key3 };
            }
        }

        in >> DelimiterIO{ ':' };
        in >> DelimiterIO{ ')' };
        return in;
    }
    std::ostream& operator<<(std::ostream& out, const DataStruct& dest)
    {
        std::ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }
        iofmtguard temp(out);
        out << "(:key1 " << std::oct << "0" << dest.key1 <<
            ":key2 " << "#c(" << std::fixed << std::setprecision(1) << dest.key2.real() << " " <<
            std::fixed << std::setprecision(1) << dest.key2.imag() << ")" <<
            ":key3 " << std::quoted(dest.key3) << ":)";
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
