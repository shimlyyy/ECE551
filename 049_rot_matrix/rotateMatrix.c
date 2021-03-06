#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage:breaker key inputFileName\n");
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
  char str[11][12];
  int i = 0;
  while (fgets(str[i], 12, f) != NULL) {
    if (i == 10) {
      fprintf(stderr, "too many lines");
      return EXIT_FAILURE;
    }
    if (strchr(str[i], '\n') == NULL) {
      fprintf(stderr, "line is too long\n");
      return EXIT_FAILURE;
    }
    if (strchr(str[i], '\n') - str[i] < 10) {
      fprintf(stderr, "line is too short\n");
      return EXIT_FAILURE;
    }
    i++;
  }
  if (i != 10) {
    fprintf(stderr, "not correct lines\n");
    return EXIT_FAILURE;
  }

  char array[10][10];
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      array[j][10 - i - 1] = str[i][j];
    }
  }
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      fprintf(stdout, "%c", array[i][j]);
    }
    fprintf(stdout, "\n");
  }

  if (fclose(f) != 0) {
    perror("Falied to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
