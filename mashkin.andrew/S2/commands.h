#ifndef S2_COMMANDS_H
#define S2_COMMANDS_H
#include <iostream>
#include <string>
#include "dictionary.h"
#include "IOrealization.h"

namespace mashkin
{
  void print(std::istream& inp, dictionaries& dicts);
  void complement(std::istream& inp, dictionaries& dicts);
  void intersect(std::istream& inp, dictionaries& dicts);
  void unionDicts(std::istream& inp, dictionaries& dicts);
}
#endif
