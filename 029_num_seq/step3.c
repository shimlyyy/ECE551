// This file is for Step 3.
#include <stdio.h>
#include <stdlib.h>
// You should do
//  Step 3 (A): write seq3
int seq3(int x, int y) {
  return (x + 2) * y - 3 * x;
}

int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi) {
  if (xLow >= xHi || yLow >= yHi) {
    return 0;
  }
  int count = 0;
  for (int i = xLow; i < xHi; i++) {
    for (int j = yLow; j < yHi; j++) {
      if (seq3(i, j) % 2 == 0) {
        count++;
      }
    }
  }
  return count;
}
//  Step 3 (B): write main to test seq3
int main(void) {
  printf("seq3(%d, %d) = %d\n", -6, -6, seq3(-6, -6));
  printf("seq3(%d, %d) = %d\n", 7, 10, seq3(7, 10));
  printf("seq3(%d, %d) = %d\n", -5, 3, seq3(-5, 3));
  printf("seq3(%d, %d) = %d\n", 4, -2, seq3(4, -2));
  printf("seq3(%d, %d) = %d\n", 0, 0, seq3(0, 0));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         -1,
         1,
         -5,
         -4,
         countEvenInSeq3Range(-1, 1, -5, -4));
  printf(
      "countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 3, 5, 2, 4, countEvenInSeq3Range(3, 5, 2, 4));
  printf(
      "countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 0, 2, 0, 3, countEvenInSeq3Range(0, 2, 0, 3));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         -5,
         6,
         -5,
         6,
         countEvenInSeq3Range(-5, 6, -5, 6));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         2,
         -1,
         -5,
         -4,
         countEvenInSeq3Range(2, -1, -5, -4));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         -1,
         1,
         7,
         5,
         countEvenInSeq3Range(-1, 1, 7, 5));
  printf(
      "countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 0, 0, 0, 0, countEvenInSeq3Range(0, 0, 0, 0));
}
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
//
// Be sure to #include any header files you need!
