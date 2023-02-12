#include "functions.h"
#include <limits>
namespace
{
  constexpr long long max_long_long = std::numeric_limits< long long >::max();
  constexpr long long min_long_long = std::numeric_limits< long long >::min();
  namespace
  {
    bool isOverAdd(long long first, long long second)
    {
      return first > 0 && second > 0 && second > (max_long_long - first);
    }
    bool isUnderAdd(long long first, long long second)
    {
      return first < 0 && second < 0 && first < (min_long_long - second);
    }
    bool isOverMult(long long first, long long second)
    {
      return (first > max_long_long / second) && ((first > 0 && second > 0) || (first < 0 && second < 0));
    }
    bool isUnderMult(long long first, long long second)
    {
      return (first < min_long_long / second) && ((first > 0 && second < 0) || (first < 0 && second > 0));
    }
  }
  bool isOverflowedAdd(long long first, long long second)
  {
    return isOverAdd(first, second) || isUnderAdd(first, second);
  }
  bool isOverflowedMult(long long first, long long second)
  {
    return isOverMult(first, second) || isUnderMult(first, second);
  }
}
bool dimkashelk::isPriorityOperation(char first, char second)
{
  if (first == '+' || first == '-')
  {
    return second == '*' || second == '/' || second == '%' || second == '(';
  }
  else
  {
    return second == '(';
  }
}
long long dimkashelk::getResult(long long first, long long second, char oper)
{
  if (oper == '+')
  {
    if (isOverflowedAdd(first, second))
    {
      throw std::logic_error("Overflow");
    }
    return first + second;
  }
  if (oper == '-')
  {
    if (isOverflowedAdd(first, second))
    {
      throw std::logic_error("Overflow");
    }
    return first - second;
  }
  if (oper == '*')
  {
    if (isOverflowedMult(first, second))
    {
      throw std::logic_error("Overflow");
    }
    return first * second;
  }
  if (oper == '/')
  {
    if (second == 0)
    {
      throw std::logic_error("Division by 0");
    }
    return first / second;
  }
  if (oper == '%')
  {
    if (first > 0)
    {
      return first % second;
    }
    else
    {
      return second - (-first) % second;
    }
  }
  throw std::logic_error("Not supported this operator");
}
