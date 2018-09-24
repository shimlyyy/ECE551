#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
void filetoarray(FILE * f, char * array) {
  int c;
  int i = 0;
  while (i < 3000 && ((c = fgetc(f)) != EOF)) {
    if (isalpha(c)) {
      array[i] = c;
      i++;
    }
  }
}

int find_e(char * array) {
  int count = 0;
  int max = 0;
  char maxchar = 'e';
  for (char a = 'a'; a <= 'z'; a++) {
    for (int j = 0; array[j] != '\0'; j++) {
      if (array[j] == a) {
        count++;
      }
    }
    if (count > max) {
      max = count;
      maxchar = a;
    }
    count = 0;
  }

  if (maxchar < 'e') {
    return maxchar - 'e' + 26;
  }
  if (maxchar == 'e') {
    return 0;
  }
  return maxchar - 'e';
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: breaker key inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  char array[30001] = {'\0'};
  filetoarray(f, array);
  int key = find_e(array);
  fprintf(stdout, "%d\n", key);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
