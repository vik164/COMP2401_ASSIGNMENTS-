#include "defs.h"

/*
  Function:  intRunSpecs
  Purpose:   dynamically allocates memory
       in:   pirates deque
       in:   tortoise
       in:   hare
       in:   stats
       in:   new runSpecs pointee
      out:   dynamically allocates memory and initializes it for new runSpec
   return:   nothing
*/
void intRunSpecs(DequeType *pirates, FighterType *tort, FighterType *hare, StatsType *stats, RunSpecsType **runSpecs){
  RunSpecsType* r = (RunSpecsType*) malloc(sizeof(RunSpecsType));
  
  r->pirates = pirates;
  r->tort = tort; 
  r->hare = hare;
  r->stats = stats;
  
  *runSpecs = r;
} 

/*
  Function:  initStat
  Purpose:   dynamically allocates memory
       in:   new stats pointee
      out:   dynamically allocates memory and initializes it for new stats
   return:   nothing
*/
void initStat(StatsType **stat){
  StatsType* s = (StatsType*) malloc(sizeof(StatsType));
  
  s->numSuccess = 0;
  s->numPartSuccess = 0;
  s->numFailure = 0;
  
  *stat = s;
}

/*
  Function:  initStats
  Purpose:   initialize and make collection of stats
       in:   stats
      out:   collection of stats made
   return:   nothing
*/
void initStats(StatsType *stats[]){
  for(int j=0;j<NUM_SCENARIOS;j++){
    initStat(&stats[j]);
  }
}

/*
  Function:  updateStats
  Purpose:   updates stats based on result receive at the end of a scenario
       in:   Result of scenario
       in:   stats
      out:   updated stats 
   return:   nothing
*/
void updateStats(ResultType res, StatsType *stats){
  if(res == FAILURE){
    stats->numFailure += 1;
  }
  else if(res == PART_SUCCESS){
    stats->numPartSuccess += 1;
  }
  else if(res == SUCCESS){
    stats->numSuccess += 1;
  }
  else{
    printf("RESULT UNKNOWN\n");
  }
}

/*
  Function: computeOutcome 
  Purpose:  computes outcome of a scenario 
       in:  fighter tortoise
       in:  fighter hare    
   return:  returns the result of a scenario 
*/
int computeOutcome(FighterType *tort, FighterType *hare){
  if((tort->health <= 0) && (hare->health <= 0)){
    return FAILURE;
  }
  else if((tort->health >= 1) && (hare->health >= 1)){
    return SUCCESS;
  }
  else if((tort->health <= 0)){
    return PART_SUCCESS;
  }
  else if((hare->health <= 0)){
    return PART_SUCCESS;
  }
  else{
    return RES_UNKNOWN;
  }
}

/*
  Function:  computeStats
  Purpose:   converts stats to percentage 
       in:   StatsType
       in:   runs
      out:   computed percent stats
   return:   nothing
*/
void computeStats(StatsType *stats, int runs){
  int percentageSuc, percentagePartsuc, percentagefail;

  percentageSuc = ((double)stats->numSuccess/runs)*100;
  percentagePartsuc = ((double)stats->numPartSuccess/runs)*100;
  percentagefail = ((double)stats->numFailure/runs)*100;
  
  stats->numSuccess = percentageSuc;
  stats->numPartSuccess = percentagePartsuc;
  stats->numFailure = percentagefail;
}

/*
  Function:  printStats
  Purpose:   prints stats with formating
       in:   stats collection array
      out:   prints all stats
   return:   nothing
*/
void printStats(int runs, StatsType *stats[]){
  printf("-------------------------------------------------------------------\n");
  printf("| HERO WITH SWORD |   %%SUCCESS    |    %%PARTIAL   |    %%FAILURE   |\n");
  printf("-------------------------------------------------------------------\n");
  for(int i=0; i<NUM_SCENARIOS; i++){
    computeStats(stats[i], runs);
    if(i == 0){
      printf("|   TORTOISE      |");
    }
    else if(i == 1){
      printf("|   HARE          |");
    }
    else if(i == 2){
      printf("|   NONE          |");
    }
    
    printf("      %-3d      |       %-3d     |       %-3d     |\n", stats[i]->numSuccess, stats[i]->numPartSuccess, stats[i]->numFailure);
    printf("-------------------------------------------------------------------\n");
  }
  
  printf("\nTOTAL RUNS: %d\n", runs); 
}

/*
  Function:  cleanupRuns
  Purpose:   Deallocate the dynamically allocated memory
       in:   RunSpecsType
      out:   dynamically allocated memory is deallocated
   return:   nothing
*/
void cleanupRuns(RunSpecsType *run[]){
  for(int i=0; i<NUM_SCENARIOS; i++){
    cleanupDeque(run[i]->pirates);
    cleanupFighter(run[i]->tort);
    cleanupFighter(run[i]->hare);
    free(run[i]);
  }
}

/*
  Function:  cleanupStats
  Purpose:   Deallocate the dynamically allocated memory
       in:   StatsType array
      out:   dynamically allocated memory is deallocated
   return:   nothing
*/
void cleanupStats(StatsType *stats[]){
  for(int i=0; i<NUM_SCENARIOS; i++){
    free(stats[i]);
  }
}

//DONE//
