#ifndef S2_DICTWITHCOMMANDS_H
#define S2_DICTWITHCOMMANDS_H
#include <string>
#include "dictionary.h"

namespace mashkin
{
  using dict = mashkin::Dictionary< int, std::string >;
  using dictionaries = mashkin::Dictionary< std::string, dict >;
  Dictionary< std::string, void (*)(std::istream&, dictionaries&) > createDictWithCommnads();
}
#endif