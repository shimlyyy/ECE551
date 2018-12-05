#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <map>

#include "common.h"
#include "nmrExp.h"

//why so many recursions,tired.
double recursive(Function * f,
                 std::vector<int> & times,
                 std::vector<double> & start,
                 std::vector<double> & temp,
                 size_t index,
                 double & step) {
  double result = 0;
  for (int i = 0; i < times[index]; i++) {
    if (i == 0) {
      double x = temp[index];
      temp[index] = x;
    }
    else {
      double x = step + temp[index];
      temp[index] = x;
    }
    if (index == times.size() - 1) {
      //only final loop can enter this if;
      f->setValue(temp);
      result += f->evaluate();
    }
    else {
      size_t next = index + 1;  //current index should not be changed!!! NO index++
      double mid = recursive(f, times, start, temp, next, step);
      result += mid;
    }
  }
  temp[index] = start[index];
  return result;
}
double integrate(Function * f, double & step, std::vector<std::pair<double, double> > & range) {
  std::vector<int> times;
  std::vector<double> start;
  for (size_t i = 0; i < range.size(); i++) {
    double data = range[i].second - range[i].first;
    double splitData = data / step;
    int time = floor(splitData);
    times.push_back(time);
    //std::cout << "times is:" << times[i] << "\n";
    double point = range[i].first + step / 2;
    start.push_back(point);
    // std::cout << "start min:" << start[i] << "\n";
  }
  //now we have parameters: start points and loop's times
  //lets start loop through recursion
  std::vector<double> temp = start;
  size_t index = 0;
  double result = recursive(f, times, start, temp, index, step);
  return result * pow(step, range.size());
}
void forNumint(std::string & line, std::map<std::string, Function *> & Myfunction) {
  std::string data = line.substr(6);
  // std::cout << "my data is:" << data << "\n";
  std::string::iterator it = data.begin();
  std::string fname = find_str(it);
  if (!isValidFname(fname, Myfunction)) {
    std::cerr << "not a valid fname\n";
    throw std::invalid_argument("invalid");
  }
  Function * f = Myfunction.find(fname)->second;
  std::string stepStr = find_str(it);
  if (!is_ValidNumber(stepStr)) {
    std::cerr << "step is invalid\n";
    throw std::invalid_argument("invalid");
  }
  std::string::size_type sz;  // alias of size_t
  double step = std::stod(stepStr, &sz);
  //std::cout << "step is" << step << "\n";
  std::vector<std::pair<double, double> > range;
  while (*it != '\0') {
    std::string start = find_str(it);
    //std::cout << "now i find start range is:" << start << "\n";
    if (!is_ValidNumber(start)) {
      std::cerr << "range is invalid\n";
      throw std::invalid_argument("invalid");
    }
    std::string::size_type sz1;  // alias of size_t
    double startNum = std::stod(start, &sz1);
    std::string end = find_str(it);
    // std::cout << "now i find end range :" << end << "\n";
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
  //ready to numint
  double result = integrate(f, step, range);
  std::cout << "result is:" << result << "\n";
}
