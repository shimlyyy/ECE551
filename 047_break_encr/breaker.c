#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
int filetoarray(FILE * f) {
  int c;
  int array[26] = {0};
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      array[c - 'a']++;
    }
  }
  int largestIndex = 0;
  for (int i = 1; i < 26; i++) {
    if (array[i] > array[largestIndex]) {
      largestIndex = i;
    }
  }
  return largestIndex;
}

int findkey(int r) {
  r = r + 'a';
  if (r < 'e') {
    return r - 'e' + 26;
  }
  return r - 'e';
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: breaker key inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (argv[1] == NULL) {
    return EXIT_FAILURE;
  }
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  int e = filetoarray(f);
  int key = findkey(e);
  fprintf(stdout, "%d\n", key);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
