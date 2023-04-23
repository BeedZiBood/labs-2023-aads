#ifndef NOTATIONS_H
#define NOTATIONS_H
#include "queue.h"
#include "expressionpart.h"
namespace romanovich
{
  bool stackPopCondition(const ExpPart &q, const ExpPart &s);
  void getPostfixFromInfix(Queue< ExpPart > &queue, Stack< ExpPart > &pStack, Queue< ExpPart > &pQueue);
  void calcPostfixExpression(Queue< ExpPart > &postfixQueue, Stack< ExpPart > &stack, Stack< ExpPart > &pStack);
  Queue< ExpPart > splitLine(const std::string &string);
  long long doOperation(long long a, long long b, const operations_t &oper);
  ExpPart createFromString(const std::string &string);
}
#endif
