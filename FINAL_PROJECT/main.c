#include "defs.h"

/*
VIKRANT KUMAR 101195442
This program allows the user to simulate scenarios and fights between pirates and heros. Once the simulation ends, it will print the results in percentage of successful, partially successful, and  failed runs of each scenario over the number of runs.
*/

int main(int argc, char *argv[]){ 
  char str[MAX_STR];
  int runs;
  StatsType *stats[NUM_SCENARIOS];
  
  initStats(stats); 
  if(argv[1]){
    strcpy(str,argv[1]);
    sscanf(str, "%d", &runs);
  }
  else{
    runs = NUM_RUNS;
  }
  
  srand((unsigned)time(NULL));
  for(int i=0;i<runs;++i){
    DequeType pirateDeq;
    generatePirates(&pirateDeq);
    //printdeque(&pirateDeq);
    
    RunSpecsType *runSpecs[NUM_SCENARIOS];
    DequeType *deqAll[NUM_SCENARIOS];
    initDeques(deqAll, &pirateDeq);
    initRuns(deqAll,stats, runSpecs);
    
    cleanupRuns(runSpecs);
    cleanupDeque(&pirateDeq);
    cleanupDeques(deqAll);
  }
  printStats(runs, stats);
  cleanupStats(stats);
  return 0;
}

/*
  Function:  randm
  Purpose:   returns a pseudo randomly generated number, 
             in the range 0 to (max - 1), inclusively
       in:   upper end of the range of the generated number
   return:   randomly generated integer in the range [0, max-1) 
*/
int randm(int max)
{
  double r = ( (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
  return (int)(r * max);
}

/*
  Function:  threadScenarioFunc
  Purpose:   thread function for scenarios
       in:   void pointer for runspecs
   return:   nothing
*/
void *threadScenarioFunc(void* runSpecs){
  RunSpecsType *run = runSpecs;
  ResultType result;
  pthread_t f1, f2;
  FightSpecsType *fight1;
  FightSpecsType *fight2;
  sem_t mutex;
  
  if(sem_init(&mutex, 0, 1) < 0){
    printf("ERROR\n");
    exit(1);
  }
  
  initFightSpecsType(run->tort, run->pirates, FRONT, &mutex, &fight1); 
  initFightSpecsType(run->hare, run->pirates, BACK, &mutex, &fight2);
  pthread_create(&f1, NULL, threadFightFunc, fight1);
  pthread_create(&f2, NULL, threadFightFunc, fight2);
  pthread_join(f1, NULL);
  pthread_join(f2, NULL);
  
  result = computeOutcome(run->tort, run->hare);
  updateStats(result,  run->stats);
  cleanupFighterSpecs(fight1);
  cleanupFighterSpecs(fight2);
  return(0);
}

/*
  Function:  threadFightFunc
  Purpose:   thread function for fights
       in:   void pointer for fightSpecs
   return:   nothing
*/
void *threadFightFunc(void* fight){
  FightSpecsType *f = (FightSpecsType*) fight;

  FighterType *ff;
  FighterType *ff2;

  while((f->pirates->head != NULL) && (f->hero->health >= 1)){
    if(sem_wait(f->dqMutex) < 0){
      printf("ERROR: Semaphore Wait\n");
      exit(1);
    }    
    if((f->dir == FRONT) && (f->pirates->head != NULL) && (f->hero->health >= 1)){
      removeFighterFront(f->pirates, &ff);
      //printf("FRONT:  STR: %d   ARM: %d  HEALTH: %d \n", ff->strength, ff->armour, ff->health);
      theFight(ff, f->hero);
    }
    if((f->dir == BACK) && (f->pirates->head != NULL) && (f->hero->health >= 1)){
      removeFighterBack(f->pirates, &ff2);
      //printf("BACK :  STR: %d   ARM: %d  HEALTH: %d \n", ff2->strength, ff2->armour, ff2->health);     
      theFight(ff2, f->hero);
    }
    
    if(sem_post(f->dqMutex) < 0){
      printf("ERROR: Semaphore Post\n");
      exit(1);
    }
    usleep(1000);
  }
  return 0;
}


/*
  Function:  initRuns
  Purpose:   initialize everything needed for one run
       in:   deque collection
       in:   stats collection
       in:   RunsSpecs collection
   return:   nothing
*/
void initRuns(DequeType *deq[], StatsType *stats[], RunSpecsType *runSpecs[]){
  FighterType *Torhero;
  FighterType *Harhero;
  pthread_t arrOfThreads[NUM_SCENARIOS];
  
  for(int i=0;i<NUM_SCENARIOS;i++){
    arrOfThreads[i] = i;
  }
  
  int counter = 0;
  for(int x=0;x<NUM_SCENARIOS;x++){
    if(counter == 0){
      initFighter(TORT_STRENGTH + SWORD_STRENGTH, TORT_ARMOUR, HERO_HEALTH , &Torhero);
      initFighter(HARE_STRENGTH, HARE_ARMOUR , HERO_HEALTH, &Harhero);
      intRunSpecs(deq[x], Torhero, Harhero, stats[x], &runSpecs[x]);
    }
    else if(counter == 1){
      initFighter(TORT_STRENGTH, TORT_ARMOUR, HERO_HEALTH, &Torhero);
      initFighter(HARE_STRENGTH + SWORD_STRENGTH, HARE_ARMOUR, HERO_HEALTH, &Harhero);
      intRunSpecs(deq[x], Torhero, Harhero, stats[x], &runSpecs[x]);
    }
    else if(counter == 2){
      initFighter(TORT_STRENGTH, TORT_ARMOUR, HERO_HEALTH, &Torhero);
      initFighter(HARE_STRENGTH, HARE_ARMOUR, HERO_HEALTH, &Harhero);
      intRunSpecs(deq[x], Torhero, Harhero, stats[x], &runSpecs[x]);
    }
    counter++;
    if(counter == 3){
      counter = 0;
    }
    pthread_create(&arrOfThreads[x], NULL, threadScenarioFunc, runSpecs[x]);
    pthread_join(arrOfThreads[x], NULL);
  }
}

//DONE//
