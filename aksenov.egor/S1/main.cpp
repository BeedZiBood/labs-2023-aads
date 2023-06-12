#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"
#include "stringToInfix.h"
#include "convertToPostfix.h"
#include "solvePostfixExpr.h"
bool isWhiteSpaceOrEmpty(const std::string &str)
{
  return str.find_first_not_of(" \n") == std::string::npos;
}
int main(int argc, char *argv[])
{
  if (argc > 2)
  {
    std::cerr << "err" << "\n";
    return 1;
  }
  std::string str = "";
  long long result = 0;
  if (argc == 1)
  {
    try
    {
      while (std::getline(std::cin, str))
      {
        if (!std::cin)
        {
          std::cerr << "input Error" << "\n";
          return 1;
        }
        if (isWhiteSpaceOrEmpty(str))
        {
          continue;
        }
        aksenov::Queue< std::string > infixQueue = aksenov::convertToInfix(str);
        aksenov::Queue< std::string > postfixQueue = aksenov::getPostfixQueue(infixQueue);
        result = aksenov::solvePostfixExpr(postfixQueue);
      }
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << "\n";
      return 1;
    }
  }
  if (argc == 2)
  {
    try
    {
      std::ifstream f(argv[1]);
      f.open(argv[1]);
      if (!f.is_open())
      {
        std::cerr << "cant open file" << "\n";
        return 2;
      }
      while (std::getline(f, str))
      {
        if (isWhiteSpaceOrEmpty(str))
        {
          continue;
        }
        aksenov::Queue< std::string > infixQueue = aksenov::convertToInfix(str);
        aksenov::Queue< std::string > postfixQueue = aksenov::getPostfixQueue(infixQueue);
        result = aksenov::solvePostfixExpr(postfixQueue);
      }
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << "\n";
      return 1;
    }
  }
  std::cout << result << "\n";
}
