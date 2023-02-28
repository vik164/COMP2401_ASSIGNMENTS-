#include "defs.h"

/*
  Function:  initFighter
  Purpose:   dynamically allocates memory
       in:   fighter strength
       in:   fighter armour
       in:   fighter health
       in:   new fighter pointee
      out:   dynamically allocates memory and initializes a fighter
   return:   nothing
*/
void initFighter(int strength, int armour, int health, FighterType **fighter){
  FighterType* f = (FighterType*) malloc(sizeof(FighterType));
  
  f->strength = strength;
  f->health = health;
  f->armour = armour;
  
  *fighter = f;
}

/*
  Function:  initFightSpecsType
  Purpose:   dynamically allocates memory
       in:   fighter
       in:   deque
       in:   direction
       in:   mutex
       in:   new fighterSpecs pointee
      out:   dynamically allocates memory and initializes a fighterSpecs
   return:   nothing
*/
void initFightSpecsType( FighterType *hero, DequeType *pirates, DirectionType dir, sem_t *dqMutex, FightSpecsType **fightSpecs){
  FightSpecsType* fs = (FightSpecsType*) malloc(sizeof(FightSpecsType));
  
  fs->hero = hero;
  fs->pirates = pirates; 
  fs->dir = dir;
  fs->dqMutex = dqMutex;
  
  *fightSpecs = fs;
}

/*
  Function:  generatePirates
  Purpose:   generate random pirates
       in:   collection of pirate deque
      out:   random pirates stroes in deque
   return:   nothing
*/
void generatePirates(DequeType *pirateDeque){
  FighterType *fighter;
  int pirateStr = 0, pirateArm = 0;
  
  initDeque(pirateDeque);
  
  for(int i=0; i<NUM_PIRATES; ++i){
    pirateStr = randm(5)+5;
    pirateArm = randm(4)+1;
    initFighter(pirateStr, pirateArm, PIRATE_HEALTH, &fighter);
    addFighterToDeque(pirateDeque, fighter);
  }
}

/*
  Function:  theFight
  Purpose:   allow the pirate and hero to fight
       in:   pirate
       in:   hero
      out:   death of one of the fighters
   return:   nothing
*/
void theFight(FighterType *pirate, FighterType *hero){
  int pirStr = 0;
  int damage = 0;
  int damagePirate = 0;
 
  while(1){
    damagePirate = (hero->strength - pirate->armour);
    if(damagePirate > 0){
      pirate->health = pirate->health - damagePirate;
    }
    if(pirate->health <= 0){
      if(hero->health < 20){
        hero->health = hero->health + 3;
      }
      if(hero->health >= 21){
        hero->health = 20;
      }
      break;
    }
    
    pirStr = randm(pirate->strength - 1);
    damage = (pirate->strength + pirStr) - hero->armour;
    if(damage > 0){
      hero->health = hero->health - damage;
    }
    
    if(hero->health <= 0){
      break; 
    }
  }
  cleanupFighter(pirate);
}

/*
  Function:  cleanupFighter
  Purpose:   Deallocate the dynamically allocated memory
       in:   fighter
      out:   dynamically allocated memory is deallocated
   return:   nothing
*/
void cleanupFighter(FighterType *hero){
  free(hero);
}

/*
  Function:  cleanupFighterSpecs
  Purpose:   Deallocate the dynamically allocated memory
       in:   fighterSpecsType
      out:   dynamically allocated memory is deallocated
   return:   nothing
*/
void cleanupFighterSpecs(FightSpecsType *fightSpecs){
  free(fightSpecs);
}

//DONE//
