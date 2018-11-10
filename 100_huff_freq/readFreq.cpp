#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>
void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  uint64_t * array = new uint64_t[257];
  for (uint64_t i = 0; i < 257; i++) {
    array[i] = 0;
  }
  int c;
  std::ifstream input(fname);
  if (input) {
    while ((c = input.get()) != EOF) {
      array[c]++;
    }
    array[256] = 1;
    input.close();
  }
  else {
    std::cerr << "can't open file\n";
    exit(EXIT_FAILURE);
  }
  return array;
}
