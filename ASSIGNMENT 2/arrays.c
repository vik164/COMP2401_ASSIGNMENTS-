#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"

/*
  Function:  initCourseArray
  Purpose:   initialize array
       in:   collection of courses array
      out:   all of array set to NULL
   return:   nothing
*/
void initCourseArray(CourseArrayType *arr){
  arr->size = 0;
}

/*
  Function:  addCourse
  Purpose:   add course to array
   in:       course collection array
   in:       new course to add
   out:      course added to course collection array
   return:   C_OK for success, C_NOK for failure
*/
int addCourse(CourseArrayType *arr, CourseType *c){
  if(arr->size < MAX_ARR){
    arr->elements[arr->size] = c;
    ++arr->size; 
    return C_OK;
  }
  return C_NOK;
}

/*
  Function:  findCourse
  Purpose:   find course in array
   in:       course collection array
   in:       course id
   in:       course
   out:      return course if found
   return:   C_OK for success, C_NOK for failure
*/
int  findCourse(CourseArrayType *arr, int id, CourseType **c){
  for(int i=0; i<arr->size; i++){
    if(arr->elements[i]->id == id){
      *c = arr->elements[i];
      return C_OK;
    } 
  }
  *c = NULL;
  return C_NOK; 
}

//DONE//
