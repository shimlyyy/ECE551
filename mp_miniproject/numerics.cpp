
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <map>

#include "nmrExp.h"
double evaluate(std::string::iterator & it, std::map<std::string, Function *> & Myfunction);
void freeMap(std::map<std::string, Function *> & function_map);
Expression * parsing(std::string::iterator & it, std::map<std::string, Function *> & Myfunction);
void skipSpace(std::string::iterator & it) {
  while (isspace(*it)) {
    it++;
  }
}
std::string find_str(std::string::iterator & it) {
  /*  std::string target;
  skipSpace(it);
  while (*it != ' ' && *it != ')') {
    target += *it;
    it++;
  }
  return target;*/
  skipSpace(it);
  std::string str;
  str.clear();
  while (*it != ' ' && *it != '\t') {
    if ((*it == '(') || (*it == '\0') || *it == ')') {
      return str;
    }
    str += *it;
    ++it;
  }
  return str;
}

std::string find_fname(std::string::iterator & it) {
  return find_str(it);
}

std::vector<std::string> make_vector(std::string::iterator & it) {
  std::vector<std::string> para_vector;
  while (*it != ')') {
    std::string para = find_str(it);
    para_vector.push_back(para);
  }
  return para_vector;
}
bool isValidRop(std::string & op) {
  std::string list = "+-*/%";
  if (list.find(op) != std::string::npos) {
    return true;
  }
  else {
    return false;
  }
}

bool isValidBop(std::string & op) {
  std::string list = "sin cos sqrt pow";
  if (list.find(op) != std::string::npos) {
    return true;
  }
  else {
    return false;
  }
}
bool isValidFname(std::string & op, std::map<std::string, Function *> MyFunction) {
  if (MyFunction.find(op) != MyFunction.end()) {
    return true;
  }
  else {
    return false;
  }
}

Expression * parseOp(std::string::iterator & it, std::map<std::string, Function *> & Myfunction) {
  skipSpace(it);
  std::string op = find_str(it);  //attention!!! change the position of iterator
  // whether a valid regular op or built-in op or fname;
  if (isValidRop(op)) {
    skipSpace(it);
    Expression * lhs = parsing(it, Myfunction);
    if (lhs == NULL) {
      return NULL;
    }
    Expression * rhs = parsing(it, Myfunction);
    if (rhs == NULL) {
      delete lhs;
      return NULL;
    }
    skipSpace(it);
    if (*it == ')') {
      it++;
      return new OP_Expression(op, lhs, rhs);
    }
    std::cerr << "Expected ) but found" << *it << "\n";
    delete lhs;
    delete rhs;
    return NULL;
  }
  else if (isValidBop(op)) {
    if (op == "pow") {
      skipSpace(it);
      Expression * lhs = parsing(it, Myfunction);
      if (lhs == NULL) {
        return NULL;
      }
      Expression * rhs = parsing(it, Myfunction);
      if (rhs == NULL) {
        delete lhs;
        return NULL;
      }
      skipSpace(it);
      if (*it == ')') {
        it++;
        return new builtOP_Expression(op, lhs, rhs);
      }
      std::cerr << "Expected ) but found" << *it << "\n";
      delete lhs;
      delete rhs;
      return NULL;
    }
    else {
      skipSpace(it);
      Expression * lhs = parsing(it, Myfunction);
      if (lhs == NULL) {
        return NULL;
      }
      skipSpace(it);
      if (*it == ')') {
        it++;
        return new builtOP_Expression(op, lhs, NULL);
      }
      std::cerr << "Expected ) but found" << *it << "\n";
      delete lhs;
      return NULL;
    }
  }
  else if (isValidFname(op, Myfunction)) {
    skipSpace(it);
    size_t sum_var = 0;
    std::vector<std::string> name;
    while (*it != ')') {
      std::string check_var = find_str(it);
      size_t num = 0;
      for (size_t i = 0; i < check_var.length(); i++) {
        if (isalpha(check_var[i])) {
          num++;
        }
      }
      if (num == check_var.length()) {
        sum_var++;
        name.push_back(check_var);
      }
      else {
        std::cerr << "variable name is not valid\n";
        return NULL;
      }
    }
    std::cout << "a valid fname\n";
    std::map<std::string, Function *>::iterator it_function = Myfunction.find(op);
    Function * f = it_function->second;
    if (sum_var == f->getVectorSize()) {
      std::cout << "size is same";
      it++;
      std::string fname_expr = f->getExpr();
      std::vector<std::string> index = f->getVar_arr();

      for (size_t i = 0; i < f->getVectorSize(); i++) {
        std::string a = index[i];
        if (a != name[i]) {
          while (fname_expr.find(a) != std::string::npos) {
            size_t begin = fname_expr.find(a);
            std::cout << "find" << a << ":" << begin << "\n";
            fname_expr.replace(begin, a.length(), name[i]);
          }
        }
      }
      std::cout << fname_expr << "\n";
      std::string::iterator it = fname_expr.begin();

      std::cout << "I really want to parsing\n";
      return parsing(it, Myfunction);
    }
    else {
      std::cerr << "number of varibles are not match\n";
      return NULL;
    }
  }
  else {
    std::cerr << "Invalid op:" << op << "\n";
    return NULL;
  }
  return NULL;
}
bool is_AllLetter(std::string & str) {
  size_t num_letter = 0;
  for (size_t i = 0; i < str.length(); i++) {
    if (isalpha(str[i])) {
      num_letter++;
    }
  }
  if (num_letter == str.length()) {
    return true;
  }
  return false;
}

bool is_ValidNumber(std::string & str) {
  size_t num_number = 0;
  for (size_t i = 0; i < str.length(); i++) {
    if (isdigit(str[i]) || str[i] == '.' || str[i] == '-' || str[i] == '+') {
      num_number++;
    }
  }
  if (num_number == str.length()) {
    return true;
  }
  return false;
}
Expression * parsing(std::string::iterator & it, std::map<std::string, Function *> & Myfunction) {
  skipSpace(it);
  if (*it == '\0') {
    std::cerr << "End of line found mid expression!\n";
    return NULL;
  }
  else if (*it == '(') {
    //op // three cases: regular operator, built-in operator and function
    it++;
    return parseOp(it, Myfunction);
  }
  else {
    //number or variable
    std::string str = find_str(it);
    if (is_ValidNumber(str)) {
      std::string::size_type sz;  // alias of size_t
      double d1 = std::stod(str, &sz);
      return new NumExpression(d1);
    }
    if (is_AllLetter(str)) {
      return new VarExpression(str);
    }
    std::cerr << "not a valid paramater\n";
    return NULL;
  }
  return NULL;
}

void split_define(std::string & line, std::map<std::string, Function *> & Myfunction) {
  if (line.find('=') == std::string::npos) {
    std::cerr << "function input is not valid\n";
    exit(EXIT_FAILURE);
  }
  //maybe testcase???
  size_t pos_equal = line.find('=');
  size_t lstart_pos = line.find('(');
  std::string lside = line.substr(lstart_pos, pos_equal - lstart_pos);
  std::string rside = line.substr(pos_equal + 1);
  std::string::iterator it_lside = lside.begin();
  // findfname
  it_lside++;
  std::string fname = find_fname(it_lside);
  if (isValidFname(fname, Myfunction)) {
    std::cerr << "the function name " << fname << "has been defined. Can not define again\n";
    return;
  }
  // make parameter vecotor
  // !!!maybe testcase (f),no parameter
  std::vector<std::string> paraVector;
  paraVector = make_vector(it_lside);
  //  pasing_expression
  std::string::iterator it_rside = rside.begin();
  Expression * expr;
  expr = parsing(it_rside, Myfunction);
  if (expr == NULL) {
    std::cerr << "Error: Invalid expression! No expression parsed." << std::endl;
    return;
  }
  std::cout << "parsed expression:" << expr->toString() << "\n";
  std::vector<double> valueVector;
  for (size_t i = 0; i < paraVector.size(); i++) {
    valueVector.push_back(0);
  }
  Function * f = new Function(rside, paraVector, expr, valueVector);
  //add to map
  Myfunction.insert(std::pair<std::string, Function *>(fname, f));
  std::cout << "defined " << lside << "\n";
}
void freeMap(std::map<std::string, Function *> & Myfunction) {
  std::map<std::string, Function *>::iterator it = Myfunction.begin();
  while (it != Myfunction.end()) {
    delete (*it).second;
    it++;
  }
}

double evaluateOp(std::string::iterator & it, std::map<std::string, Function *> & Myfunction) {
  skipSpace(it);
  std::string op = find_str(it);  //function name
  if (!isValidFname(op, Myfunction)) {
    // std::cerr << "Invalid fname:" << op << "\n";
    throw std::invalid_argument("No such key in the tree");
  }
  //need to make a vector
  std::cout << "it is a valide fname\n";
  double result;
  std::vector<double> testList;
  while (*it != ')') {
    skipSpace(it);
    if (*it == '(') {
      result = evaluate(it, Myfunction);  //if the id is (f x y) we need to evaluate it first
      if (*it == ')') {
        testList.push_back(result);
        it++;
      }
      else {
        throw std::invalid_argument("No such key in the tree");
      }
    }
    else {  //number

      std::string str = find_str(it);
      if (is_ValidNumber(str)) {
        std::string::size_type sz;  // alias of size_t
        double d1 = std::stod(str, &sz);
        testList.push_back(d1);
        std::cout << "testList:" << d1 << "\n";
        skipSpace(it);
      }
      else {
        // std::cerr << "Not a valid number:" << str << "\n";
        //  return 0;
        throw std::invalid_argument("No such key in the tree");
      }
    }
  }
  Function * f = Myfunction.find(op)->second;
  std::cout << "check size:" << testList.size();
  if (f->getVectorSize() != testList.size()) {
    // std::cerr << "length is not match"
    // << "\n";
    //return 0;
    throw std::invalid_argument("No such key in the tree");
  }
  f->setValue(testList);
  return f->evaluate();
}
double evaluate(std::string::iterator & it, std::map<std::string, Function *> & Myfunction) {
  skipSpace(it);
  it++;
  return evaluateOp(it, Myfunction);
}

void split_test(std::string & line, std::map<std::string, Function *> & Myfunction) {
  //attention : test case
  size_t left_start = line.find_first_of('(');
  size_t left_end = line.find_last_of(')');
  std::string lside = line.substr(left_start, left_end - left_start + 1);
  std::cout << "check l side:" << lside << "\n";
  std::string rside = line.substr(left_end + 1);
  std::string::iterator it_lside = lside.begin();
  double result;
  result = evaluate(it_lside, Myfunction);

  std::string::size_type sz;  // alias of size_t
  double d1 = std::stod(rside, &sz);
  if (abs(result - d1) < 0.0000000000001) {
    std::cout << lside << "=" << d1 << "[correct]\n";
  }
  else {
    std::cout << lside << "=" << d1 << "[INCORRECT: expected " << result << "]\n";
  }
}
int main(void) {
  std::string line;
  std::map<std::string, Function *> Myfunction;
  while (getline(std::cin, line)) {
    std::string::iterator it = line.begin();
    skipSpace(it);
    size_t pos = line.find(*it);
    std::string temp = line.substr(pos);  //skipspace to assure id is first
    //the temp string is what we need to split

    if (temp.find("define") == 0) {  // testcase: xydefine(f x y z) ....
      try {
        split_define(temp, Myfunction);
      }
      catch (std::exception & e) {
        std::cerr << "can not parse expression because input is invalid\n";
      }
    }
    else if (temp.find("test") == 0) {
      try {
        split_test(temp, Myfunction);
      }
      catch (std::exception & e) {
        std::cerr << "invalid test\n";
      }
    }
    else {
      std::cerr << "no such commands\n";
    }
  }
  freeMap(Myfunction);
  return EXIT_SUCCESS;
}
