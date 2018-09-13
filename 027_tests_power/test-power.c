#include <stdio.h>
#include <stdlib.h>
unsigned power(unsigned x, unsigned y);
int run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned ans = power(x, y);
  if (ans == expected_ans) {
    return 1;
  }
  else {
    exit(EXIT_FAILURE);
  }
}
int main(void) {
  unsigned x = 4294967295;
  unsigned y = 1;
  int w, z, m;
  w = run_check(4294967295, 1, 4294967295);
  x = -1;
  y = 2;
  z = run_check(-1, 2, 1);
  x = 0;
  y = 0;
  m = run_check(0, 0, 1);
  if (z + w + m == 3) {
    return EXIT_SUCCESS;
  }
}
