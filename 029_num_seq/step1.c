// This file is for Step 1.
#include <stdio.h>
#include <stdlib.h>
// You should do
//  Step 1 (A): write seq1
int seq1(int x) {
  return (4 * x - 3);
}
void printSeq1Range(int low, int high) {
  if (low >= high) {
    printf("\n");
  }
  else {
    while (low < high - 1) {
      printf("%d, ", seq1(low));
      low++;
    }
    printf("%d\n", seq1(low));
  }
}
//  Step 1 (B): write main to test seq1
int main(void) {
  printf("seq1(%d)=%d\n", -3, seq1(-3));
  printf("seq1(%d)=%d\n", -2, seq1(-2));
  printf("seq1(%d)=%d\n", -1, seq1(-1));
  printf("seq1(%d)=%d\n", 0, seq1(0));
  printf("seq1(%d)=%d\n", 1, seq1(1));
  printf("seq1(%d)=%d\n", 10, seq1(10));
  printf("seq1(%d)=%d\n", 11, seq1(11));
  printf("printSeq1Range(%d, %d)\n", 0, 0);
  printSeq1Range(0, 0);
  printf("printSeq1Range(%d, %d)\n", 4, 5);
  printSeq1Range(4, 5);
  printf("printSeq1Range(%d, %d)\n", -2, 6);
  printSeq1Range(-2, 6);
  printf("printSeq1Range(%d, %d)\n", 7, 3);
  printSeq1Range(7, 3);
}
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
//
// Be sure to #include any header files you need!
