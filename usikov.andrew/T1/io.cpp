#include <string>

#include "iotypes.h"

usikov::StreamGuard::StreamGuard( std::basic_ios<char> &ref ) :
  strm_(ref), fill_(ref.fill()), prec_(ref.precision()), flags_(ref.flags())
{
}

usikov::StreamGuard::~StreamGuard( void )
{
  strm_.fill(fill_);
  strm_.precision(prec_);
  strm_.flags(flags_);
}

std::istream & usikov::operator >>( std::istream &stream, usikov::Delim &&res )
{
  std::istream::sentry sentry(stream);

  if (!sentry)
    return stream;

  std::string inputDelim;

  for (int i = 0; i < res.length_; i++)
  {
    char ch;

    stream >> ch;
    inputDelim += ch;
  }

  if (!stream)
    return stream;

  bool isFind = false;

  for (const auto &delim : res.valid_)
  {
    if (delim == inputDelim)
    {
      isFind = true;
      break;
    }
  }

  if (!isFind)
    stream.setstate(std::istream::failbit);

  return stream;
}

std::istream & usikov::operator >>( std::istream &stream, usikov::ULLInput &&res )
{
  std::istream::sentry sentry(stream);

  if (!sentry)
    return stream;

  return stream >> res.val_ >> Delim({"ULL", "ull"}, 3);
}

std::istream & usikov::operator >>( std::istream &stream, usikov::HexInput &&res )
{
  std::istream::sentry sentry(stream);
  StreamGuard guard(stream);

  if (!sentry)
    return stream;

  return stream >> Delim({"0x", "0X"}, 2) >> std::hex >> res.val_;
}

std::istream & usikov::operator >>( std::istream &stream, usikov::StrInput &&res )
{
  std::istream::sentry sentry(stream);

  if (!sentry)
    return stream;

  return std::getline(stream >> Delim({"\""}, 1), res.val_, '"');
}

std::istream & usikov::operator >>( std::istream &stream, usikov::Data &res )
{
  std::istream::sentry sentry(stream);
  auto savePos = stream.tellg();

  if (!sentry)
    return stream;

  res.isFail_ = false;
  bool flags[3] = {false};

  auto inputType = [&]
  ( const std::string &key, Data &input )
  {
    int spaceChar = stream.get(),
        afterSpaceChar = stream.get();

    if (!stream || spaceChar != ' ' || isspace(afterSpaceChar))
    {
      stream.setstate(std::istream::failbit);
      return;
    }

    stream.seekg(-1, std::istream::cur);
    if (key == "key1")
    {
      flags[0] = true;
      stream >> ULLInput{input.key1_};
    }
    else if (key == "key2")
    {
      flags[1] = true;
      stream >> HexInput{input.key2_};
    }
    else if (key == "key3")
    {
      flags[2] = true;
      stream >> StrInput{input.key3_};
    }
    else
    {
      stream.setstate(std::istream::failbit);
    }
  };

  Data input;
  stream >> Delim({"(:"}, 2);

  for (int i = 0; i < 3; i++)
  {
    std::string key;

    if (!stream)
      break;

    stream >> key;
    inputType(key, input);
    stream >> Separator(':');
  }
  stream >> Separator(')');

  for (int i = 0; i < 3; i++)
  {
    if (!flags[i])
      stream.setstate(std::istream::failbit);
  }

  res = input;
  if (!stream)
  {
    res.isFail_ = true;
    stream.clear();
    stream.seekg(savePos);
    stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  return stream;
}

std::ostream & usikov::operator <<( std::ostream &stream, const usikov::Data &data )
{
  std::ostream::sentry sentry(stream);

  if (!sentry)
    return stream;

  StreamGuard guard(stream);

  stream << "(:key1 " << data.key1_ << 
            "ull:key2 " << std::uppercase << std::hex << "0x" << data.key2_ <<
            ":key3 \"" << data.key3_ << "\":)";
  return stream;
}
