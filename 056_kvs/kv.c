#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvpair_t * getOne(char * curr) {
  int lenKey = strchr(curr, '=') - curr;
  char * array = malloc((lenKey + 1) * sizeof(*array));
  int i = 0;
  while (curr[i] != '=') {
    array[i] = curr[i];
    i++;
  }
  array[i] = '\0';
  i++;
  int lenValue = strchr(curr, '\n') - strchr(curr, '=');
  char * data = malloc((lenValue) * sizeof(*data));
  int j = 0;
  while (curr[i] != '\n') {
    data[j] = curr[i];
    i++;
    j++;
  }
  data[j] = '\0';
  kvpair_t * answer = malloc(sizeof(*answer));
  answer->key = array;
  answer->value = data;
  return answer;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    return NULL;
  }
  kvarray_t * answer = malloc(sizeof(*answer));
  char * curr = NULL;
  size_t linecap;
  int i = 0;
  answer->person = NULL;
  while (getline(&curr, &linecap, f) >= 0) {
    answer->person = realloc(answer->person, (i + 1) * sizeof(*answer->person));
    answer->person[i] = getOne(curr);
    curr = NULL;
    i++;
  }
  free(curr);
  answer->numPerson = i;
  return answer;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->numPerson; i++) {
    free(pairs->person[i]->key);
    free(pairs->person[i]->value);
    free(pairs->person[i]);
  }
  free(pairs->person);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->numPerson; i++) {
    printf("key='%s' value='%s'\n", pairs->person[i]->key, pairs->person[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (int i = 0; i < pairs->numPerson; i++) {
    if (strcmp(pairs->person[i]->key, key) == 0) {
      return pairs->person[i]->value;
    }
  }
  return NULL;
}
