double makeFunc(std::string op, std::vector<Expression *> & Id) {
  if (fmap[op]->getsize() != Id.size()) {
    std::cerr << "should have same size for assignment"
              << "\n";

    //delete Ids
    /*   for (size_t i = 0; i < Id.size(); i++) {
      free(Id[i]);
      }*/
    exit(0);
  }
  //set value for args in function
  try {
    std::vector<double> ids_val;
    for (size_t i = 0; i < fmap[op]->getsize(); i++) {
      ids_val.push_back(Id[i]->evaluate());
    }
    fmap[op]->setvars(ids_val);
  }
  catch (std::invalid_argument) {
    std::cerr << "Invalid argument for makefunc"
              << "\n";
  }
  //?free vector?
  /*  for (size_t i = 0; i < Id.size(); i++) {
    free(Id[i]);
    }*/

  std::string defline = fmap[op]->getdefline();
  std::cout << defline << "this!"
            << "\n";
  //parse function until it's broken down to basic op
  // Expression * funcexpr = parse(defline, op);
  std::map<std::string, Function *>::iterator it = fmap.find(op);
  Function * func = it->second;
  std::cout << (parse(func->getdefline(), it->first))->evaluate();
  return parse(func->getdefline(), it->first)->evaluate();

  //return parse()
}

//return to the new function
Expression * makeExpr(std::string op, std::vector<Expression *> & Id) {
  //defined function name
  if (existFunc(op)) {
    double i = makeFunc(op, Id);
    return new NumExpression(i);
  }
  //return to operators, take two args
  else if (Id.size() == 2) {
    if (op == "+") {
      return new PlusExpression(Id[0], Id[1]);
    }
    if (op == "-") {
      return new MinusExpression(Id[0], Id[1]);
    }
    if (op == "*") {
      return new TimesExpression(Id[0], Id[1]);
    }
    if (op == "/") {
      return new DivExpression(Id[0], Id[1]);
    }
    if (op == "%") {
      return new ModExpression(Id[0], Id[1]);
    }
    if (op == "pow") {
      return new Pow(Id[0], Id[1]);
    }
  }
  //return to operator_for_one_arg, take one arg
  else if (Id.size() == 1) {
    if (op == "sin") {
      return new SinExpression(Id[0]);
    }
    if (op == "cos") {
      return new CosExpression(Id[0]);
    }
    if (op == "log") {
      return new Log(Id[0]);
    }
    if (op == "sqrt") {
      return new Sqrt(Id[0]);
    }
  }

  //unrecognizable char

  else {
    std::cerr << "can not recognize such op" << op << "*"
              << "\n";
  }
  return NULL;
}

/*else {
    std::cerr << "Impossible op string: " << op << "\n";
    for (size_t i = 0; i < Id.size(); i++) {
      free(Id[i]);
    }
    exit(0);
  }
  */

Expression * parseOp(std::string & line, std::string name) {
  if (fmap[name] == NULL) {
    std::cerr << "no function correspond to name"
              << "\n";
    return NULL;
  }

  //operator or fname
  std::string id;
  //ids represent args(num or variable) in (op args args...)
  std::vector<Expression *> ids;
  std::string temp;
  skipSpace(line);
  id = gettoken(line);  //id should be a opearator or fname now
  /*  if (fmap[name] == NULL && (existFunc(name))) {
    std::map<std::string, Function *>::iterator it = fmap.find(id);
    fmap[name] = it->second;
    }*/
  if (!isValidOp(id)) {
    std::cerr << "op is not valid: " << id << "\n";
    return NULL;
  }
  skipSpace(line);
  Expression * newexpr;
  while ((newexpr = parse(line, name)) != NULL) {
    ids.push_back(newexpr);
    skipSpace(line);
  }

  return makeExpr(id, ids);
}

Expression * parse(std::string & line, std::string name) {
  if (fmap[name] == NULL) {
    std::cerr << "no function correspond to name"
              << "\n";
    return NULL;
  }
  skipSpace(line);
  //std::cout << "in parse" << line << "\n";

  std::string token;
  //if this is empty
  if (line.empty()) {
    std::cerr << "defline empty"
              << "\n";
    return NULL;
  }
  token = gettoken(line);
  skipSpace(line);
  //if it is the begin of function
  if (token == "(") {
    return parseOp(line, name);
  }
  //end of a function , jump out of recursion
  else if (token == ")") {
    return NULL;
  }
  else {
    //num
    if (isNum(token)) {
      if (token.empty()) {
        exit(0);
      }
      return new NumExpression(stod(token));
    }

    //variable
    std::vector<std::string> var_list = fmap[name]->getvar_list();
    auto index = std::find(var_list.begin(), var_list.end(), token);
    if (index == var_list.end()) {
      //invalid token
      std::cerr << "no such variable in defined function"
                << "\n";
      return NULL;
    }
    //valid variable
    return new NumExpression(fmap[name]->returnvalue(token));
  }
}
