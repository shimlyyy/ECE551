#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * ans = malloc(sizeof(*ans));
  ans->numValue = 0;
  ans->valueName = NULL;
  ans->unknown = 0;
  return ans;
}
counts_t * addValueToList(counts_t * c, const char * name) {
  c->numValue++;
  c->valueName = realloc(c->valueName, c->numValue * sizeof(*c->valueName));
  one_count_t * new = malloc(sizeof(*new));
  new->str = name;
  new->count = 1;
  c->valueName[c->numValue - 1] = new;
  return c;
}
int contains(one_count_t ** array, const char * str, int n) {
  int i = 0;
  while (i < n) {
    if (strcmp(array[i]->str, str) == 0) {
      array[i]->count++;
      return 0;
    }
    i++;
  }
  return 1;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->unknown++;
  }
  else {
    if (contains(c->valueName, name, c->numValue) == 1) {
      addValueToList(c, name);
    }
  }
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (int i = 0; i < c->numValue; i++) {
    printf("%s: %d\n", c->valueName[i]->str, c->valueName[i]->count);
  }
  if (c->unknown != 0) {
    printf("<unknown> : %d\n", c->unknown);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->numValue; i++) {
    free(c->valueName[i]);
  }
  free(c->valueName);
  free(c);
}
