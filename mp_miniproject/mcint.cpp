#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <cstdlib>
#include <iostream>
#include <map>

#include "common.h"
#include "nmrExp.h"
std::vector<double> forRandom(std::vector<std::pair<double, double> > & range) {
  std::vector<double> randomVector;
  srand((unsigned int)time(NULL));
  for (size_t i = 0; i < range.size(); i++) {
    double lower = range[i].first;
    double upper = range[i].second;
    double random = rand() / (double)RAND_MAX * (upper - lower) + lower;
    randomVector.push_back(random);
  }
  return randomVector;
}
double getRange(std::vector<std::pair<double, double> > & range) {
  double subr = 1;
  for (size_t i = 0; i < range.size(); i++) {
    double temp = range[i].second - range[i].first;
    subr *= temp;
  }
  return subr;
}
double mcint(Function * f, double & trial, std::vector<std::pair<double, double> > & range) {
  double sum = 0;
  std::vector<double> random;
  //first generate random double
  for (size_t i = 0; i < trial; i++) {
    random = forRandom(range);
    f->setValue(random);
    sum += f->evaluate();
  }
  double subr = getRange(range);
  double result;
  result = sum * subr * (1 / trial);
  return result;
}
void forMcint(std::string & line, std::map<std::string, Function *> & Myfunction) {
  std::string data = line.substr(5);
  std::string::iterator it = data.begin();
  std::string fname = find_str(it);
  if (!isValidFname(fname, Myfunction)) {
    std::cerr << "not a valid fname\n";
    throw std::invalid_argument("invalid");
  }
  Function * f = Myfunction.find(fname)->second;

  std::string trialStr = find_str(it);
  if (!is_ValidNumber(trialStr)) {
    std::cerr << "step is invalid\n";
    throw std::invalid_argument("invalid");
  }
  std::string::size_type sz;  // alias of size_t
  double trial = std::stod(trialStr, &sz);
  //
  std::vector<std::pair<double, double> > range;
  while (*it != '\0') {
    std::string start = find_str(it);
    if (!is_ValidNumber(start)) {
      std::cerr << "range is invalid\n";
      throw std::invalid_argument("invalid");
    }
    std::string::size_type sz1;  // alias of size_t
    double startNum = std::stod(start, &sz1);
    std::string end = find_str(it);
    if (!is_ValidNumber(end)) {
      std::cerr << "end range is invalid\n";
      throw std::invalid_argument("invalid");
    }
    std::string::size_type sz2;
    double endNum = std::stod(end, &sz2);
    if (endNum <= startNum) {
      throw std::invalid_argument("invalid");
    }
    std::pair<double, double> pair = std::make_pair(startNum, endNum);
    range.push_back(pair);
  }
  if (range.size() != f->getVectorSize()) {
    std::cerr << "Invalid input\n";
    throw std::invalid_argument("invalid");
  }
  //start mcint
  double result = mcint(f, trial, range);
  std::cout << "result is: " << result << "\n";
}
