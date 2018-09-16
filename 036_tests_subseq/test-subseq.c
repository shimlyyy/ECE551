#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n);
int run_check(int * array, size_t n, size_t expected_ans) {
  if (maxSeq(array, n) == expected_ans) {
    return EXIT_SUCCESS;
  }
  else {
    exit(EXIT_FAILURE);
  }
}
int main(void) {
  int array[10] = {1, 2, 1, 3, 5, 8, 2, 4, 6, 9};
  int a[1] = {4};
  int b[3] = {-1, 0, 2};
  int c[9] = {0, 1, 2, 3, 3, 4, 5, 6, 7};
  int d[8] = {4, 4, 4, 4, 4, 4, 4, 4};
  int e[7] = {1, 2, 3, 4, 5, 6, 7};
  int f[0];
  run_check(array, 10, 4);
  run_check(a, 1, 1);
  run_check(b, 3, 3);
  run_check(c, 9, 5);
  run_check(d, 8, 1);
  run_check(e, 7, 7);
  run_check(f, 0, 0);
  return EXIT_SUCCESS;
}
