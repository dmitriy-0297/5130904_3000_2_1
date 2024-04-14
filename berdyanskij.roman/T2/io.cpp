#include "io.h"

std::pair<std::string, std::string> berdyanskij::get_next_pair(std::string& s)
{
    s.erase(0, s.find(':') + 1); // remove ':' from the beginning of string
    std::string key = s.substr(0, 4);
    s.erase(0, 5);
    std::string value;
    if (key == "key3")
    {
        value = s.substr(0, s.find('"', 1) + 1);
        s.erase(0, value.size());
    }
    else
    {
        value = s.substr(0, s.find(':'));
        s.erase(0, value.size());
    }
    return std::make_pair(key, value); // key, value
}
std::istream& berdyanskij::operator>>(std::istream& in, berdyanskij::DataStruct& ds)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    ds.valid = true;
    std::string token;
    getline(in, token);
    while (!token.empty())
    {
        std::pair<std::string, std::string> pair = berdyanskij::get_next_pair(token);
        if (pair.first == "key1")
        {
            if (!berdyanskij::is_double(pair.second))
            {
                ds.valid = false;
                break;
            }
            ds.key1 = std::stod(pair.second);
        }
        else if (pair.first == "key2")
        {
            if (!berdyanskij::is_long(pair.second)) {
                ds.valid = false;
                break;
            }
            ds.key2 = std::stoll(pair.second);
        }
        else if (pair.first == "key3")
        {
            if (!berdyanskij::is_string(pair.second))
            {
                ds.valid = false;
                break;
            }
            ds.key3 = pair.second.substr(1, pair.second.size() - 2);
        }
    }
    return in;
}
std::string berdyanskij::get_scientific(double x)
{
    std::stringstream ss;
    ss << std::scientific << x;
    std::string out = ss.str();
    size_t i = std::min(out.find('E'), out.find('e'));
    while (out[i - 1] == '0' && out[i - 2] != '.')
    {
        out.erase(i - 1, 1);
        i = std::min(out.find('E'), out.find('e'));
    }
    while (out[i + 2] == '0')
    {
        out.erase(i + 2, 1);
        i = std::min(out.find('E'), out.find('e'));
    }
    return out;
}
std::ostream& berdyanskij::operator<<(std::ostream& out, const berdyanskij::DataStruct& ds) {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
        return out;
    }
    iofmtguard fmtguard(out);
    out << "(:key1 " << get_scientific(ds.key1) << ":key2 " << ds.key2 << ":key3 \"" << ds.key3 << "\":)";
    return out;
}

bool berdyanskij::is_double(const std::string& str)
{
    std::regex pattern("^[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)$");
    return std::regex_match(str, pattern);
}
bool berdyanskij::is_long(const std::string& str)
{
    std::regex pattern("^-?[0-9]+(ll|LL)?$");
    return std::regex_match(str, pattern);
}
bool berdyanskij::is_string(const std::string& str)
{
    std::regex pattern("\".*\"");
    return std::regex_match(str, pattern);
}
berdyanskij::iofmtguard::iofmtguard(std::basic_ios< char >& s) :
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
{}
berdyanskij::iofmtguard::~iofmtguard()
{
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
}
