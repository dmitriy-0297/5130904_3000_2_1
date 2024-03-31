#include <sstream>
#include <algorithm>
#include <iterator>
#include "Io.h"

int main()
{
  using namespace simonov;
  std::vector<Data> myVector;
  std::string str;

  while (true)
  {
    std::string input;

    if ((getline(std::cin, input)) && !input.empty())
    {
      str += input + "\n";
    }
    else
    {
      break;
    }
  }

  std::stringstream ss(str);
  std::copy_if(
    std::istream_iterator<Data>(ss),
    std::istream_iterator<Data>(),
    std::back_inserter(myVector),
    [&](const Data& data)
    {
      return !data.thatIsHorror;
    }
  );

  std::sort(myVector.begin(), myVector.end(),
    [](const Data& data1, const Data& data2)
    {
      if (data1.key1 == data2.key1)
      {
        if (data1.key2 == data2.key2)
        {
          return data1.key3.length() < data2.key3.length();
        }
        return data1.key2 < data2.key2;
      }
      return data1.key1 < data2.key1;
    });

  std::copy(
    std::begin(myVector),
    std::end(myVector),
    std::ostream_iterator<Data>(std::cout, "\n")
  );

  return EXIT_SUCCESS;
}
