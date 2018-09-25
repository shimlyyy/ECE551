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
  char str[10][12];
  int i = 0;
  while (fgets(str[i], 12, f) != NULL) {
    if (strchr(str[i], '\n') == NULL) {
      printf("line is too long");
      return EXIT_FAILURE;
    }
    i++;
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

  /*  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      fprintf(stdout, "%c", reverse[i][j]);
    }
    fprintf(stdout, "\n");
  }
  return EXIT_SUCCESS;*/
}
