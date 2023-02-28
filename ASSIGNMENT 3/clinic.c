#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"

/*
  Function:   initClinic
   Purpose:   initializes the clinic collection
    in-out:   the clinic collection
    return:   nothing
*/
void initClinic(ClinicType *c, char *name){
  strcpy(name,"THE CARLETON PET CLINIC");
  initAnimals(&c->animals);
  initCustomers(c);
  initSchedule(&c->sch, &c->animals);
}

/*
  Function:  cleanupClinic
  Purpose:   Deallocate the dynamically allocated memory
       in:   clinic collection
      out:   dynamically allocated memory is deallocated
   return:   nothing
*/
void cleanupClinic(ClinicType *clinic){
  cleanupAnimals(&clinic->animals);
  cleanupCustomers(&clinic->customers);
  cleanupSchedule(&clinic->sch);
}

//DONE//
