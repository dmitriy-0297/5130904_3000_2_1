#include "io.h"
#include <vector>

int main(void)
{
  std::vector<sevostyanova::Data> vc;
  std::string str = "";
  while (!std::cin.eof())
  {
    std::getline(std::cin, str,'\n');
    if (str == "" || std::cin.eof())
      break;
    if (sevostyanova::isCorrectTypes(str))
    {
      std::istringstream input(str);
      sevostyanova::Data ds;
      input >> ds;
      vc.push_back(ds);
    }
  }
  std::sort(vc.begin(), vc.end(),
  [](const sevostyanova::Data& el1, const sevostyanova::Data& el2)
  {
    if (el1.key1_ == el2.key1_)
    {
      if (el1.key2_ == el2.key2_)
        return el1.key3_.length() < el2.key3_.length();
      return el1.key2_ < el2.key2_;
    }
    return el1.key1_ < el2.key1_;
  });
  std::copy(vc.begin(), vc.end(), std::ostream_iterator<sevostyanova::Data>(std::cout));

  return EXIT_SUCCESS;
}
