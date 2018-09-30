#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvpair_t * getOne(char * curr) {
  char * check = curr;
  int ch = 0;
  while (*check != '\0') {
    if (*check == '=') {
      ch++;
    }
    check++;
  }
  if (ch != 1) {
    exit(EXIT_FAILURE);
  }

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
  if (fname == NULL) {
    return NULL;
  }
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
    free(curr);
    curr = NULL;
    i++;
  }
  free(curr);

  answer->numPerson = i;
  if (fclose(f) != 0) {
    perror("Failed to close the file");
    return NULL;
  }
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
    printf("key = '%s' value = '%s'\n", pairs->person[i]->key, pairs->person[i]->value);
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
