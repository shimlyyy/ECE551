#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

bool myfunction(std::string i, std::string j) {
  return i < j;
}

struct myclass {
  bool operator()(std::string i, std::string j) { return (i < j); }
} myobject;

void getfile(std::istream & input) {
  std::string line;
  std::vector<std::string> s;
  while (getline(input, line)) {
    s.push_back(line);
  }
  if (s.size() > 1) {
    size_t a = s.size() / 2;
    std::sort(s.begin(), s.begin() + a);
    std::sort(s.begin() + a, s.end(), myfunction);
    std::sort(s.begin(), s.end(), myobject);
  }
  for (std::vector<std::string>::iterator it = s.begin(); it != s.end(); ++it) {
    std::cout << *it << "\n";
  }
}

int main(int argc, char * argv[]) {
  if (argc == 1) {
    getfile(std::cin);
  }

  for (int i = 1; i < argc; i++) {
    std::ifstream input(argv[i]);
    if (input) {
      getfile(input);
    }
    else {
      std::cerr << "can't open";
      return EXIT_FAILURE;
    }
    input.close();
  }
}
