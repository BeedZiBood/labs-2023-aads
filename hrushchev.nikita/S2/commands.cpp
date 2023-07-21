#include "commands.hpp"
#include <string>
#include <ostream>
#include "dictionary.hpp"

using dict_t = Dictionary< size_t, std::string >;

void printDict(std::string name, Dictionary< std::string, dict_t >& dict_of_dict, std::ostream& out)
{
  try
  {
    dict_t dict = dict_of_dict.at(name);
    if (dict.empty())
    {
      out << "<EMPTY>";
      return;
    }
    out << name;
    for (auto i = dict.begin(); i != dict.end(); i++)
    {
      out << " " << i->first << " " << i->second;
    }
  }
  catch (...)
  {
    throw;
  }
}

void complementDict(std::string name, std::string first, std::string second, Dictionary< std::string, dict_t >& dict_of_dict)
{
  try
  {
    dict_t temp;
    dict_t first_dict = dict_of_dict.at(first);
    dict_t second_dict = dict_of_dict.at(second);
    for (auto i = first_dict.begin(); i != first_dict.end(); i++)
    {
      try
      {
        second_dict.at(i->first);
      }
      catch (...)
      {
        temp.insert(*i);
      }
    }
    for (auto i = second_dict.begin(); i != second_dict.end(); i++)
    {
      try
      {
        first_dict.at(i->first);
      }
      catch (...)
      {
        temp.insert(*i);
      }
    }
    dict_of_dict.push(name, temp);
  }
  catch(...)
  {
    throw;
  }
}

void intersectDict(std::string name, std::string first, std::string second, Dictionary< std::string, dict_t >& dict_of_dict)
{
  try
  {
    dict_t temp;
    dict_t first_dict = dict_of_dict.at(first);
    dict_t second_dict = dict_of_dict.at(second);
    for (auto i = first_dict.begin(); i != first_dict.end(); i++)
    {
      try
      {
        second_dict.at(i->first);
        temp.insert(*i);
      }
      catch (...)
      {
      }
    }
    dict_of_dict.push(name, temp);
  }
  catch (...)
  {
    throw;
  }
}

void unionDict(std::string name, std::string first, std::string second, Dictionary< std::string, dict_t >& dict_of_dict)
{
  try
  {
    dict_t temp;
    dict_t first_dict = dict_of_dict.at(first);
    dict_t second_dict = dict_of_dict.at(second);
    for (auto i = second_dict.begin(); i != second_dict.end(); i++)
    {
      temp.insert(*i);
    }
    for (auto i = first_dict .begin(); i != first_dict.end(); i++)
    {
      temp.insert(*i);
    }
    dict_of_dict.push(name, temp);
  }
  catch (...)
  {
    throw;
  }
}
