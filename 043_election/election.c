#include "election.h"
//include any other headers you need here...
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
state_t parseLine(const char * line) {
  //STEP 1: write me
  const char * check = line;
  int count = 0;
  while (*check != '\0') {
    if (*check == ':') {
      count++;
    }
    check++;
  }
  if (count != 2) {
    fprintf(stderr, "input is invalid");
    exit(EXIT_FAILURE);
  }
  state_t state;
  size_t i = 0;
  while (*line != ':') {
    if (i == MAX_STATE_NAME_LENGTH) {
      fprintf(stderr, "name is too long. Invalid input");
      exit(EXIT_FAILURE);
    }
    state.name[i] = *line;
    i++;
    line++;
  }
  state.name[i] = '\0';
  line++;
  state.population = 0;
  while (*line != ':') {
    state.population = state.population * 10 + (*line - '0');
    line++;
  }
  line++;
  state.electoralVotes = 0;
  while (*line != '\0') {
    state.electoralVotes = state.electoralVotes * 10 + (*line - '0');
    line++;
  }
  return state;
}

unsigned int countElectoralVotes(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 2: write me
  return 0;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me
}
