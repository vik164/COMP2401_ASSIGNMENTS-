#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"

/*
  Function:  initCustomerArray
  Purpose:   initialize dynamically allocated array
       in:   collection of customers array
      out:   all of array set to NULL
   return:   nothing
*/
void initCustomerArray(CustomerArrayType *arr){
  arr->elements = malloc(MAX_ARR * sizeof(CustomerType*));
  arr->size = 0;
}

/*
  Function:  initCustomer
  Purpose:   dynamically allocates memory
       in:   customer id
       in:   customer name
       in:   new customer pointee
      out:   dynamically allocates memory and initializes it for new customer
   return:   nothing
*/
void initCustomer(int id, char *name, CustomerType **cust){
  CustomerType* c = (CustomerType*) malloc(sizeof(CustomerType));
  
  c->id = id;
  strcpy(c->name,name);
  initAnimalArray(&c->pets);
  *cust = c;
}

/*
  Function:  addCustomer
  Purpose:   add customer to array
   in:       customer collection array
   in:       new customer to add
   out:      customer added to customer collection array
   return:   C_OK for success, C_NOK for failure
*/
int addCustomer(CustomerArrayType *arr, CustomerType *cust){
  if(arr->size < MAX_ARR){
    arr->elements[arr->size] = cust;
    ++arr->size; 
    return C_OK;
  }
  return C_NOK;
}


/*
  Function:  findCustomer
  Purpose:   find customer in array
   in:       customer collection array
   in:       customer id
   in:       customer
   out:      return customer if found
   return:   C_OK for success, C_NOK for failure
*/
int findCustomer(CustomerArrayType *arr, int id, CustomerType **cust){
  for(int i=0; i<arr->size; i++){
    if(arr->elements[i]->id == id){
      *cust = arr->elements[i];
      return C_OK;
    } 
  }
  return C_NOK;
}

/*
  Function:  addToCustomer
  Purpose:   Adds customer and animal to clinic
       in:   clinic
       in:   given customer to add
       in:   given animal to add
      out:   added customer with animal to clinic
   return:   C_OK for success, C_NOK for failure
*/
int addToCustomer(ClinicType *clinic, int custId, int animalId){
    CustomerType *Cc;
    AnimalType *Aa;
    
    if(findCustomer(&clinic->customers, custId, &Cc) == C_OK){
      if(findAnimal(&clinic->animals, animalId, &Aa) == C_OK){
        if(Aa->parent == NULL){
          Aa->parent = Cc->name;
          addAnimal(&Cc->pets,Aa);
	  return C_OK;
	}
	else{
	  printf("ANIMAL HAS PARENT - %s\n", Aa->name);
	  
	}
      }
      else{
        printf("ANIMAL ID NOT FOUND - %d\n", animalId);   
      }
    }
    else{
      printf("CUSTOMER NOT FOUND - %d\n", custId);
    }
  return C_NOK;
}

/*
  Function:  printCustomers
  Purpose:   Prints customers with formating
       in:   customers collection in array
      out:   Prints all customers
   return:   nothing
*/
void printCustomers(CustomerArrayType *arr){
  for(int i=0;i<arr->size;i++){
    printf("\n%d %s \n",arr->elements[i]->id, arr->elements[i]->name);
    printf("PETS:\n");
    if(arr->elements[i]->pets.size == 0){
      printf("     NONE \n");
    }
    printAnimals(&arr->elements[i]->pets);
  }
}

/*
  Function:  cleanupCustomers
  Purpose:   Deallocate the dynamically allocated memory
       in:   customers collection in array
      out:   dynamically allocated memory is deallocated
   return:   nothing
*/
void cleanupCustomers(CustomerArrayType *arr){
  for(int i=0;i<arr->size;++i){
    free(arr->elements[i]);
  }
  free(arr->elements);
  
}

//DONE//

