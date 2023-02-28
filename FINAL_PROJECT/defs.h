#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_RUNS       100
#define NUM_PIRATES     10
#define NUM_SCENARIOS    3

#define TORT_STRENGTH    5
#define TORT_ARMOUR      8
#define HARE_STRENGTH    8
#define HARE_ARMOUR      5
#define HERO_HEALTH     20
#define PIRATE_HEALTH   10
#define SWORD_STRENGTH   2

#define MAX_STR         64

typedef enum { SUCCESS, FAILURE, PART_SUCCESS, RES_UNKNOWN } ResultType;
typedef enum { FRONT, BACK } DirectionType;

typedef struct {	// Stats for one scenario, accumulated over all runs
  int numSuccess;
  int numPartSuccess;
  int numFailure;
} StatsType;

typedef struct {	// One fighter:  Tortoise, Hare, or Pirate
  int  strength;
  int  armour;
  int  health;
} FighterType;

typedef struct Node {
  FighterType  *data;
  struct Node  *next;
} NodeType;

typedef struct {	// Stores the fighting pirates for one scenario
  NodeType *head;
  NodeType *tail;
} DequeType;

typedef struct {	// Specs for one scenario of one run
  DequeType   *pirates;
  FighterType *tort;
  FighterType *hare;
  StatsType   *stats;
} RunSpecsType;

typedef struct {	// Specs for one fight of one scenario of one run
  FighterType  *hero;
  DequeType    *pirates;
  DirectionType dir;
  sem_t        *dqMutex;
} FightSpecsType;


int randm(int);		// Pseudo-random number generator function
void *threadScenarioFunc(void* runSpecs);
void *threadFightFunc(void* fight);
void initRuns(DequeType *deq[], StatsType *stats[], RunSpecsType *runSpecs[]);

void initDeque(DequeType *deq);
void initDeque2(DequeType **deq);
void initDeques(DequeType *deq[], DequeType *pirates);
void addFighterToDeque(DequeType *deq, FighterType *fighter);
void removeFighterFront(DequeType *deq, FighterType **fighter);
void removeFighterBack(DequeType *deq, FighterType **fighter);
void deepCopy(DequeType *deq, DequeType *newDeq);
void cleanupDeque(DequeType *deq);
void cleanupDeques(DequeType *deq[]);

void initFighter(int strength, int health, int armour, FighterType **fighter);
void initFightSpecsType( FighterType *hero, DequeType *pirates, DirectionType dir, sem_t *dqMutex, FightSpecsType **fightSpecs);
void generatePirates(DequeType *pirateDeque);
void theFight(FighterType *pirate, FighterType *hero);
void cleanupFighter(FighterType *hero);
void cleanupFighterSpecs(FightSpecsType *fightSpecs);

void intRunSpecs(DequeType *pirates, FighterType *tort, FighterType *hare, StatsType *stats, RunSpecsType **runSpecs);
void initStat(StatsType **stat);
void initStats(StatsType *stats[]);
void computeStats(StatsType *stats, int runs);
int computeOutcome(FighterType *tort, FighterType *hare);
void updateStats(ResultType res, StatsType *stats);
void printStats(int runs, StatsType *stats[]);
void cleanupRuns(RunSpecsType *run[]);
void cleanupStats(StatsType *stats[]);

#endif

//DONE//

