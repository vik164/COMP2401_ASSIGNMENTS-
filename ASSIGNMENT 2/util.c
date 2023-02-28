#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"

/*
  Function:  printCourses
  Purpose:   Prints courses with formating
       in:   courses collection in array
       in:   the current term
      out:   Prints all courses offered in current term
   return:   nothing
*/
void printCourses(CourseArrayType *arr, char *term){
  char convertedDays[MAX_STR];
  printf ("\nCourses for current term %s: \n", term);
  for(int i=0;i<arr->size;i++){
    if(strcmp(term,arr->elements[i]->term) == 0){
      convertDelDays(arr->elements[i]->delDays, convertedDays);
      printf("%-5d %-4s %-5s %-3c %-14s %-2s %02d:%02d \n",arr->elements[i]->id,arr->elements[i]->term,arr->elements[i]->code,
      arr->elements[i]->section,arr->elements[i]->instructor, convertedDays, arr->elements[i]->startTime.hour,arr->elements[i]->startTime.mins);           
    }
  }
}

/*
  Function:  cleanCourses
  Purpose:   Deallocate the dynamically allocated memory
       in:   courses collection in array
      out:   dynamically allocated memory is deallocated
   return:   nothing
*/
void cleanCourses(CourseArrayType *arr){
  for(int i=0;i<arr->size;++i){
    free(arr->elements[i]);
  }
}

/*
  Function:  convertDelDays
  Purpose:   Prints courses with formating
       in:   the course delivery days
       in:   converted string
      out:   returns corresponding string
   return:   nothing
*/
void convertDelDays(DeliveryDaysType dd, char *ddStr){
  if(dd == C_MON_WED){
    strcpy(ddStr, "MW");
  }
  else if(dd == C_TUE_THU){
    strcpy(ddStr,"TR");
  }
  else if(dd == C_WED_FRI){
    strcpy(ddStr,"WF");
  }
}

//DONE//
