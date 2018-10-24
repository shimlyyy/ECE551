#ifndef __EXPR_H__
#define __EXPR_H__

#include <cstdlib>
#include <sstream>
#include <string>
class Expression
{
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression
{
 private:
  long num;

 public:
  NumExpression(long i) : num(i) {}
  virtual std::string toString() const {
    std::stringstream ss;
    std::string res;
    ss << num;
    ss >> res;
    return res;
  }

  virtual ~NumExpression() {}
};

class PlusExpression : public Expression
{
 private:
  Expression * l;
  Expression * r;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : l(lhs), r(rhs) {}
  std::string toString() const {
    std::ostringstream ss;
    std::string res;
    ss << "(" << l->toString() << " + " << r->toString() << ")";
    res = ss.str();
    return res;
  }
  virtual ~PlusExpression(){};
};
#endif
