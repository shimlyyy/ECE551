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
  while (line[i] != ':') {
    if (i == MAX_STATE_NAME_LENGTH) {
      fprintf(stderr, "name is too long. Invalid input");
      exit(EXIT_FAILURE);
    }
    state.name[i] = line[i];
    i++;
  }
  state.name[i] = '\0';
  i++;
  state.population = 0;
  while (line[i] != ':') {
    state.population = state.population * 10 + (line[i] - '0');
    i++;
  }
  i++;
  state.electoralVotes = 0;
  while (line[i] != '\0') {
    state.electoralVotes = state.electoralVotes * 10 + (line[i] - '0');
    i++;
  }
  return state;
}

unsigned int countElectoralVotes(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 2: write me
  unsigned int totalvotes = 0;
  for (size_t i = 0; i < nStates; i++) {
    if (2 * voteCounts[i] > stateData[i].population) {
      totalvotes += stateData[i].electoralVotes;
    }
  }
  return totalvotes;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
  for (size_t i = 0; i < nStates; i++) {
    double t = voteCounts[i] / (double)stateData[i].population;
    if (0.495 <= t && 0.505 >= t) {
      printf("%s requires a recount(Candidate A has %.2f%% of the vote)\n",
             stateData[i].name,
             t * 100);
    }
  }
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me

  size_t largestindex = 0;
  double large = voteCounts[largestindex] / (double)stateData[largestindex].population;
  double current;
  for (size_t i = 1; i < nStates; i++) {
    current = voteCounts[i] / (double)stateData[i].population;
    if (current > large) {
      large = current;
      largestindex = i;
    }
  }
  printf("Candidate A won %s with %.2f%% of the vote\n", stateData[largestindex].name, large * 100);
}
