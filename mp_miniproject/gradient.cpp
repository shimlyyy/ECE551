#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <cstdlib>
#include <iostream>
#include <map>

#include "common.h"
#include "nmrExp.h"
std::vector<double> gradient(Function * f, std::vector<double> & temp) {
  double dis = 0.01;
  std::vector<double> gradient;
  std::vector<double> temp1 = temp;
  for (size_t i = 0; i < temp1.size(); i++) {
    f->setValue(temp1);
    double df1 = f->evaluate();
    temp1[i] += dis;
    f->setValue(temp1);
    double df2 = f->evaluate();
    double grad = (df2 - df1) / dis;
    gradient.push_back(grad);
    temp1 = temp;  //be the start value;
  }
  return gradient;
}
std::vector<double> mtpGamma(std::vector<double> & grad, double gamma) {
  std::vector<double> result;
  for (size_t i = 0; i < grad.size(); i++) {
    double temp = grad[i] * gamma;
    result.push_back(temp);
  }
  return result;
}
double averageDis(std::vector<double> & current, std::vector<double> & nextPos) {
  double result = 0;
  for (size_t i = 0; i < current.size(); i++) {
    result += pow(nextPos[i] - current[i], 2);
  }
  return sqrt(result);
}
std::vector<double> EVAgradient(Function * f,
                                double gamma,
                                double convergedDistance,
                                std::vector<double> & startPoint,
                                double steps,
                                int choice) {
  int i = 0;
  std::vector<double> current = startPoint;
  std::vector<double> nextPos(current.size(), 0);
  double distance;
  do {
    std::vector<double> grad;
    grad = gradient(f, current);
    grad = mtpGamma(grad, gamma);

    for (size_t i = 0; i < current.size(); i++) {
      nextPos[i] = current[i] + choice * grad[i];
    }
    distance = averageDis(current, nextPos);
    current = nextPos;
    i++;
  } while (distance > convergedDistance && i < steps);
  return nextPos;
}
void forGradient(std::string & line, std::map<std::string, Function *> & Myfunction, int choice) {
  std::string data = line.substr(3);
  std::string::iterator it = data.begin();
  std::string fname = find_str(it);
  if (!isValidFname(fname, Myfunction)) {
    std::cerr << "not a valid fname\n";
    throw std::invalid_argument("invalid");
  }
  Function * f = Myfunction.find(fname)->second;
  //gamma
  std::string gammaStr = find_str(it);
  if (!is_ValidNumber(gammaStr)) {
    std::cerr << "step is invalid\n";
    throw std::invalid_argument("invalid");
  }
  std::string::size_type sz1;  // alias of size_t
  double gamma = std::stod(gammaStr, &sz1);
  //convergedDistance;
  std::string coverged = find_str(it);
  if (!is_ValidNumber(coverged)) {
    std::cerr << "step is invalid\n";
    throw std::invalid_argument("invalid");
  }
  std::string::size_type sz2;  // alias of size_t
  double convergedDistance = std::stod(coverged, &sz2);
  std::vector<double> startPoint;
  for (size_t i = 0; i < f->getVectorSize(); i++) {
    if (*it == '\0') {
      std::cerr << "points are not enough\n";
      throw std::invalid_argument("invalid");
    }
    std::string point = find_str(it);
    if (!is_ValidNumber(gammaStr)) {
      std::cerr << "point is invalid\n";
      throw std::invalid_argument("invalid");
    }
    std::string::size_type sz3;
    double pointNum = std::stod(point, &sz3);
    startPoint.push_back(pointNum);
  }
  std::string stepStr = find_str(it);
  if (!is_ValidNumber(stepStr)) {
    std::cerr << "step is invalid\n";
    throw std::invalid_argument("invalid");
  }
  std::string::size_type sz4;
  double steps = std::stod(stepStr, &sz4);
  skipSpace(it);
  if (*it != '\0') {
    throw std::invalid_argument("invalid input");
  }
  //now we get all the parameters we need;
  //compute final step!
  std::vector<double> result = EVAgradient(f, gamma, convergedDistance, startPoint, steps, choice);
  std::cout << "the result is:";
  for (size_t i = 0; i < result.size(); i++) {
    std::cout << " " << result[i];
  }
  std::cout << "\n";
}
