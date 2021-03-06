#ifndef __EXPR_H__
#define __EXPR_H__

#include <cstdlib>
#include <sstream>
#include <string>
class Expression
{
 protected:
  Expression * l;
  Expression * r;

 public:
  Expression(Expression * lhs, Expression * rhs) : l(lhs), r(rhs) {}
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression
{
 private:
  long num;

 public:
  NumExpression(long i) : Expression(NULL, NULL), num(i) {}
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
  /*private:
  Expression * l;
  Expression * r;*/

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : Expression(lhs, rhs) {}
  std::string toString() const {
    std::ostringstream ss;
    std::string res;
    ss << "(" << l->toString() << " + " << r->toString() << ")";
    res = ss.str();
    return res;
  }
  virtual ~PlusExpression() {
    delete l;
    delete r;
  }
};

class MinusExpression : public Expression
{
  /* private:
  Expression * l;
  Expression * r;*/

 public:
  MinusExpression(Expression * lhs, Expression * rhs) : Expression(lhs, rhs) {}
  std::string toString() const {
    std::ostringstream ss;
    std::string res;
    ss << "(" << l->toString() << " - " << r->toString() << ")";
    res = ss.str();
    return res;
  }
  virtual ~MinusExpression() {
    delete l;
    delete r;
  }
};

class TimesExpression : public Expression
{
  /* private:
  Expression * l;
  Expression * r;
  */
 public:
  TimesExpression(Expression * lhs, Expression * rhs) : Expression(lhs, rhs) {}
  std::string toString() const {
    std::ostringstream ss;
    std::string res;
    ss << "(" << l->toString() << " * " << r->toString() << ")";
    res = ss.str();
    return res;
  }
  virtual ~TimesExpression() {
    delete l;
    delete r;
  }
};

class DivExpression : public Expression
{
  /* private:
  Expression * l;
  Expression * r;
*/
 public:
  DivExpression(Expression * lhs, Expression * rhs) : Expression(lhs, rhs) {}
  std::string toString() const {
    std::ostringstream ss;
    std::string res;
    ss << "(" << l->toString() << " / " << r->toString() << ")";
    res = ss.str();
    return res;
  }
  virtual ~DivExpression() {
    delete l;
    delete r;
  }
};

#endif
