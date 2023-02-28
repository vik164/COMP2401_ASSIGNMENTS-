/*
VIKRANT KUMAR 101195442

This program allows the clinic manage and make new appointments schedule for there pets. 
*/

#include <stdio.h>
#include "defs.h"

int main()
{
  int  choice = -1;
  char str[MAX_STR];
  int anId,y,m,d,h,min;
  int AppId = 7020;
  char nameOfClinic;
 
  ClinicType clinics;
  AppointmentType *appt;
  
  initClinic(&clinics, &nameOfClinic);
  printf("\n%s\n\n", &nameOfClinic);

  while (choice != 0) {

    printMenu(&choice);
    if (choice == 0){
      cleanupClinic(&clinics);
      break;
    }

    switch(choice) {
      case 1:   // Create appointment
               printf("PLease course id: ");
               fgets(str, sizeof(str), stdin);
               sscanf(str, "%d", &anId); 
               
               printf("PLease year month day hour min: ");
               fgets(str, sizeof(str), stdin);
               sscanf(str, "%d %d %d %d %d", &y,&m,&d,&h,&min); 
               
               if (initAppointment(&clinics.animals, AppId, anId, y, m, d, h, min, &appt) == C_OK){
    	         addAppointment(&clinics.sch, appt);
    	         ++AppId;
    	       }
    	       else{
    	         printf("--> ERROR\n");
    	       }

        break;

      case 2:   // Print schedule
               printSchedule(&clinics.sch);

        break;

      case 3:   // Print animals
               printAnimals(&clinics.animals);

        break;

      case 4:   // Print customers
               printCustomers(&clinics.customers);

        break;

      default:
        printf("ERROR:  invalid option\n");
    }
  }


  return 0;
}
/*
  Function:  printMenu
  Purpose:   displays the menu and reads the users selection, 
             and returns the selection
       in:   choice
      out:   the user's selection from the menu
   return:   nothing
*/
void printMenu(int *choice)
{
  int c = -1;
  int numOptions = 4;
  char str[MAX_STR];

  printf("\nMAIN MENU\n");
  printf("  (1) Create appointment\n");
  printf("  (2) Print schedule\n");
  printf("  (3) Print animals\n");
  printf("  (4) Print customers\n");
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
