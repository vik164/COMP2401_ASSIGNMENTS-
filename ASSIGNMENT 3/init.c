#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"

/*
  Function:  initAnimals
  Purpose:   initializes the animal collection
   in-out:   the primary animal collection
   return:   nothing
*/
void initAnimals(AnimalArrayType *arr)
{
  
  AnimalType *a;
  
  initAnimalArray(arr);
  printf("Initialization of Animals: \n");
  initAnimal(1008, C_DOG, "Lily", "F", 1, 6, &a);
  addAnimal(arr, a);
  initAnimal(1001, C_DOG, "Betsy", "F", 5, 0, &a);
  addAnimal(arr, a);
  initAnimal(1002, C_DOG, "Killer", "F", 3, 5, &a);
  addAnimal(arr, a);
  initAnimal(1004, C_DOG, "Fluffy", "M", 2, 7, &a);
  addAnimal(arr, a);
  initAnimal(1013, C_CAT, "Lady", "F", 11, 0, &a);
  addAnimal(arr, a);
  initAnimal(1029, C_SPEC_OTHER, "Pecorino", "M", 0, 3, &a);
  addAnimal(arr, a);
  initAnimal(1007, C_DOG, "Leon", "M", 4, 0, &a);
  addAnimal(arr, a);
  initAnimal(1027, C_SPEC_OTHER, "Quasar", "M", 1, 4, &a);
  addAnimal(arr, a);
  initAnimal(1016, C_CAT, "Shadow", "M", 5, 2, &a);
  addAnimal(arr, a);
  initAnimal(1017, C_CAT, "Luka", "M", 7, 0, &a);
  addAnimal(arr, a);
  initAnimal(1018, C_CAT, "Fiona", "F", 8, 0, &a);
  addAnimal(arr, a);
  initAnimal(1021, C_CAT, "Ruby", "F", 5, 0, &a);
  addAnimal(arr, a);
  initAnimal(1023, C_SPEC_OTHER, "Ziggy", "F", 3, 8, &a);
  addAnimal(arr, a);
  initAnimal(1024, C_SPEC_OTHER, "Quark", "M", 9, 0, &a);
  addAnimal(arr, a);
  initAnimal(1032, C_SPEC_OTHER, "Gruyere", "M", 0, 3, &a);
  addAnimal(arr, a);
  initAnimal(1033, C_SPEC_OTHER, "Limburger", "M", 0, 3, &a);
  addAnimal(arr, a);
  printf("...DONE \n\n");
}

/*
  Function:   initCustomers
   Purpose:   initializes the customer collection
    in-out:   the clinic collection
    return:   nothing
*/
void initCustomers(ClinicType *clinic)
{
  CustomerArrayType *arr = &clinic->customers;
  CustomerType *c;
  
  initCustomerArray(arr);
  printf("Initialization of Customers: \n");
  initCustomer(4010, "Lee", &c);
  addCustomer(arr, c);
  initCustomer(4012, "Kara", &c);
  addCustomer(arr, c);
  initCustomer(4015, "Laura", &c);
  addCustomer(arr, c);
  initCustomer(4016, "Gaius", &c);
  addCustomer(arr, c);
  initCustomer(4019, "Bill", &c);
  addCustomer(arr, c);
  initCustomer(4025, "Sharon", &c);
  addCustomer(arr, c);
  initCustomer(4028, "Karl", &c);
  addCustomer(arr, c);
  initCustomer(4029, "Sonja", &c);
  addCustomer(arr, c);
  
  addToCustomer(clinic, 4010, 1002);
  addToCustomer(clinic, 4025, 1024);
  addToCustomer(clinic, 4025, 1027);
  addToCustomer(clinic, 4015, 1013);
  addToCustomer(clinic, 4015, 1023);
  addToCustomer(clinic, 4012, 1029);
  addToCustomer(clinic, 4012, 1033);
  addToCustomer(clinic, 4012, 1032);
  addToCustomer(clinic, 4029, 1007);
  addToCustomer(clinic, 4029, 1008);
  addToCustomer(clinic, 4019, 1016);
  addToCustomer(clinic, 4019, 1017);

  addToCustomer(clinic, 4021, 1001);
  addToCustomer(clinic, 4016, 1015);
  addToCustomer(clinic, 4016, 1002);
  printf("...DONE \n\n");
}

/*
  Function:  initSchedule
  Purpose:   initializes the clinic collection that has customer array
       in:   schedule list
       in:   animal array
      out:   the schedule collection
   return:   nothing
*/
void initSchedule(ScheduleType *sched, AnimalArrayType *animals)
{
  AppointmentType *appt;
  initSchedList(sched);
  printf("Initialization of Appointments: \n");
  if (initAppointment(animals, 7010, 1001, 2021, 10, 3, 11, 15, &appt) == 0)
    addAppointment(sched, appt);
  if (initAppointment(animals, 7011, 1013, 2021, 10, 3, 11, 30, &appt) == 0)
    addAppointment(sched, appt);
  if (initAppointment(animals, 7012, 1013, 2021, 10, 3, 11, 45, &appt) == 0)
    addAppointment(sched, appt);
  if (initAppointment(animals, 7018, 1021, 2021, 10, 3, 11, 45, &appt) == 0)
    addAppointment(sched, appt);
  if (initAppointment(animals, 7019, 1021, 2021, 10, 3, 12, 0, &appt) == 0)
    addAppointment(sched, appt);
  if (initAppointment(animals, 7015, 1032, 2021, 10, 3, 11, 0, &appt) == 0)
    addAppointment(sched, appt);
  if (initAppointment(animals, 7016, 1032, 2021, 10, 3, 11, 0, &appt) == 0)
    addAppointment(sched, appt);
  if (initAppointment(animals, 7014, 1023, 2021, 11, 3, 10, 0, &appt) == 0)
    addAppointment(sched, appt);
  if (initAppointment(animals, 7005, 1007, 2021, 11, 3, 9, 45, &appt) == 0)
    addAppointment(sched, appt);
  if (initAppointment(animals, 7007, 1007, 2021, 11, 3, 9, 30, &appt) == 0)
    addAppointment(sched, appt);
  if (initAppointment(animals, 7008, 1017, 2021, 10, 2, 11, 15, &appt) == 0)
    addAppointment(sched, appt);

  if (initAppointment(animals, 7017, 1015, 2021, 11, 3, 11, 15, &appt) == 0)
    addAppointment(sched, appt);
  if (initAppointment(animals, 7013, 1029, 2018, 10, 1, 11, 45, &appt) == 0)
    addAppointment(sched, appt);
  if (initAppointment(animals, 7013, 1029, 2021, 14, 1, 11, 45, &appt) == 0)
    addAppointment(sched, appt);
  if (initAppointment(animals, 7013, 1029, 2021, 10, 41, 11, 45, &appt) == 0)
    addAppointment(sched, appt);
  if (initAppointment(animals, 7013, 1029, 2021, 10, 1, 1, 45, &appt) == 0)
    addAppointment(sched, appt);
  if (initAppointment(animals, 7013, 1029, 2021, 10, 1, 11, 25, &appt) == 0)
    addAppointment(sched, appt);
  printf("\n...DONE \n\n");

}

//DONE//
