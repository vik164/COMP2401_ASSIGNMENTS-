#include <stdio.h>

#define C_TRUE     1
#define C_FALSE    0

#define C_OK       0
#define C_NOK     -1

#define MAX_STR   32
#define MAX_ARR  128

typedef enum {C_DOG, C_CAT, C_SPEC_OTHER} SpeciesType;

struct Customer;

typedef struct {
  int             id;
  SpeciesType     species;
  char            name[MAX_STR];
  char            gender[MAX_STR];
  int             age;
  struct Customer *parent;
} AnimalType;

/*** Define the AnimalArrayType here ***/
typedef struct {
  int size;
  AnimalType *elements[MAX_ARR];
} AnimalArrayType;
  
typedef struct Customer {
  int  id;
  char name[MAX_STR];
  AnimalArrayType pets;
} CustomerType;

/*** Define the CustomerArrayType here ***/
typedef struct {
  int size;
  CustomerType **elements;;
} CustomerArrayType;

typedef struct {
  int hour;
  int mins;
} TimeType;

typedef struct {
  int      year;
  int      month;
  int      day;
  TimeType tt;
} DateType;

typedef struct {
  int          id;
  DateType     *dt;
  CustomerType *cust;
  AnimalType   *animal;
} AppointmentType;

/*** Define the other data types here ***/
typedef struct Node {
  AppointmentType *data;
  struct Node *prev;
  struct Node *next;
} NodeType;

typedef struct List {
  struct Node *head;
} ListType;

typedef struct {
  ListType list;
} ScheduleType;

typedef struct {
  char              name[MAX_STR];
  AnimalArrayType   animals;
  CustomerArrayType customers;
  ScheduleType      sch;
} ClinicType;


void printMenu(int*);

void initCustomerArray(CustomerArrayType *arr);
void initCustomer(int id, char *name, CustomerType **cust);
int addCustomer(CustomerArrayType *arr, CustomerType *cust);
int findCustomer(CustomerArrayType *arr, int id, CustomerType **cust);
int addToCustomer(ClinicType *clinic, int custId, int animalId);
void printCustomers(CustomerArrayType *arr);
void cleanupCustomers(CustomerArrayType *arr);

void initAnimalArray(AnimalArrayType *arr);
void initAnimal(int id, SpeciesType sp, char *name, char *g, int y, int m, AnimalType **an);
int addAnimal(AnimalArrayType *arr, AnimalType *an);
int findAnimal(AnimalArrayType *arr, int id, AnimalType **an);
void printAnimals(AnimalArrayType *arr);
void convertspecies(SpeciesType sp, char *spStr);
void cleanupAnimals(AnimalArrayType *arr);

void initAnimals(AnimalArrayType *arr);
void initSchedule(ScheduleType *sched, AnimalArrayType *animals);
void initCustomers(ClinicType *clinic);

void initClinic(ClinicType *c, char *name);
void cleanupClinic(ClinicType *clinic);

void initSchedList(ScheduleType *sched);
int initAppointment(AnimalArrayType *animals, int id, int anId, int y, int m, int d, int h, int mn, AppointmentType **appt);
int compareDates(DateType *d1, DateType *d2);
int overlapAppts(AppointmentType *a1, AppointmentType *a2);
int addAppointment(ScheduleType *sched, AppointmentType *appt);
void printSchedule(ScheduleType *sched);
void printAppointments(AppointmentType *appt);
void cleanupSchedule(ScheduleType *sched);


//DONE//
