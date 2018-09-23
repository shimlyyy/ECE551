#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int filetoarray(FILE * f, char * array) {
  int c;
  int i = 0;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      array[i] = c;
      i++;
    }
  }
  return i;
}

int find_e(char * array, int len) {
  int count = 0;
  int max = 0;
  char maxchar;
  for (char a = 'a'; a <= 'z'; a++) {
    for (int j = 0; j < len; j++) {
      if (array[j] == a) {
        count++;
      }
    }
    if (count > max) {
      max = count;
      maxchar = a;
    }
  }
  return maxchar - 'e';
}

void breaker(FILE * f, int key) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c -= 'a';
      c -= key;
      c %= 26;
      c += 'a';
    }
    printf("%c", c);
  }
}

int main(int argc, char ** argv) {
  if (argc != 1) {
    fprintf(stderr, "Usage: breaker key inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[0], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  char array[2000];
  int count = filetoarray(f, array);
  int key = find_e(array, count);
  printf("key=%d\n", key);
  breaker(f, key);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
