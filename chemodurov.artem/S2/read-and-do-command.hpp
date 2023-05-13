#ifndef S2_READ_AND_DO_COMMAND_HPP
#define S2_READ_AND_DO_COMMAND_HPP
#include "create-command-dictionary.hpp"

namespace chemodurov
{
  std::string readCommand(std::istream & in);
  void doCommand(const std::string & name_command,
      const Dictionary< std::string, command_t > & commands,
      Dictionary< std::string, dic_t > & data,
      std::istream & in,
      std::ostream & out);
}

#endif
