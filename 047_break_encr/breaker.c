#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
int in_count(FILE * f) {
  int c;
  int count = 0;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      count++;
    }
  }
  return count;
}

int find_e(FILE * f, int len) {
  char array[len];
  int c;
  int i = 0;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      array[i] = c;
      i++;
    }
  }
  int count = 0;
  int max = 0;
  char maxch;
  for (char a = 'a'; a <= 'z'; a++) {
    for (int j = 0; j < len; j++) {
      if (array[j] == a) {
        count++;
      }
    }
    if (count > max) {
      max = count;
      maxch = a;
    }
  }
  return maxch - 'e';
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
  if (argc != 2) {
    fprintf(stderr, "Usage: breaker key inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  int len = in_count(f);
  int key = find_e(f, len);
  printf("key=%d\n", key);
  breaker(f, key);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
