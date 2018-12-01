#ifndef __NMREXP_H__
#define __NMREXP_H__

#include <math.h>

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Expression
{
 public:
  virtual std::string toString() const = 0;
  virtual double evaluate(std::vector<std::string> & arr_para,
                          std::vector<double> & arr_value) const = 0;
  virtual ~Expression(){};
};

class Function : public Expression
{
 private:
  std::string expression;
  std::vector<std::string> arr_para;
  Expression * def;
  std::vector<double> arr_value;

 public:
  Function(){};
  Function(std::string & expr,
           std::vector<std::string> & str,
           Expression * d,
           std::vector<double> & value) :
      expression(expr),
      arr_para(str),
      def(d),
      arr_value(value) {}
  virtual std::string toString() const { return def->toString(); }
  double evaluate() { return def->evaluate(arr_para, arr_value); }  //to call evaluate much easiler
  virtual double evaluate(std::vector<std::string> & arr_para,
                          std::vector<double> & arr_value) const {
    return def->evaluate(arr_para, arr_value);
  }
  virtual ~Function() { delete def; }
  size_t getVectorSize() { return arr_para.size(); }
  std::vector<std::string> getVar_arr() { return arr_para; }
  void setValue(std::vector<double> & value) { arr_value = value; }
  std::string getExpr() { return expression; }
};

class OP_Expression : public Expression
{
 private:
  std::string op;
  Expression * left;
  Expression * right;

 public:
  OP_Expression(std::string & op, Expression * lhs, Expression * rhs) :
      op(op),
      left(lhs),
      right(rhs) {}
  virtual std::string toString() const {
    std::ostringstream ss;
    ss << "(" << left->toString() << op << right->toString() << ")";
    return ss.str();
  }

  virtual double evaluate(std::vector<std::string> & arr_para,
                          std::vector<double> & arr_value) const {
    if (op.compare("+") == 0) {
      return left->evaluate(arr_para, arr_value) + right->evaluate(arr_para, arr_value);
    }
    else if (op.compare("-") == 0) {
      return left->evaluate(arr_para, arr_value) - right->evaluate(arr_para, arr_value);
    }
    else if (op.compare("*") == 0) {
      return left->evaluate(arr_para, arr_value) * right->evaluate(arr_para, arr_value);
    }
    else if (op.compare("/") == 0) {
      return left->evaluate(arr_para, arr_value) / right->evaluate(arr_para, arr_value);
    }
    else {
      return fmod(left->evaluate(arr_para, arr_value), right->evaluate(arr_para, arr_value));
    }
  }

  virtual ~OP_Expression() {
    delete left;
    delete right;
  }
};

class builtOP_Expression : public Expression
{
 private:
  std::string op;
  Expression * left;
  Expression * right;

 public:
  builtOP_Expression(std::string & op, Expression * lhs, Expression * rhs) :
      op(op),
      left(lhs),
      right(rhs) {}
  virtual std::string toString() const {
    std::ostringstream ss;
    if (op.compare("sin") == 0) {
      ss << "(" << op << left->toString() << ")";
      return ss.str();
    }
    else if (op.compare("cos") == 0) {
      ss << "(" << op << left->toString() << ")";
      return ss.str();
    }
    else if (op.compare("sqrt") == 0) {
      ss << "(" << op << left->toString() << ")";
      return ss.str();
    }
    else if (op.compare("ln") == 0) {
      ss << "(" << op << left->toString() << ")";
      return ss.str();
    }
    else if (op.compare("pow") == 0) {
      ss << "(" << op << "(" << left->toString() << "," << right->toString() << ")"
         << ")";  //if input has only one para. test case
      return ss.str();
    }
    else {
      std::cerr << "Impossible op char: " << op << "\n";
      abort();
    }
  }

  virtual double evaluate(std::vector<std::string> & arr_para,
                          std::vector<double> & arr_value) const {
    if (op.compare("sin") == 0) {
      return sin(left->evaluate(arr_para, arr_value));
    }
    else if (op.compare("cos") == 0) {
      return cos(left->evaluate(arr_para, arr_value));
    }
    else if (op.compare("sqrt") == 0) {
      return sqrt(left->evaluate(arr_para, arr_value));
    }
    else if (op.compare("ln") == 0) {
      return log(left->evaluate(arr_para, arr_value));
    }
    else {
      return pow(left->evaluate(arr_para, arr_value), right->evaluate(arr_para, arr_value));
    }
  }
  virtual ~builtOP_Expression() {
    delete left;
    delete right;
  }
};

class NumExpression : public Expression  //basic class, represent the num parameter
{
 private:
  double num;
  std::vector<std::string> arr_para;
  std::vector<double> arr_value;

 public:
  NumExpression(double i) : num(i) {}
  NumExpression(std::vector<std::string> & arr, std::vector<double> & value) :
      arr_para(arr),
      arr_value(value) {}
  virtual std::string toString() const {
    std::ostringstream ss;
    ss << num;
    return ss.str();
  }

  virtual double evaluate(std::vector<std::string> & arr, std::vector<double> & value) const {
    NumExpression(
        arr,
        value);  //actually, it has no meaning...but if I don't write it, unused parameters
                 //So I do not know how to handle it more properly..
    return num;
  }

  virtual ~NumExpression() {}
};

class VarExpression : public Expression  //basic class variable class
{
 private:
  std::string var;

 public:
  VarExpression(std::string & var) : var(var) {}
  virtual std::string toString() const { return var; }
  virtual double evaluate(std::vector<std::string> & arr_para,
                          std::vector<double> & arr_value) const {
    double value;
    for (size_t i = 0; i < arr_para.size(); i++) {
      if (arr_para[i] == var) {  //return value according to the string in VarExpression
        value = arr_value[i];
      }
    }
    return value;
  }
  virtual ~VarExpression() {}
};

#endif
