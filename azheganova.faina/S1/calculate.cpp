#include "calculate.h"
#include <stdexcept>
#include <limits>

long long maximum = std::numeric_limits< long long >::max();
long long minimum = std::numeric_limits< long long >::min();
std::string calculateOperations(long long secondnum, long long firstnum, const std::string & element)
{
  if (element == "+")
  {
    if ((firstnum * secondnum >= 0) && (firstnum >= 0))
    {
      if (maximum - firstnum >= secondnum)
      {
        return std::to_string(firstnum + secondnum);
      }
      else
      {
        throw std::overflow_error("overflow");
      }
    }
    if ((firstnum * secondnum >= 0) && (firstnum <= 0))
    {
      if (minimum - firstnum <= secondnum)
      {
        return std::to_string(firstnum + secondnum);
      }
      else
      {
        throw std::overflow_error("overflow");
      }
    }
    else
    {
      return std::to_string(firstnum + secondnum);
    }
  }
  if (element == "-")
  {
    if ((firstnum > 0) && (minimum + firstnum > secondnum))
    {
      throw std::overflow_error("overflow");
    }
    return std::to_string(firstnum - secondnum);
  }
  if (element == "*")
  {
    if ((firstnum * secondnum < 0) && (firstnum >= 0))
    {
      if (maximum / firstnum >= secondnum)
      {
        return std::to_string(firstnum * secondnum);
      }
      else
      {
        throw std::overflow_error("overflow");
      }
    }
    if ((firstnum * secondnum >= 0) && (firstnum <= 0))
    {
      if (minimum / firstnum >= secondnum)
      {
        return std::to_string(firstnum * secondnum);
      }
      else
      {
        throw std::overflow_error("overflow");
      }
    }
    else
    {
      return std::to_string(firstnum * secondnum);
    }
  }
  if (element == "/")
  {
    if (secondnum == 0)
    {
      throw std::logic_error("division by 0");
    }
    return std::to_string(firstnum / secondnum);
  }
  if (firstnum < 0)
  {
    return std::to_string((firstnum % secondnum) + secondnum);
  }
  return std::to_string(firstnum % secondnum);
}

void calculatePostfix(q_n & postfix, s_n & answer, s_n & stack)
{
  stack.push(postfix.drop());
  postfix.pop();
  while (!postfix.isEmpty())
  {
    std::string element;
    element = postfix.drop();
    postfix.pop();
    if (isdigit(element[0]))
    {
      stack.push(element);
    }
    else
    {
      try
      {
        long long secondnum = std::stoll(stack.drop(), nullptr, 10);
        stack.pop();
        long long firstnum = std::stoll(stack.drop(), nullptr, 10);
        stack.pop();
        stack.push(calculateOperations(secondnum, firstnum, element));
      }
      catch (...)
      {
        throw std::range_error("error");
      }
    }
  }
  answer.push(stack.drop());
}
