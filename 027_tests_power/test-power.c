#include <stdio.h>
#include <stdlib.h>
unsigned power(unsigned x, unsigned y);
int run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned ans = power(x, y);
  if (ans == expected_ans) {
    return EXIT_SUCCESS;
  }
  else {
    exit(EXIT_FAILURE);
  }
}
int main(void) {
  run_check(4294967295, 1, 4294967295);
  run_check(-1, 2, 1);
  run_check(0, 0, 1);
  return EXIT_SUCCESS;
}
