// This file is for Step 2.
#include <stdio.h>
#include <stdlib.h>
// You should do
//  Step 2 (A): write seq2
int seq2(int x) {
  return (x + 1) * (x + 2) - 1;
}
//  Step 2 (B): write main to test seq2
int sumSeq2(int low, int high) {
  int sum = 0;
  if (low >= high) {
    return 0;
  }
  while (low < high) {
    sum = sum + seq2(low);
    low++;
  }
  return sum;
}

int main(void) {
  printf("seq2(%d) = %d\n", -4, seq2(-4));
  printf("seq2(%d) = %d\n", -2, seq2(-2));
  printf("seq2(%d) = %d\n", -1, seq2(-1));
  printf("seq2(%d) = %d\n", 0, seq2(0));
  printf("seq2(%d) = %d\n", 1, seq2(1));
  printf("seq2(%d) = %d\n", 14, seq2(14));
  printf("seq2(%d) = %d\n", 15, seq2(15));
  printf("sumSeq2(%d, %d) = %d\n", 0, 2, sumSeq2(0, 2));
  printf("sumSeq2(%d, %d) = %d\n", 3, 6, sumSeq2(3, 6));
  printf("sumSeq2(%d, %d) = %d\n", 9, 7, sumSeq2(9, 7));
  printf("sumSeq2(%d, %d) = %d\n", -4, 1, sumSeq2(-4, 2));
  printf("sumSeq2(%d,%d)=%d\n", 0, 0, sumSeq2(0, 0));
  return EXIT_SUCCESS;
}
//  Step 2 (C): write sumSeq2
//  Step 2 (D): add test cases to main to test sumSeq2
//
// Be sure to #include any header files you need!
