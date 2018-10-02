#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * ans = malloc(sizeof(*ans));
  ans->numValue = 0;
  ans->valueName = NULL;
  return ans;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  c->unknown = 0;
  if (name == NULL) {
    c->unknown++;
  }
  for (int i = 0; i < c->numValue; i++) {
    if (strcmp(c->valueName[i]->str, name) == 0) {
      c->valueName[i]->count++;
    }
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (int i = 0; i < c->numValue; i++) {
    printf("%s: %d\n", c->valueName[i]->str, c->valueName[1]->count);
  }
  if (c->unknown != 0) {
    printf("<unknown> : %d\n", c->unknown);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->numValue; i++) {
    free(c->valueName[i]->str);
    free(c->valueName[i]);
  }
  free(c->valueName);
  free(c);
}
