#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"

/*
  Function:  initAnimalArray
  Purpose:   initialize array
       in:   collection of animal array
      out:   all of array set to NULL
   return:   nothing
*/
void initAnimalArray(AnimalArrayType *arr){
  arr->size = 0;
}

/*
  Function:  initAnimal
  Purpose:   dynamically allocates memory
       in:   animal id
       in:   animal specie
       in:   animal name
       in:   animal gender
       in:   animal age in year
       in:   animal age in months
       in:   new animal pointee
      out:   dynamically allocates memory and initializes it for new animal
   return:   nothing
*/
void initAnimal(int id, SpeciesType sp, char *name, char *g, int y, int m, AnimalType **an){

  AnimalType* animal = (AnimalType*) malloc(sizeof(AnimalType));
  
  int totalMonths;
  
  totalMonths = (y*12) + m;

  animal->id = id;
  animal->species = sp; 
  strcpy(animal->name,name);
  strcpy(animal->gender,g);
  animal->age = totalMonths;
  animal->parent = NULL;
  
  *an = animal;
}

/*
  Function:  addAnimal
  Purpose:   add animal to array
   in:       animal collection array
   in:       new animal to add
   out:      animal added to animal collection array
   return:   C_OK for success, C_NOK for failure
*/
int addAnimal(AnimalArrayType *arr, AnimalType *an){
  if(arr->size >= MAX_ARR){
    return C_NOK;
  }
   
  if(arr->size == 0){
    arr->elements[0] = an;
    ++arr->size; 
    return C_OK;
  }
  else{
    for(int i=0;i<arr->size;++i){
      if(an->age > arr->elements[i]->age){
        for(int j=arr->size;j>i;--j){
          arr->elements[j] = arr->elements[j-1];         
         }
         arr->elements[i] = an;
         ++arr->size;
         return C_OK;
       }      
     }
   }
   arr->elements[arr->size] = an;
   ++arr->size;
   return C_OK;  
}

/*
  Function:  findAnimal
  Purpose:   find animal in array
   in:       animal collection array
   in:       animal id
   in:       animal
   out:      return animal if found
   return:   C_OK for success, C_NOK for failure
*/
int findAnimal(AnimalArrayType *arr, int id, AnimalType **an){
  for(int i=0; i<arr->size; i++){
    if(arr->elements[i]->id == id){
      *an = arr->elements[i];
      return C_OK;
    } 
  }
  return C_NOK;
}

/*
  Function:  printAnimals
  Purpose:   Prints animals with formating
       in:   animal collection in array
      out:   Prints all animals in sorted order
   return:   nothing
*/
void printAnimals(AnimalArrayType *arr){
  char spConverted[MAX_STR];
  int mon;
  int year;
  
  for(int i=0;i<arr->size;i++){
    convertspecies(arr->elements[i]->species, spConverted);
    mon = arr->elements[i]->age%12;
    year = (arr->elements[i]->age-mon)/12;
    if(arr->elements[i]->parent == NULL){
      printf("     %-5d %-12s %-8s Years:%-5d Months:%-5d NONE\n",arr->elements[i]->id,arr->elements[i]->name, spConverted, year, mon); 
    }
    else{
      printf("     %-5d %-12s %-8s Years:%-5d Months:%-5d %s\n",arr->elements[i]->id,arr->elements[i]->name, spConverted, year, mon, arr->elements[i]->parent); 
    }  
  } 
}

/*
  Function:  convertspecies
  Purpose:   converts species 
       in:   the animal species
       in:   converted string
      out:   returns corresponding string
   return:   C_OK for success, C_NOK for failure
*/
void convertspecies(SpeciesType sp, char *spStr){
  if(sp == C_DOG){
    strcpy(spStr, "DOG");
  }
  else if(sp == C_CAT){
    strcpy(spStr,"CAT");
  }
  else if(sp == C_SPEC_OTHER){
    strcpy(spStr,"OTHER");
  }
  else{
    strcpy(spStr,"INVAILD SPECIE");
  }
}

/*
  Function:  cleanupAnimals
  Purpose:   Deallocate the dynamically allocated memory
       in:   animal collection in array
      out:   dynamically allocated memory is deallocated
   return:   nothing
*/
void cleanupAnimals(AnimalArrayType *arr){
  for(int i=0;i<arr->size;++i){
    free(arr->elements[i]);
  }
}

//DONE//
