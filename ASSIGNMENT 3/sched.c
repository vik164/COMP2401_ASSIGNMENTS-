#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"

/*
  Function:  initSchedList
  Purpose:   initialize array
       in:   collection of schedule array
      out:   all of array set to NULL
   return:   nothing
*/
void initSchedList(ScheduleType *sched){
  sched->list.head = NULL;
}

/*
  Function:  initAppointment
  Purpose:   dynamically allocates memory
       in:   collection of animal array
       in:   appointment id 
       in:   animal id 
       in:   appointment year 
       in:   appointment month 
       in:   appointment day 
       in:   appointment hour 
       in:   appointment min 
       in:   new appointment pointee
      out:   dynamically allocates memory and initializes it for new animal
   return:   nothing
*/
int initAppointment(AnimalArrayType *animals, int id, int anId, int y, int m, int d, int h, int mn, AppointmentType **appt){
  
  AnimalType *name;
  
  if(findAnimal(animals, anId, &name) != C_OK){
    printf("\nANIMAL NOT FOUND = %d ", anId);
    return C_NOK;
  }
  if(y < 2021){
    printf("\nINVALID YEAR = %d ",y);
    return C_NOK;
  }
  else if(0 > m || m > 12){
    printf("\nINVALID MONTH = %d ",m);
    return C_NOK;
  }
  else if(0 > d || d > 31){
    printf("\nINVALID DAY = %d ",d);
    return C_NOK;
  }
  else if(9 > h || h > 15){
    printf("\nINVALID HOUR = %d ", h);
    return C_NOK;
  }
  else if(0 > mn || mn > 45 || mn%15 != 0){
    printf("\nINVALID MIN = %d ",mn);
    return C_NOK;
  }
  
  DateType* date = malloc(sizeof(DateType));
  date->year = y;
  date->month = m;
  date->day = d;
  date->tt.hour = h;
  date->tt.mins = mn;
  
  AppointmentType* app = malloc(sizeof(AppointmentType));
  app->id = id;
  app->animal = name;
  app->dt = date;
  
  app->cust = name->parent;
  
  *appt = app;

  return C_OK;

}

/*
  Function:  compareDates
  Purpose:   compare if d1 starts before d2
       in:   date 1
       in:   date 2
      out:   if d1 starts before d2
   return:   C_OK for success, C_NOK for failure
*/
int compareDates(DateType *d1, DateType *d2){
  if(d1->year < d2->year){
    return C_OK;
  }
  else if(d1->year > d2->year){
    return C_NOK;
  }
  
  if(d1->month < d2->month){
    return C_OK;
  }
  else if(d1->month > d2->month){
    return C_NOK;
  }
  
  if(d1->day < d2->day){
    return C_OK;    
  }
  else if(d1->day > d2->day){
    return C_NOK;
  }

  if(d1->tt.hour < d2->tt.hour){
    return C_OK;
  }
  else if(d1->tt.hour > d2->tt.hour){
    return C_NOK;
  }
  
  if(d1->tt.mins < d2->tt.mins){
    return C_OK;
  }
  else if(d1->tt.mins > d2->tt.mins){
    return C_NOK;
  }
}

/*
  Function:  overlapAppts
  Purpose:   compare if appointment 1 overlaps appointment 2
       in:   appointment 1
       in:   appointment 2
      out:   if appointment 1 overlaps appointment 2
   return:   C_OK for success, C_NOK for failure
*/
int overlapAppts(AppointmentType *a1, AppointmentType *a2){
  if(a1->dt->year == a2->dt->year){
    if(a1->dt->month == a2->dt->month){
      if(a1->dt->day == a2->dt->day){
        if(a1->dt->tt.hour == a2->dt->tt.hour){
    	  if(a1->dt->tt.mins == a2->dt->tt.mins){
    	    return C_NOK;
    	  }
    	  else if(a1->dt->tt.mins == 0 & a2->dt->tt.mins == 15 || a1->dt->tt.mins == 15 & a2->dt->tt.mins == 0){
    	    return C_NOK;
    	  }
    	  else if(a1->dt->tt.mins == 15 & a2->dt->tt.mins == 30 || a1->dt->tt.mins == 30 & a2->dt->tt.mins == 15){
    	    return C_NOK;
    	  }
    	  else if(a1->dt->tt.mins == 30 & a2->dt->tt.mins == 45 || a1->dt->tt.mins == 45 & a2->dt->tt.mins == 30){
    	    return C_NOK;
    	  }
    	}
    	else if(a1->dt->tt.hour - a2->dt->tt.hour == 1 || a2->dt->tt.hour - a1->dt->tt.hour == 1){
    	  if(a1->dt->tt.mins == 0 & a2->dt->tt.mins == 45 || a1->dt->tt.mins == 45 & a2->dt->tt.mins == 0){
    	    return C_NOK;
    	  }
    	}
      }
    }
  } 	  
  return C_OK;
}

/*
  Function:  addAppointment
  Purpose:   add appointment to list
   in:       schedule collection list
   in:       new appointment to add
   out:      appointment added to schedule collection list
   return:   C_OK for success, C_NOK for failure
*/
int addAppointment(ScheduleType *sched, AppointmentType *appt){
   NodeType *nodeCurrent;
   NodeType *nodePervious;
   NodeType *nodeNew;

   nodeCurrent = sched->list.head;
   nodePervious = NULL;

   while(nodeCurrent != NULL) {
     if (overlapAppts(appt, nodeCurrent->data) == C_NOK){
       printf("Appointment Overlap: %d at %d-%d-%02d @ %02d:%02d conflicts with %d at %d-%d-%02d @ %02d:%02d\n", appt->id,appt->dt->year,appt->dt->month,appt->dt->day,
       appt->dt->tt.hour, appt->dt->tt.mins,nodeCurrent->data->id,nodeCurrent->data->dt->year,nodeCurrent->data->dt->month,nodeCurrent->data->dt->day,
       nodeCurrent->data->dt->tt.hour,nodeCurrent->data->dt->tt.mins);
       free(appt->dt);
       free(appt);
       return C_NOK;
     }
     nodePervious = nodeCurrent;
     nodeCurrent = nodeCurrent->next;
   }
   
   nodeCurrent = sched->list.head;
   nodePervious = NULL;
   
   while(nodeCurrent != NULL){
     if(compareDates(appt->dt, nodeCurrent->data->dt) == C_OK && appt->id != nodeCurrent->data->id){
       break;
     }
     nodePervious = nodeCurrent;
     nodeCurrent = nodeCurrent->next;
   }
   
   nodeNew = malloc(sizeof(NodeType));
   nodeNew->data = appt;
   nodeNew->next = NULL;
   nodeNew->prev = NULL;
  
   if (nodePervious == NULL){ 
     sched->list.head = nodeNew;
   }
   else{
     nodePervious->next = nodeNew;
   }
   nodeNew->next = nodeCurrent;
   nodeNew->prev = nodePervious;
   
   if (nodeCurrent != NULL){
     nodeCurrent->prev = nodeNew;
   }
  return C_OK;
}

/*
  Function:  printSchedule
  Purpose:   Prints schedule with formating
       in:   schedule collection list
      out:   Prints schedule
   return:   nothing
*/
void printSchedule(ScheduleType *sched){
  NodeType *nodeCurrent;
  NodeType *nodePervious;
  
  nodeCurrent = sched->list.head;
  nodePervious = NULL;
  
  printf("LIST DIRECTION IN FORWARD:\n");
  while (nodeCurrent != NULL) {
    printAppointments(nodeCurrent->data);
    nodePervious = nodeCurrent;
    nodeCurrent = nodeCurrent->next;
  }

  nodeCurrent = nodePervious;

  printf("\nLIST DIRECTION IN BACKWARD:\n");
  while (nodeCurrent != NULL) {
    printAppointments(nodeCurrent->data);
    nodeCurrent = nodeCurrent->prev;
  }
}

/*
  Function:  printAppointments
  Purpose:   Prints appointments with formating
       in:   appointment
      out:   Prints appointment
   return:   nothing
*/
void printAppointments(AppointmentType *appt){
   if(appt->animal->parent == NULL){
      printf("APPOINTMENT:  %d at %d-%02d-%02d @ %02d:%02d -- %-5s   with parent NONE\n",appt->id,appt->dt->year,appt->dt->month,
    appt->dt->day,appt->dt->tt.hour, appt->dt->tt.mins,appt->animal->name);
   }
   else{
     printf("APPOINTMENT:  %d at %d-%02d-%02d @ %02d:%02d -- %-5s   with parent %s\n",appt->id,appt->dt->year,appt->dt->month,
      appt->dt->day,appt->dt->tt.hour, appt->dt->tt.mins,appt->animal->name,appt->animal->parent);
   }
}

/*
  Function:  cleanupSchedule
  Purpose:   Deallocate the dynamically allocated memory
       in:   schedule collection in array
      out:   dynamically allocated memory is deallocated
   return:   nothing
*/
void cleanupSchedule(ScheduleType *sched){
   NodeType *nodeCurrent;
   NodeType *nodeNext;

   nodeCurrent = sched->list.head;

   while (nodeCurrent != NULL) {
     nodeNext = nodeCurrent->next;
     free(nodeCurrent->data->dt);
     free(nodeCurrent->data);
     free(nodeCurrent);
     nodeCurrent = nodeNext;
  }
}

//DONE//

