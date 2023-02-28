/*
VIKRANT KUMAR - 101195442

This program allows the user to build a schedule for courses offered in fall 2021 and winter 2022 terms. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"

int main()
{
  char currTerm[MAX_STR] = "NONE SELECTED";
  char str[MAX_STR];
  int choice = -1;
  int courseId;
  
  CourseArrayType courseArray;
  ScheduleType currentSch;
  CourseType *course;
  
  if(initCourses(&courseArray) == C_NOK){
    printf("INITIALIZATION ERROR!\n");
    return 0;
  }
  clearSchedule(&currentSch);

  while (choice != 0) {

    printMenu(currTerm, &choice);
    if (choice == 0){ 
      cleanCourses(&courseArray);
      break;
    }
    
    switch(choice) {

      case 1:   // Reset current term
               clearSchedule(&currentSch);
               printf("PLease enter new term: ");
               fgets(currTerm, sizeof(currTerm), stdin);
               sscanf(currTerm, "%s", currTerm);
                            
        break;

      case 2:   // Print courses for current term
               printCourses(&courseArray,currTerm);

        break;

      case 3:   // Add course to schedule
               printf("PLease course id: ");
               fgets(str, sizeof(str), stdin);
               sscanf(str, "%d", &courseId);
              
               if(findCourse(&courseArray, courseId, &course) == C_OK){
                 if(strcmp(currTerm,course->term) == 0){
                   addToSchedule(&currentSch, course);
                 }
                 else{
                   printf("ERROR: Course not offered this term!\n");
                 }
               }
               else{
                 printf("ERROR: COURSE NOT FOUND!\n");
               }              

        break;

      case 4:   // Print schedule
                printSchedule(&currentSch, currTerm);

        break;

      case 5:   // Clear schedule
               clearSchedule(&currentSch);

        break;

      default:
        break;
    }
  }
  return 0;
}

/*
  Function:  printMenu
  Purpose:   displays the menu, reads the user's selection, 
             and returns the selection
       in:   the current term
      out:   the user's selection from the menu
   return:   nothing
*/
void printMenu(char *term, int *choice)
{
  int c = -1;
  int numOptions = 5;
  char str[MAX_STR];

  printf("\nMAIN MENU -- CURRENT TERM: %s\n", term);
  printf("  (1) Reset current term\n");
  printf("  (2) Print courses\n");
  printf("  (3) Add to schedule\n");
  printf("  (4) Print schedule\n");
  printf("  (5) Clear schedule\n");
  printf("  (0) Exit\n\n");

  printf("Please enter your selection: ");
  fgets(str, sizeof(str), stdin);
  sscanf(str, "%d", &c);

  if (c == 0) {
    *choice = c;
    return;
  }

  while (c < 0 || c > numOptions) {
    printf("Please enter your selection: ");
    fgets(str, sizeof(str), stdin);
    sscanf(str, "%d", &c);
  }

  *choice = c;
}

//DONE//
