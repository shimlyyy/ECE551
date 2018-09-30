#include "election.h"
//include any other headers you need here...
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
state_t parseLine(const char * line) {
  //STEP 1: write me
  const char * check = line;  //define a pointer to check the format of strings
  int count = 0;
  while (*check != '\0') {  //until null-terminated
    if (*check == ':') {
      count++;  //check the number of ':'
    }
    check++;
  }
  if (count != 2) {  // if the format is wrong,output the informantion and exit
    fprintf(stderr, "input is invalid\n");
    exit(EXIT_FAILURE);
  }
  if (strchr(line, ':') - line >=
      MAX_STATE_NAME_LENGTH) {  //check whether the states'name is correct
    fprintf(stderr, "name is too long\n");
    exit(EXIT_FAILURE);
  }
  state_t state;
  size_t i = 0;
  while (line[i] != ':') {  // let  the strings of name in state.name
    state.name[i] = line[i];
    i++;
  }
  state.name[i] = '\0';  // add the null-terminated
  i++;
  state.population = 0;
  while (line[i] != ':') {
    if (line[i] < '0' || line[i] > '9') {  //check whether the population is correct, if not, exit
      fprintf(stderr, "population is not correct\n");
      exit(EXIT_FAILURE);
    }
    state.population = state.population * 10 + (line[i] - '0');  //transfer char to integer
    i++;
  }
  i++;
  state.electoralVotes = 0;
  while (line[i] != '\0') {
    if (line[i] < '0' || line[i] > '9') {  //check the votes
      fprintf(stderr, "vote is not correct\n");
      exit(EXIT_FAILURE);
    }
    state.electoralVotes = state.electoralVotes * 10 + (line[i] - '0');  //transfer char to intefer
    i++;
  }
  return state;
}

unsigned int countElectoralVotes(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 2: write me
  unsigned int totalvotes = 0;
  for (size_t i = 0; i < nStates; i++) {  //all states
    if (2 * voteCounts[i] >
        stateData[i].population) {  // if 2*votecount more than population,A obtained the votes
      totalvotes += stateData[i].electoralVotes;
    }
  }
  return totalvotes;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
  for (size_t i = 0; i < nStates; i++) {
    double t = voteCounts[i] / (double)stateData[i].population;  //get the percent of vote
    if (0.495 <= t && 0.505 >= t) {  //check whehter the state has to vote again
      printf("%s requires a recount(Candidate A has %.2f%% of the vote)\n",
             stateData[i].name,
             t * 100);
    }
  }
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me

  size_t largestindex = 0;  //index the largest percent of vote,assuming 0 is the largestindex
  double large = voteCounts[largestindex] /
                 (double)stateData[largestindex].population;  //get the percent of vote
  double current;
  for (size_t i = 1; i < nStates; i++) {
    current = voteCounts[i] / (double)stateData[i].population;
    if (current > large) {  //find the larger percent of vote
      large = current;      //if it is update the largest percent and largetindex
      largestindex = i;
    }
  }
  printf("Candidate A won %s with %.2f%% of the vote\n", stateData[largestindex].name, large * 100);
}
