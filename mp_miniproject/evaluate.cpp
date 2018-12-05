#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <map>

#include "common.h"
#include "nmrExp.h"

double evaluate(std::string::iterator & it, std::map<std::string, Function *> & Myfunction);
double evaluateOp(std::string::iterator & it, std::map<std::string, Function *> & Myfunction) {
  skipSpace(it);
  std::string op = find_str(it);
  //function name
  if (!isValidFname(op, Myfunction)) {
    throw std::invalid_argument("invalid input");
  }
  //need to make a vector
  double result;
  std::vector<double> testList;
  while (*it != ')') {
    skipSpace(it);
    if (*it == '(') {
      result = evaluate(it, Myfunction);  //if the id is (f 2 3) we need to evaluate it first
      //but how about (+ 2 3)...don't care it is not required accroding to readme
      if (*it == ')') {
        testList.push_back(result);
        it++;
        skipSpace(it);
      }
      else {
        throw std::invalid_argument("invalid input");
      }
    }
    else {  //number
      std::string str = find_str(it);
      if (!is_ValidNumber(str)) {
        throw std::invalid_argument("invalid input");
      }
      std::string::size_type sz;  // alias of size_t
      double d1 = std::stod(str, &sz);
      testList.push_back(d1);
      skipSpace(it);
    }
  }
  Function * f = Myfunction.find(op)->second;
  if (f->getVectorSize() != testList.size()) {
    throw std::invalid_argument("invalid input");
  }
  f->setValue(testList);
  return f->evaluate();
}
double evaluate(std::string::iterator & it, std::map<std::string, Function *> & Myfunction) {
  if (*it != '(') {
    throw std::invalid_argument("invalid input");
  }
  skipSpace(it);
  it++;
  return evaluateOp(it, Myfunction);
}

void split_test(std::string & line, std::map<std::string, Function *> & Myfunction) {
  //attention : test case
  if (line.find_first_of("(") == std::string::npos) {
    throw std::invalid_argument("invalid input");
  }
  size_t left_start = line.find_first_of('(');
  if (line.find_last_of(')') == std::string::npos) {
    throw std::invalid_argument("invalid input");
  }
  size_t left_end = line.find_last_of(')');
  std::string lside = line.substr(left_start, left_end - left_start + 1);
  bracket_macth(lside);
  //
  std::string rside = line.substr(left_end + 1);
  std::string::iterator check = rside.begin();
  skipSpace(check);
  std::string onlyOne = find_str(check);
  if (!is_ValidNumber(onlyOne)) {
    throw std::invalid_argument("invalid input");
  }
  if (*check != '\0') {
    throw std::invalid_argument("invalid input");
  }
  std::string::iterator it_lside = lside.begin();
  double result;
  result = evaluate(it_lside, Myfunction);

  std::string::size_type sz;  // alias of size_t
  double d1 = std::stod(rside, &sz);
  std::string::iterator output = lside.begin();
  output++;
  skipSpace(output);
  std::string fname = find_str(output);
  skipSpace(output);
  std::string substr;
  while (output != lside.end()) {
    substr += *output;
    output++;
  }
  substr = fname + "(" + substr;
  if (abs(result - d1) < 0.0000000000001) {
    std::cout << substr << "=" << d1 << "[correct]\n";
  }
  else {
    std::cout << substr << "=" << d1 << "[INCORRECT: expected " << result << "]\n";
  }
}
