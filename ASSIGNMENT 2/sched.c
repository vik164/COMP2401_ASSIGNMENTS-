#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"

/*
  Function:  addToSchedule
  Purpose:   Adds two lectures to users schdedule
       in:   user's schedule
       in:   given course to add
      out:   adds course twice in schedule
   return:   C_OK for success, C_NOK for failure
*/
int  addToSchedule(ScheduleType *sched, CourseType *c){
    int d1;
    int d2;
    int slot;
   
    if(computeDaysFromDel(c->delDays, &d1, &d2) == C_OK){
      if(computeSlotFromTime(c->startTime.hour,c->startTime.mins, &slot) == C_OK){
        sched->courses[d1][slot] = c;
        sched->courses[d2][slot] = c; 
        return C_OK;
      }
      else{
        printf("ERROR: THIS TIME IS NOT OFFERED!\n");
        return C_NOK;
      }
    }
    else{
      printf("ERROR: THIS DAY IS NOT OFFERED!\n");
      return C_NOK;
    }
}

/*
  Function:  printSchedule
  Purpose:   print users schdedule
       in:   user's schedule
       in:   current term
      out:   user's schedule printed properly
   return:   nothing
*/
void printSchedule(ScheduleType *sched, char *term){
  int hr;
  int min;
  int slot = 0;
  int len;
  
  printf("\n     SCHEDULE FOR CURRENT TERM: %s\n\n", term);
  printf("----------------------------------------------------------------------------------------------- \n");
  printf("|        MON              TUE              WED              THU              FRI              |\n");
  printf("-----------------------------------------------------------------------------------------------\n");

  for(int i=0;i<NUM_SLOTS;++i){
    computeTimeFromSlot(slot,&hr,&min);
    if(i == slot){
      printf("| %02d:%02d |",hr,min);
    }
    slot++;
	
    for(int j=0;j<NUM_DAYS;++j){
      if(sched->courses[j][i] != NULL){    
        printf("%2s %c      ", sched->courses[j][i]->code,sched->courses[j][i]->section);
      }
      else{
        printf("                 ");
      } 
    }
    printf("|");
    printf("\n");
    printf("|       |");
    for(int x=0;x<NUM_DAYS;++x){
      if(sched->courses[x][i] != NULL){
        len = 11 - strlen(sched->courses[x][i]->instructor);
        printf("%s      ",sched->courses[x][i]->instructor);
        if(len > 0){
          printf("%*s",len, " ");
        }
      }
      else{
        printf("                 ");
      }
    }
    printf("|");
    printf("\n-----------------------------------------------------------------------------------------------");
    printf("\n");
  }
}

/*
  Function:  clearSchedule
  Purpose:   clear user's schedule
       in:   user's schedule
      out:   clear user's schedule by setting all to NULL
   return:   nothing
*/
void clearSchedule(ScheduleType *sched){
  for(int i=0;i<NUM_DAYS;++i){
    for(int j=0;j<NUM_SLOTS;++j){
      sched->courses[i][j] = NULL;
    }
  }
}

/*
  Function:  computeDaysFromDel
  Purpose:   to get indexes
       in:   course delivery days
       in:   day 1 index
       in:   day 2 index
      out:   the two indexes for schedule’s 2D array
   return:   C_OK for success, C_NOK for failure
*/
int  computeDaysFromDel(DeliveryDaysType dd, int *d1, int *d2){
  if(dd == C_MON_WED){
    *d1 = 0;
    *d2 = 2;
    return C_OK;
  }
  else if(dd == C_TUE_THU){
    *d1 = 1;
    *d2 = 3;
    return C_OK;
  }
  else if(dd == C_WED_FRI){
    *d1 = 2;
    *d2 = 4;
    return C_OK;
  }
  return C_NOK;
}

/*
  Function:  computeTimeFromSlot
  Purpose:   to get course start time
       in:   slot index
       in:   course start hour
       in:   course start hour
      out:   the start time of course
   return:   nothing
*/
int  computeTimeFromSlot(int slot, int *hrs, int *mins){
   if(slot == 0){
     *hrs = 8;
     *mins = 30;
   }
   else if(slot == 1){
     *hrs = 10;
     *mins = 00;
   }
   else if(slot == 2){
     *hrs = 11;
     *mins = 30;
   }
   else if(slot == 3){
     *hrs = 13;
     *mins = 00;
   }
   else if(slot == 4){
     *hrs = 14;
     *mins = 30;
   }
   else if(slot == 5){
     *hrs = 16;
     *mins = 00;
   }
}

/*
  Function:  computeSlotFromTime
  Purpose:   to get index for slot
       in:   course start hour
       in:   course start hour
       in:   slot index
      out:   the slot index for schedule’s 2D array
   return:   C_OK for success, C_NOK for failure
*/
int  computeSlotFromTime(int hrs, int mins, int *slot){

  if(hrs == 8 && mins == 30){
    *slot = 0;
    return C_OK;
  }
  else if(hrs == 10 && mins == 0){
    *slot = 1;
    return C_OK;
  }
  else if(hrs == 11 && mins == 30){
    *slot = 2;
    return C_OK;
  }
  else if(hrs == 13 && mins == 0){
    *slot = 3;
    return C_OK;
  }
  else if(hrs == 14 && mins == 30){
    *slot = 4;
    return C_OK;
  }
  else if(hrs == 16 && mins == 0){
    *slot = 5;
    return C_OK;
  }
  return C_NOK;

}

//DONE//
