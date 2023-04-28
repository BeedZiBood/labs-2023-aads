#include "convertinfixtopostfix.hpp"
#include <string>
#include <stdexcept>
#include "queue.hpp"
#include "stack.hpp"

namespace hr = hrushchev;

bool isHighPriorOperator(std::string op)
{
  return (op == "*") || (op == "/") || (op == "%");
}

bool isLowPriorOperator(std::string op)
{
  return  (op == "+") || (op == "-");
}

bool isOperator(std::string op)
{
  return isLowPriorOperator(op) || isHighPriorOperator(op);
}

hr::Queue< std::string > hr::convertInfixToPostfix(hr::Queue< std::string >& infixQueue)
{
  hr::Queue< std::string > postfixQueue;
  hr::Stack< std::string > stack;
  while (!infixQueue.isEmpty())
  {
    std::string token = infixQueue.get();
    infixQueue.pop();
    if (std::isdigit(token[0]))
    {
      postfixQueue.push(token);
    }
    else if (isLowPriorOperator(token))
    {
      while (!stack.isEmpty() && isOperator(stack.get()))
      {
        postfixQueue.push(stack.get());
        stack.pop();
      }
      stack.push(token);
    }
    else if (isHighPriorOperator(token))
    {
      while (!stack.isEmpty() && isHighPriorOperator(stack.get()))
      {
        postfixQueue.push(stack.get());
        stack.pop();
      }
      stack.push(token);
    }
    else if (token == "(")
    {
      stack.push(token);
    }
    else if (token == ")")
    {
      while (!stack.isEmpty() && stack.get() != "(")
      {
        postfixQueue.push(stack.get());
        stack.pop();
      }
      stack.pop();
    }
    else
    {
      throw std::logic_error("Invalid token");
    }
  }
  while (!stack.isEmpty())
  {
    postfixQueue.push(stack.get());
    stack.pop();
  }
  return postfixQueue;
}

