#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "MathNode.hpp"
#include "Queue.hpp"
#include "Stack.hpp"
#include "StringSplitter.hpp"

struct MathSolver {
  void operator()(odintsov::MathNode& node)
  {
    processParen(node);
    processOperand(node);
    processOperator(node);
  }

  void processParen(odintsov::MathNode& paren)
  {
    if (paren.tag != odintsov::MathNode::Tag::Paren) {
      return;
    }
    if (paren.data.paren == '(') {
      opers_.push(paren);
    } else {
      sendOperatorsOver();
      if (opers_.empty()) {
        throw std::runtime_error("Parenthesis error");
      }
      odintsov::MathNode openParen = opers_.tail();
      if (openParen.tag != paren.tag || openParen.data.paren != '(') {
        throw std::runtime_error("Parenthesis error");
      }
      opers_.pop();
    }
  }

  void processOperand(odintsov::MathNode& operand)
  {
    if (operand.tag != odintsov::MathNode::Tag::Operand) {
      return;
    }
    result_.push(operand);
  }

  void processOperator(odintsov::MathNode& oper)
  {
    if (oper.tag != odintsov::MathNode::Tag::Operator) {
      return;
    }
    while (!opers_.empty() && opers_.tail().tag == oper.tag && opers_.tail().data.oper >= oper.data.oper) {
      result_.push(opers_.tail());
      opers_.pop();
    }
    opers_.push(oper);
  }

  void sendOperatorsOver()
  {
    while (!opers_.empty() && opers_.tail().tag == odintsov::MathNode::Tag::Operator) {
      result_.push(opers_.tail());
      opers_.pop();
    }
  }

  double getResult()
  {
    sendOperatorsOver();
    if (!opers_.empty()) {
      throw std::runtime_error("Syntax error");
    }
    odintsov::Stack< odintsov::MathNode > solver;
    while (!result_.empty()) {
      odintsov::MathNode node = result_.head();
      if (node.tag == odintsov::MathNode::Operator) {
        double rhs = solver.tail().data.operand;
        solver.pop();
        double lhs = solver.tail().data.operand;
        solver.pop();
        double res = node.data.oper.exec(lhs, rhs);
        solver.push(odintsov::MathNode(res));
      } else {
        solver.push(result_.head());
      }
      result_.pop();
    }
    if (solver.empty()) {
      throw std::runtime_error("Empty expression");
    }
    double res = solver.tail().data.operand;
    solver.pop();
    if (!solver.empty()) {
      throw std::runtime_error("Syntax error");
    }
    return res;
  }

 private:
  odintsov::Stack< odintsov::MathNode > opers_;
  odintsov::Queue< odintsov::MathNode > result_;
};

int main(int argc, char* argv[])
{
  std::istream* in = &std::cin;
  if (argc == 2) {
    std::ifstream inFile(argv[1]);
    if (!inFile.is_open()) {
      std::cerr << "Can't open file\n";
      return 1;
    }
    in = &inFile;
  } else if (argc != 1) {
    std::cerr << "Incorrect amount of arguments\n";
    return 1;
  }

  odintsov::Stack< double > results;
  try {
    while (in->good()) {
      MathSolver addToSolution;
      std::string exprStr;
      std::getline(*in, exprStr);
      if (!in->good()) {
        break;
      }
      if (exprStr.empty()) {
        continue;
      }
      odintsov::StringSplitter splitter(exprStr);
      while (!splitter.empty()) {
        std::string nodeStr;
        splitter >> nodeStr;
        odintsov::MathNode node(nodeStr);
        addToSolution(node);
      }
      results.push(addToSolution.getResult());
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
  if (results.empty()) {
    return 0;
  }
  std::cout << results.tail();
  results.pop();
  while (!results.empty()) {
    std::cout << ' ' << results.tail();
    results.pop();
  }
  std::cout << '\n';
}
