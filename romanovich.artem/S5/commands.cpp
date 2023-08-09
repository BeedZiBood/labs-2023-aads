#include "commands.h"
namespace
{
  struct ValuePrinter
  {
    void operator()(const romanovich::map_value_t &data/*, std::ostream &out*/)
    {
      std::cout << " " << data.second;
    }
  };
  struct KeySumCalc
  {
    int operator()(const romanovich::map_t &map)
    {
      int total = 0;
      for (auto &data: map)
      {
        total += data.first;
      }
      return total;
    }
  };
  struct LnrTraverse
  {
    void operator()(std::ostream &out, const romanovich::map_t &map) const
    {
      KeySumCalc keySumCalc;
      out << keySumCalc(map);
      ValuePrinter valuePrinter;
      map.traverseLnr(valuePrinter);
    }
  };
}
namespace romanovich
{
  command_map_t createCommandDictionary()
  {
    std::string lnrCall = "ascending";
    command_map_t commands;
    using namespace std::placeholders;
    commands[lnrCall] = std::function< void(std::ostream &, map_t &) >(LnrTraverse());
    return commands;
  }
}