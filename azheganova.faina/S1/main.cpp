#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "convertfrominfixtopostfix.h"
#include "converttoinfix.h"
#include "calculate.h"
#include "queue.h"
#include "stack.h"

int main(int argc, char * argv[])
{
  if (argc > 2)
  {
    std::cout << "too much parameters";
    return 1;
  }
  std::string string;
  azheganova::Stack< std::string > result;
  if(argc == 2)
  {
    std::ifstream input(argv[1]);
    if (!input)
    {
      std::cerr << "error";
      return 1;
    }
    while (std::getline(input, string))
    {
      if (!input)
      {
        break;
      }
      if (string.empty())
      {
        continue;
      }
      azheganova::Queue< std::string > infixform = convertToInfix(string);
      azheganova::Queue< std::string > postfixform;
      azheganova::Stack< std::string > stack;
      try
      {
        convertFromInfixToPostfix(infixform, stack, postfixform);
      }
      catch (const std::exception & e)
      {
        std::cerr << e.what() << "\n";
        return 2;
      }
      azheganova::Stack< std::string > resstack;
      try
      {
        calculatePostfix(postfixform, result, resstack);
      }
      catch (const std::exception & e)
      {
        std::cerr << e.what() << "\n";
        return 2;
      }
    }
    if (!result.isEmpty())
    {
      std::cout << result.drop();
      result.pop();
      while (!result.isEmpty())
      {
        std::cout << " " << result.drop();
        result.pop();
      }
    }
  }
  else
  {
    while (std::cin)
    {
      std::getline(std::cin, string);
      if (!std::cin)
      {
        break;
      }
      if (string.empty())
      {
        continue;
      }
      azheganova::Queue< std::string > infixform = convertToInfix(string);
      azheganova::Queue< std::string > postfixform;
      azheganova::Stack< std::string > stack;
      try
      {
        convertFromInfixToPostfix(infixform, stack, postfixform);
      }
      catch (const std::exception & e)
      {
        std::cerr << e.what() << "\n";
        return 2;
      }
      azheganova::Stack< std::string > resstack;
      try
      {
        calculatePostfix(postfixform, result, resstack);
      }
      catch (const std::exception & e)
      {
        std::cerr << e.what() << "\n";
        return 2;
      }
    }
    if (!result.isEmpty())
    {
      std::cout << result.drop();
      result.pop();
      while (!result.isEmpty())
      {
        std::cout << " " << result.drop();
        result.pop();
      }
    }
  }
  std::cout << "\n";
  return 0;
}
