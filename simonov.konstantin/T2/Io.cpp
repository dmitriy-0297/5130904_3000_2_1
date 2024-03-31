#include "Io.h"
#include <string>
#include <limits>
#include <iterator>

std::istream& simonov::operator>>(std::istream& in, Border&& fence)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  std::string input;
  short i = 0;
  while (i != fence.length_)
  {
    char symbol;

    in >> symbol;
    input += symbol;
    i++;
  }

  bool allGood = false;
  for (int j = 0; j < fence.borders.size(); j++)
  {
    if (input == fence.borders[j])
    {
      allGood = true;
      break;
    }
  }

  if (allGood == false)
  {
    in.setstate(std::istream::failbit);
  }

  return in;
}

std::istream& simonov::operator>>(std::istream& in, StrKey&& str)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> Border({ "\"" }, 1), str.valueStr, '"');
}

std::istream& simonov::operator>>(std::istream& in, ULLLit&& lit)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  return in >> lit.valueLit >> Border({"ull", "ULL"}, 3);
}

std::istream& simonov::operator>>(std::istream& in, ULLOct&& oct)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  std::string temp;

  return in >> Border({"0"}, 1) >> std::oct >> oct.valueOct;
}

std::istream& simonov::operator>>(std::istream& in, Data& data)
{
  using blok = Border;
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::istream::streampos position = in.tellg();
  data.thatIsHorror = false;
  bool keys[3] = { false };
  Data input;
  in >> blok({ "(:" }, 2);

  for (int i = 0; i < 3; i++)
  {
    std::string key;

    if (!in)
    {
      break;
    }

    in >> key;
    whichKeyYouWrote(key, input, in, keys);
    in >> blok({ ":" }, 1);
  }
  in >> blok({")"}, 1);

  for (int i = 0; i < 3; i++)
  {
    if (!keys[i])
    {
      in.setstate(std::istream::failbit);
    }
  }

  data = input;

  if (!in)
  {
    data.thatIsHorror = true;
    in.clear();
    in.seekg(position);
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  return in;
}

std::ostream& simonov::operator<<(std::ostream& out, const simonov::Data& data)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  StreamGuard temp(out);

  out << "(:key1 " << data.key1 << "ull:key2 " << std::oct << "0" << data.key2 << ":key3 \"" << data.key3 << "\":)";
  return out;
}

void simonov::whichKeyYouWrote(const std::string& key, Data& data, std::istream& in, bool keys[])
{

  using lit = ULLLit;
  using oct = ULLOct;
  using str = StrKey;

  char chCurrent = in.get();
  char chNext = in.get();
  if (!in || chCurrent != ' ' || chNext == ' ')
  {
    in.setstate(std::istream::failbit);
    return;
  }
  else
  {
    in.seekg(-1, std::istream::cur);
    if (key == "key1")
    {
      keys[0] = true;
      in >> lit{ data.key1 };
      return;
    }
    if (key == "key2")
    {
      keys[1] = true;
      in >> oct{ data.key2 };
      return;
    }
    if (key == "key3")
    {
      keys[2] = true;
      in >> str{ data.key3 };
      return;
    }
    else
    {
      in.setstate(std::istream::failbit);
    }
  }
}

simonov::StreamGuard::StreamGuard(std::basic_ios<char>& s):
strm_(s), fill_(s.fill()), precision_(s.precision()), fmt_(s.flags())
{
}

simonov::StreamGuard::~StreamGuard()
{
  strm_.fill(fill_);
  strm_.precision(precision_);
  strm_.flags(fmt_);
}
