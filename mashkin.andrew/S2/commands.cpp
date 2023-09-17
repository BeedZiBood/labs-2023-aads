#include "commands.h"
#include <iostream>
#include <stdexcept>
#include <IOstreamOverloads.h>

namespace mashkin
{
  void print(std::istream& inp, Dictionary< std::string, Dictionary< int, std::string > >& dicts)
  {
    std::string dictionary;
    inp >> dictionary;
    if (dicts.contains(dictionary))
    {
      auto iter = dicts.find(dictionary);
      if (iter->second.size() == 0)
      {
        std::cout << "<EMPTY>\n";
      }
      else
      {
        std::cout << iter->first << iter->second << "\n";
      }
    }
    else
    {
      throw std::logic_error("Logic error");
    }
  }

  void complement(std::istream& inp, Dictionary< std::string, Dictionary< int, std::string > >& dicts)
  {
    std::string newDict;
    inp >> newDict;
    std::string first;
    inp >> first;
    std::string second;
    inp >> second;
    if (!dicts.contains(second) || !dicts.contains(first))
    {
      throw std::logic_error("Logic error");
    }
    Dictionary< int, std::string > newDictionary;
    auto firstDict = dicts.find(first);
    auto firstBegin = firstDict->second.begin();
    auto firstEnd = firstDict->second.end();
    for (auto i = firstBegin; i != firstEnd; i++)
    {
      if (!dicts.find(second)->second.contains(i->first))
      {
        newDictionary.insert(*i);
      }
    }
    auto secondDict = dicts.find(second);
    auto secondBegin = secondDict->second.begin();
    auto secondEnd = secondDict->second.end();
    for (auto i = secondBegin; i != secondEnd; i++)
    {
      if (!dicts.find(first)->second.contains(i->first))
      {
        newDictionary.insert(*i);
      }
    }
    if (first == newDict)
    {
      dicts.find(first)->second.clear();
      dicts.find(first)->second.insert(newDictionary.begin(), newDictionary.end());
      return;
    }
    else if (second == newDict)
    {
      dicts.find(second)->second.clear();
      dicts.find(second)->second.insert(newDictionary.begin(), newDictionary.end());
      return;
    }
    else
    {
      dicts.insert({newDict, newDictionary});
    }
  }

  void intersect(std::istream& inp, Dictionary< std::string, Dictionary< int, std::string > >& dicts)
  {
    std::string newDict;
    inp >> newDict;
    std::string first;
    inp >> first;
    std::string second;
    inp >> second;
    if (dicts.contains(newDict) && newDict != first && newDict != second)
    {
      dicts.find(newDict)->second.clear();
    }
    if (!dicts.contains(second) || !dicts.contains(first))
    {
      throw std::logic_error("Logic error");
    }
    Dictionary< int, std::string > newDictionary;
    auto firstDict = dicts.find(first);
    auto firstBegin = firstDict->second.begin();
    auto firstEnd = firstDict->second.end();
    for (auto i = firstBegin; i != firstEnd; i++)
    {
      if (dicts.find(second)->second.contains(i->first))
      {
        newDictionary.insert(*i);
      }
    }
    if (first == newDict)
    {
      dicts.find(first)->second.clear();
      dicts.find(first)->second.insert(newDictionary.begin(), newDictionary.end());
      return;
    }
    else if (second == newDict)
    {
      dicts.find(second)->second.clear();
      dicts.find(second)->second.insert(newDictionary.begin(), newDictionary.end());
      return;
    }
    else
    {
      dicts.insert({newDict, newDictionary});
    }
  }

  void unionDicts(std::istream& inp, Dictionary< std::string, Dictionary< int, std::string > >& dicts)
  {
    std::string newDict;
    inp >> newDict;
    std::string first;
    inp >> first;
    std::string second;
    inp >> second;
    if (!dicts.contains(second) || !dicts.contains(first))
    {
      throw std::logic_error("Logic error");
    }
    Dictionary< int, std::string > newDictionary = dicts.find(first)->second;
    auto secondDict = dicts.find(second);
    auto secondBegin = secondDict->second.begin();
    auto secondEnd = secondDict->second.end();
    for (auto i = secondBegin; i != secondEnd; i++)
    {
      if (!newDictionary.contains(i->first))
      {
        newDictionary.insert(*i);
      }
    }
    if (first == newDict)
    {
      dicts.find(first)->second.clear();
      dicts.find(first)->second.insert(newDictionary.begin(), newDictionary.end());
      return;
    }
    else if (second == newDict)
    {
      dicts.find(second)->second.clear();
      dicts.find(second)->second.insert(newDictionary.begin(), newDictionary.end());
      return;
    }
    else
    {
      dicts.insert({newDict, newDictionary});
    }
  }
}
