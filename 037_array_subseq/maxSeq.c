#include <stdlib.h>
size_t maxSeq(int * array, size_t n) {
  if (n <= 0) {
    return 0;
  }
  size_t sum = 1;
  size_t subseq = 1;
  for (int i = 0; i < n - 1; i++) {
    if (array[i] < array[i + 1]) {
      subseq++;
    }
    else {
      if (subseq > sum) {
        sum = subseq;
      }
      subseq = 1;
    }
  }
  return sum;
}
