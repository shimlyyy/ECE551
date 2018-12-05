#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <cstdlib>
#include <iostream>
#include <map>

#include "common.h"
#include "function.h"
#include "nmrExp.h"
void freeMap(std::map<std::string, Function *> & function_map);
Expression * parsing(std::string::iterator & it,
                     std::map<std::string, Function *> & Myfunction,
                     std::vector<std::string> & paraVector);

std::string find_fname(std::string::iterator & it) {
  return find_str(it);
}

std::vector<std::string> make_vector(std::string::iterator & it) {
  std::vector<std::string> para_vector;
  while (*it != ')') {
    std::string para = find_str(it);
    skipSpace(it);
    if (!is_AllLetter(para)) {
      throw std::invalid_argument("Invalid input");
    }
    para_vector.push_back(para);
  }
  return para_vector;
}

// parseOp,three cases
Expression * parseOp(std::string::iterator & it,
                     std::map<std::string, Function *> & Myfunction,
                     std::vector<std::string> & paraVector) {
  skipSpace(it);
  std::string op = find_str(it);  //attention!!! change the position of iterator
  if (op.empty()) {
    return NULL;
  }
  // whether a valid regular op or built-in op or fname;
  if (isValidRop(op)) {
    skipSpace(it);
    Expression * lhs = parsing(it, Myfunction, paraVector);
    if (lhs == NULL) {
      return NULL;
    }
    Expression * rhs = parsing(it, Myfunction, paraVector);
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
      Expression * lhs = parsing(it, Myfunction, paraVector);
      if (lhs == NULL) {
        return NULL;
      }
      Expression * rhs = parsing(it, Myfunction, paraVector);
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
      Expression * lhs = parsing(it, Myfunction, paraVector);
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
    /////////
    std::map<std::string, Function *>::iterator it_function = Myfunction.find(op);
    Function * f = it_function->second;
    //std::string expr = f->getExpr();
    //std::vector<std::string> index = f->getVar_arr();
    std::vector<Expression *> whatIwant;
    while (*it != ')') {
      Expression * element = parsing(it, Myfunction, paraVector);
      if (element != NULL) {
        whatIwant.push_back(element);
      }
      else {
        return NULL;
      }
    }
    if (whatIwant.size() != f->getVectorSize()) {
      for (size_t i = 0; i < whatIwant.size(); i++) {
        delete whatIwant[i];
      }
      std::cerr << "paremeter is not match\n";
      return NULL;
    }
    it++;
    //construct is wrong,tired rewrite
    //now we get index string and Expression * list combine them
    /* for (size_t i = 0; i < index.size(); i++) {
      pass.insert(std::pair<std::string, Expression *>(index[i], whatIwant[i]));
      }*/
    // std::string::iterator itFirst = expr.begin();
    //parsing op's expression ,really important
    // Expression * result = parsing(itFirst, Myfunction, pass, paraVector);
    //pass.clear();  //important
    // return result;
    return new newExpression(f, whatIwant);
  }
  else {
    std::cerr << "Invalid op:" << op << "\n";
    return NULL;
  }
  return NULL;
}

Expression * parsing(std::string::iterator & it,
                     std::map<std::string, Function *> & Myfunction,
                     std::vector<std::string> & paraVector) {
  skipSpace(it);
  if (*it == '\0') {
    std::cerr << "End of line found mid expression!\n";
    return NULL;
  }
  else if (*it == '(') {
    //op // three cases: regular operator, built-in operator and function
    it++;
    return parseOp(it, Myfunction, paraVector);
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
      for (size_t i = 0; i < paraVector.size(); i++) {
        if (str == paraVector[i]) {
          return new VarExpression(str);
        }
      }
      std::cerr << "right para is not macth left para\n";
      return NULL;
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
  if (line.find("=") == std::string::npos) {
    throw std::invalid_argument("Invalid input");
  }
  size_t pos_equal = line.find('=');
  if (line.find("(") == std::string::npos) {
    throw std::invalid_argument("Invalid input");
  }
  size_t lstart_pos = line.find('(');
  if (lstart_pos > pos_equal) {
    throw std::invalid_argument("Invalid input");
  }
  std::string lside = line.substr(lstart_pos, pos_equal - lstart_pos);
  bracket_macth(lside);
  std::string rside = line.substr(pos_equal + 1);
  bracket_macth(rside);
  std::string::iterator it_lside = lside.begin();
  // findfname
  it_lside++;
  std::string fname = find_fname(it_lside);
  if (isValidFname(fname, Myfunction)) {
    std::cerr << "the function name " << fname << "has been defined\n";
    throw std::invalid_argument("Invalid input");
  }
  // make parameter vector
  // !!!maybe testcase (f),no parameter
  std::vector<std::string> paraVector;
  paraVector = make_vector(it_lside);
  if (paraVector.empty()) {  // (f ) //no parameters
    throw std::invalid_argument("Invalid input");
  }
  for (size_t i = 0; i < paraVector.size() - 1; i++) {
    for (size_t j = i + 1; j < paraVector.size(); j++) {
      if (paraVector[i] == paraVector[j]) {
        throw std::invalid_argument("Invalid input");
      }
    }
  }
  //  pasing_expression
  std::string::iterator it_rside = rside.begin();
  Expression * expr;
  // std::map<std::string, Expression *> pass;
  expr = parsing(it_rside, Myfunction, paraVector);
  if (expr == NULL) {
    throw std::invalid_argument("invalid input");
  }
  std::vector<double> valueVector;
  for (size_t i = 0; i < paraVector.size(); i++) {
    valueVector.push_back(0);
  }
  Function * f = new Function(rside, paraVector, expr, valueVector);
  //add to map
  Myfunction.insert(std::pair<std::string, Function *>(fname, f));
  std::ostringstream ss;
  ss << "defined " << fname << "(";
  for (size_t i = 0; i < paraVector.size(); i++) {
    if (i == paraVector.size() - 1) {
      ss << paraVector[i] << ")\n";
    }
    else {
      ss << paraVector[i] << " ";
    }
  }
  std::cout << ss.str();
}
void freeMap(std::map<std::string, Function *> & Myfunction) {
  std::map<std::string, Function *>::iterator it = Myfunction.begin();
  while (it != Myfunction.end()) {
    delete it->second;
    it++;
  }
}
int main(void) {
  std::string line;
  std::map<std::string, Function *> Myfunction;
  while (getline(std::cin, line)) {
    std::string::iterator it = line.begin();
    skipSpace(it);
    if (*it == '\0') {
      std::cerr << "empty string\n";
      std::cout << "-----end----\n";
      freeMap(Myfunction);
      return EXIT_FAILURE;
    }
    else {
      size_t pos = line.find(*it);
      std::string temp = line.substr(pos);  //skipspace to assure id is first
      //the temp string is what we need to split

      if (temp.find("define") == 0) {  // testcase: xydefine(f x y z) ....
        try {
          split_define(temp, Myfunction);
        }
        catch (std::exception & e) {
          std::cerr << "invalid input\n";
          std::cout << "-----end----\n";
          freeMap(Myfunction);
          return EXIT_FAILURE;
        }
      }
      else if (temp.find("test") == 0) {
        try {
          split_test(temp, Myfunction);
        }
        catch (std::exception & e) {
          std::cerr << "invalid test\n";
          std::cout << "-----end----\n";
          freeMap(Myfunction);
          return EXIT_FAILURE;
        }
      }
      else if (temp.find("numint") == 0) {
        try {
          forNumint(temp, Myfunction);
        }
        catch (std::exception & e) {
          std::cerr << "invalid numint\n";
          std::cout << "-----end----\n";
          freeMap(Myfunction);
          return EXIT_FAILURE;
        }
      }
      else if (temp.find("mcint") == 0) {
        try {
          forMcint(temp, Myfunction);
        }
        catch (std::exception & e) {
          std::cerr << "invalid mcint\n";
          std::cout << "-----end----\n";
          freeMap(Myfunction);
          return EXIT_FAILURE;
        }
      }
      else if (temp.find("max") == 0) {
        try {
          forGradient(temp, Myfunction, 1);
        }
        catch (std::exception & e) {
          std::cerr << "invalid gradient--max\n";
          std::cout << "-----end----\n";
          freeMap(Myfunction);
          return EXIT_FAILURE;
        }
      }
      else if (temp.find("min") == 0) {
        try {
          forGradient(temp, Myfunction, -1);
        }
        catch (std::exception & e) {
          std::cerr << "invalid gradient--min\n";
          std::cout << "-----end----\n";
          freeMap(Myfunction);
          return EXIT_FAILURE;
        }
      }
      else {
        std::cerr << "no such commands\n";
        std::cout << "-----end----\n";
        freeMap(Myfunction);
        return EXIT_FAILURE;
      }
    }
  }
  freeMap(Myfunction);
  return EXIT_SUCCESS;
}
