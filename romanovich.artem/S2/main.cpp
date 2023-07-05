#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "forwardlist.h"
#include "dict.h"
std::vector< std::string > splitString(const std::string &line, char del)
{
  std::vector< std::string > elems;
  std::string word;
  size_t startPos = 0;
  size_t endPos = line.find(del);
  while (endPos != std::string::npos)
  {
    word = line.substr(startPos, endPos - startPos);
    elems.push_back(word);
    startPos = endPos + 1;
    endPos = line.find(del, startPos);
  }
  word = line.substr(startPos, endPos);
  elems.push_back(word);
  return elems;
}
int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "No file provided.\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Cannot open file.\n";
    return 1;
  }
  using dict_type = Dictionary< int, std::string >;
  using dict_value_type = std::pair< int, std::string >;
  using container_type = Dictionary< std::string, dict_type >;
  using container_value_type = std::pair< std::string, dict_type >;
  container_type dictionary;
  std::string line;
  while (std::getline(input, line))
  {
    std::vector< std::string > lineWords = splitString(line, ' ');
    std::string dictName = lineWords[0];
    dict_type dictData;
    for (size_t i = 1; i < lineWords.size(); i += 2)
    {
      int key = std::stoi(lineWords[i]);
      std::string val = lineWords[i + 1];
      std::cout << key << " " << val << "\n";
      dictData.emplace(dict_value_type(key, val));
    }
    dictionary.emplace(container_value_type(dictName, dictData));
  }
}
