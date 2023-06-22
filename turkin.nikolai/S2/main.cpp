#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <functional>
#include "dictionary.hpp"
#include "forward-list.hpp"

int main(int argc, char * argv[])
{
  if (argc == 1)
  {
    std::cerr << "no file\n";
    return 1;
  }

  std::ifstream file;
  file.open(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "cannot open file\n";
    return 1;
  }
  using dict_t = turkin::Dictionary< std::size_t, std::string, std::less< std::size_t > >;
  dict_t dict;
  dict.insert(12, "asdsdad");
  std::cout << dict.count(12) << "\n";
  std::cout << "asd\n";
  /*
  std::string name;
  std::size_t key;
  std::string value;
  while (file)
  {
    file >> name;
    while
    file >> key >> value;
    std::cout <<  << "\n";
  }
*/
  return 0;
}
