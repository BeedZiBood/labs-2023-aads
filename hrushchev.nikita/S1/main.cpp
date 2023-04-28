#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "convertstringtoinfix.hpp"
#include "convertinfixtopostfix.hpp"
#include "calcucalepostfix.hpp"
#include "queue.hpp"
#include "stack.hpp"

int main(int argc, char* argv[])
{
  namespace hr = hrushchev;

  if (argc > 2)
  {
    std::cerr << "Error arg\n";
    return 1;
  }
  
  std::ifstream file_input;
  if(argc == 2)
  {
    std::ifstream file_input(argv[1]);
    if (!file_input)
    {
      std::cerr << "Unable to open file: " << argv[1] << "\n";
      return 1;
    }
  }
  std::istream& input = (argc == 2) ? file_input : std::cin;

  std::string line;
  hr::Stack < long long > results;
  while (std::getline(input, line))
  {
    if (!input)
    {
      break;
    }
    if (line.empty())
    {
      continue;
    }
    hr::Queue< std::string > infix = hr::convertStringToInfix(line);
    try
    {
      hr::Queue< std::string > postfix = hr::convertInfixToPostfix(infix);
      long long result = hr::calculatePostfix(postfix);
      results.push(result);
    }
    catch (const std::exception& e)
    {
      std::cerr << "Error: " << e.what() << "\n";
      return 2;
    }
  }
  if (!results.isEmpty())
  {
    std::cout << results.get();
    results.pop();
    while (!results.isEmpty())
    {
      std::cout << " " << results.get();
      results.pop();
    }
  }
  std::cout << "\n";
}

