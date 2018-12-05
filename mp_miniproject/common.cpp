#include "common.h"
void skipSpace(std::string::iterator & it) {
  while (isspace(*it)) {
    it++;
  }
}

std::string find_str(std::string::iterator & it) {
  skipSpace(it);
  std::string target;
  while (*it != ' ') {
    if ((*it == '(') || *it == ')' || (*it == '\0')) {
      return target;
    }
    target += *it;
    it++;
  }
  return target;
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
  std::string list = "sin cos sqrt pow ln";
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
//check ();
void bracket_macth(std::string & side) {
  int left = 0;
  int right = 0;
  std::string::iterator macth = side.begin();
  while (macth != side.end()) {
    if (*macth == '(') {
      left++;
    }
    if (*macth == ')') {
      right++;
    }
    macth++;
  }
  if (right != left) {
    throw std::invalid_argument("Invalid input");
  }
}
