#ifndef MATHEXPRPTR_H
#define MATHEXPRPTR_H

#include "mathExpression.h"
#include "number.h"
#include "operator.h"
#include "bracket.h"

#include <string>

class MathExprPtr
{
public:
  MathExprPtr();
  MathExprPtr(std::string inp);//explict
  MathExprPtr(const MathExprPtr& otherMathExprPtr) = delete;
  MathExprPtr(MathExprPtr&& otherMathExprPtr) noexcept;
  Expression* getRawPointer() const;
  ~MathExprPtr();

private:
  Expression* adress;

};

#endif
