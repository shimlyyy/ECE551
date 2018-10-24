#ifndef __EXPR_H__
#define __EXPR_H__

#include <cstdlib>
#include <sstream>
#include <string>
class Expression
{
 public:
  virtual std::string toString() const = 0;
  virtual long evaluate() const = 0;
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
  virtual long evaluate() const { return num; }
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
  virtual long evaluate() const { return l->evaluate() + r->evaluate(); }
  virtual ~PlusExpression() {
    delete l;
    delete r;
  };
};

class MinusExpression : public Expression
{
 private:
  Expression * l;
  Expression * r;

 public:
  MinusExpression(Expression * lhs, Expression * rhs) : l(lhs), r(rhs) {}
  std::string toString() const {
    std::ostringstream ss;
    std::string res;
    ss << "(" << l->toString() << " - " << r->toString() << ")";
    res = ss.str();
    return res;
  }
  virtual long evaluate() const { return l->evaluate() - r->evaluate(); }

  virtual ~MinusExpression() {
    delete l;
    delete r;
  }
};

class TimesExpression : public Expression
{
 private:
  Expression * l;
  Expression * r;

 public:
  TimesExpression(Expression * lhs, Expression * rhs) : l(lhs), r(rhs) {}
  std::string toString() const {
    std::ostringstream ss;
    std::string res;
    ss << "(" << l->toString() << " * " << r->toString() << ")";
    res = ss.str();
    return res;
  }
  virtual long evaluate() const { return l->evaluate() * r->evaluate(); }
  virtual ~TimesExpression() {
    delete l;
    delete r;
  }
};
class DivExpression : public Expression
{
 private:
  Expression * l;
  Expression * r;

 public:
  DivExpression(Expression * lhs, Expression * rhs) : l(lhs), r(rhs) {}
  std::string toString() const {
    std::ostringstream ss;
    std::string res;
    ss << "(" << l->toString() << " / " << r->toString() << ")";
    res = ss.str();
    return res;
  }
  virtual long evaluate() const { return l->evaluate() / r->evaluate(); }
  virtual ~DivExpression() {
    delete l;
    delete r;
  }
};

#endif
