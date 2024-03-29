#include <cstddef>
#include <fstream>
#include <iostream>
#include <limits>
#include <DictWithCommands.h>
#include <IOstreamOverloads.h>
#include <dictionary.h>
#include <ForwardList/ForwardConstIterator.h>
#include <ForwardList/ForwardIterator.h>
#include <ForwardList/forwardList.h>

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Wrong number of arguments\n";
    return 1;
  }
  else
  {
    std::ifstream input;
    input.open(argv[1]);
    if (!input.is_open())
    {
      std::cerr << "Can't open file\n";
      return 1;
    }
    using dict = mashkin::Dictionary< int, std::string >;
    using dictionaries = mashkin::Dictionary< std::string, dict >;
    constexpr auto maxSize = std::numeric_limits< std::streamsize >::max();
    dictionaries dicts;
    while (!input.eof())
    {
      if (input.fail())
      {
        input.clear();
      }
      input >> dicts;
    }
    using Commands = mashkin::Dictionary< std::string, void (*)(std::istream&, dictionaries&) >;
    Commands commands;
    commands = mashkin::createDictWithCommnads< Commands >();
    std::string command;
    while (!std::cin.eof())
    {
      std::cin >> command;
      if (std::cin.eof())
      {
        break;
      }
      try
      {
        if (commands.contains(command))
        {
          commands[command](std::cin, dicts);
        }
        else
        {
          throw std::logic_error("Logic error");
        }
      }
      catch (const std::logic_error& ex)
      {
        std::cout << "<INVALID COMMAND>\n";
        std::cin.setstate(std::ios::failbit);
      }
      if (std::cin.fail())
      {
        std::cin.clear();
        std::cin.ignore(maxSize, '\n');
      }
    }
  }
  return 0;
}
