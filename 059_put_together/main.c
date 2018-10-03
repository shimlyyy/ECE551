#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    perror("Could not open file");
    exit(EXIT_FAILURE);
  }
  counts_t * c = createCounts();

  char ** lines = NULL;
  char * curr = NULL;
  size_t linecap;
  size_t k = 0;
  while (getline(&curr, &linecap, f) >= 0) {
    lines = realloc(lines, (k + 1) * sizeof(*lines));
    lines[k] = curr;
    curr = NULL;
    k++;
  }
  free(curr);
  char ** value = NULL;
  for (size_t i = 0; i < k; i++) {
    size_t ii = 0;
    while (lines[i][ii] != '\n') {
      ii++;
    }
    lines[i][ii] = '\0';
    value = realloc(value, (i + 1) * sizeof(*value));
    value[i] = lookupValue(kvPairs, lines[i]);
    free(lines[i]);
  }
  free(lines);
  for (size_t i = 0; i < k; i++) {
    addCount(c, value[i]);
  }
  free(value);
  if (fclose(f) != 0) {
    perror("failed to close");
    exit(EXIT_FAILURE);
  }
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc <= 2) {
    fprintf(stderr, "Invalid input\n");
    exit(EXIT_FAILURE);
  }
  kvarray_t * array = readKVs(argv[1]);
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  for (int i = 2; i < argc; i++) {
    //count from 2 to argc (call the number you count i)
    counts_t * c = countFile(argv[i], array);
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    char * fname = computeOutputFileName(argv[i]);
    FILE * output_file = fopen(fname, "w");
    //compute the output file name from argv[i] (call this outName)
    //open the file named by outName (call that f)
    printCounts(c, output_file);
    //print the counts from c into the FILE f
    if (fclose(output_file) != 0) {
      perror("failed to close");
      return EXIT_FAILURE;
    }
    //close f
    freeCounts(c);
    free(fname);
  }
  //free the memory for outName and c
  freeKVs(array);
  //free the memory for kv
  return EXIT_SUCCESS;
}
