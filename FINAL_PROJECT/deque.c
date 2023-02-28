#include "defs.h"

/*
  Function:  initDeque
  Purpose:   initialize deque
       in:   pirate deque
      out:   deque set to NULL and initialized
   return:   nothing
*/
void initDeque(DequeType *deq){
  deq->head = NULL;
  deq->tail = NULL;
}

/*
  Function:  initDeque
  Purpose:   initialize and allocates memory for deque
       in:   deque
      out:   deque set to NULL and initialized
   return:   nothing
*/
void initDeque2(DequeType **deq){
  DequeType* d = (DequeType*) malloc(sizeof(DequeType));
  d->head = NULL;
  d->tail = NULL;
  *deq = d;
}

/*
  Function:  initDeques
  Purpose:   initialize and make collection of deque with data from pirates deque
       in:   deque collection
       in:   deque of pirates
      out:   collection of deque made
   return:   nothing
*/
void initDeques(DequeType *deq[], DequeType *pirates){
  for(int i=0;i<NUM_SCENARIOS;i++){
    initDeque2(&deq[i]);
    deepCopy(pirates, deq[i]);
  }
}

/*
  Function:  addFighterToDeque
  Purpose:   add pirate to deque
   in:       deque to add pirates to
   in:       new pirate to add
   out:      pirate added to deque
   return:   nothing
*/
void addFighterToDeque(DequeType *deq, FighterType *fighter){
   NodeType *nodeCurrent;
   NodeType *nodeNew;

   nodeCurrent = deq->head;
   
   nodeNew = malloc(sizeof(NodeType));
   nodeNew->data = fighter;
   nodeNew->next = NULL;
   
   if (nodeCurrent == NULL){ 
     deq->head = nodeNew;
     deq->tail = nodeNew;
   }
   else{
     deq->tail->next = nodeNew;
     deq->tail = nodeNew;
   }
}

/*
  Function:  removeFighterFront
  Purpose:   remove pirate from front of deque
   in:       deque to remove pirates from
   in:       pirate
   out:      pirate removed from deque
   return:   nothing
*/
void removeFighterFront(DequeType *deq, FighterType **fighter){  
  NodeType *nodeCurrent;
  nodeCurrent = deq->head;
  
  *fighter = deq->head->data;
  deq->head = nodeCurrent->next;
  free(nodeCurrent);
}

/*
  Function:  removeFighterBack
  Purpose:   remove pirate from back of deque
   in:       deque to remove pirates from
   in:       pirate
   out:      pirate removed from deque
   return:   nothing
*/
void removeFighterBack(DequeType *deq, FighterType **fighter){
  
  NodeType *nodeCurrent;
  NodeType *nodePervious;
  
  nodeCurrent = deq->head;
  nodePervious = NULL;

  while(nodeCurrent != NULL){
    if(nodeCurrent->next == NULL){
      break;
    }
    nodePervious = nodeCurrent;
    nodeCurrent = nodeCurrent->next;
  }

  *fighter = nodeCurrent->data;

  if(nodeCurrent == deq->head){
    deq->head = NULL;
  }
  else{
    nodePervious->next = NULL;
  }
  deq->tail = nodePervious;
  free(nodeCurrent);
}

/*
  Function:  deepCopy
  Purpose:   copy all data from one deque to another
   in:       deque to get data from
   in:       new deque where data will be stored
   out:      two deques with the same data
   return:   nothing
*/
void deepCopy(DequeType *deq, DequeType *newDeq){
  NodeType *nodeCurrent;
  nodeCurrent = deq->head;
  
  while(nodeCurrent != NULL){
    FighterType *f;
    initFighter(nodeCurrent->data->strength, nodeCurrent->data->armour, nodeCurrent->data->health, &f);
    addFighterToDeque(newDeq, f);
    nodeCurrent = nodeCurrent->next;
  }
}

/*
  Function:  cleanupDeques
  Purpose:   Deallocate the dynamically allocated memory
       in:   deque collection
      out:   dynamically allocated memory is deallocated
   return:   nothing
*/
void cleanupDeques(DequeType *deq[]){
  for(int i=0;i<NUM_SCENARIOS;i++){
    free(deq[i]);
  }
}

/*
  Function:  cleanupDeque
  Purpose:   Deallocate the dynamically allocated memory
       in:   deque
      out:   dynamically allocated memory is deallocated
   return:   nothing
*/
void cleanupDeque(DequeType *deq){
   NodeType *nodeCurrent;
   NodeType *nodeNext;

   nodeCurrent = deq->head;

   while (nodeCurrent != NULL) {
     nodeNext = nodeCurrent->next;
     free(nodeCurrent->data);
     free(nodeCurrent);
     nodeCurrent = nodeNext;
  }
}

//DONE//
