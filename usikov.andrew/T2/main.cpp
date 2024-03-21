#include <sstream>
#include <algorithm>
#include <iterator>

#include "iotypes.h"

using namespace usikov;

int main( void )
{
  std::vector<Data> data;
  /* Sample: (:key1 30ull:key2 0xFFFF:key3 "LOLOLOL":) */

  std::cout << "Input data in format (:key1 <number>ull:key2 0x<hex>:key3 \"<string>\":)\n" << std::endl;
  std::string input;

  while (true)
  {
    std::string buf;

    std::getline(std::cin, buf, '\n');

    if (buf == "")
      break;

    input += buf + '\n';
  }

  std::stringstream ss(input);
  std::copy_if(
    std::istream_iterator<Data>(ss),
    std::istream_iterator<Data>(),
    std::back_inserter(data),
    [&]( const Data &d )
    {
      return !d.isFail_;
    }
  );

  std::sort(data.begin(), data.end(),
    []( const Data &d1, const Data &d2 )
    {
      if (d1.key1_ == d2.key1_)
      {
        if (d1.key2_ == d2.key2_)
          return d1.key3_.length() < d2.key3_.length();
        return d1.key2_ < d2.key2_;
      }
      return d1.key1_ < d2.key1_;
    });

  std::cout << "Data:\n";
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator< Data >(std::cout, "\n")
  );
}
