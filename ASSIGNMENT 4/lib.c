#include "defs.h"

/*
  Function:  loadBooks
  Purpose:   read books from text document
       in:   collection of book array
      out:   stored all data from document to books
   return:   nothing
*/
void loadBooks(BookListType *books){
  int id = 1000;
  char str[MAX_BUFF];
  char name[MAX_STR];
  char author[MAX_STR];
  int year;
  int status;
  FILE *infile;
  BookType *bookToAdd;
  
  infile = fopen("booksData.txt", "r");
  if(!infile){
    printf("ERROR: Could not open file\n");
    exit(1);
  }
  
  while (1) {
    fgets(name, sizeof(name), infile);
    if(name[strlen(name)-1] == '\n'){
      name[strlen(name)-1] = '\0';
    }
  
    fgets(author, sizeof(author), infile);
    if(author[strlen(author)-1] == '\n'){
      author[strlen(author)-1] = '\0';
    }
  
    fgets(str, sizeof(str), infile);
    sscanf(str,"%d", &year);
    
    fgets(str, sizeof(str), infile);
    sscanf(str,"%d", &status);

    if (feof(infile)){
      break;
    }
    
    initBook(++id, name, author, year, status, &bookToAdd);
    addBook(books, bookToAdd);
  }
  fclose(infile);
  
}

/*
  Function:  initLibrary
  Purpose:   dynamically allocates memory
       in:   library collection
       in:   name library
      out:   dynamically allocates memory and initializes it for new library
   return:   nothing
*/
void initLibrary(LibraryType **library, char *n){
  char books[MAX_BUFF*MAX_STR] = "";
  LibraryType* booked = (LibraryType*) malloc(sizeof(LibraryType));
  strcpy(n,"THE CARLETON BOOK LIBRARY:");
  
  initList(&booked->books);
  loadBooks(&booked->books);
  formatBooks(&booked->books, books);
 
  *library = booked;
  
  printf("\n%s",n);
  printf("\n%s", books);
}

/*
  Function:  checkOutBook
  Purpose:   checks book out
       in:   library
       in:   book id
      out:   checked book out that was currently checked in
   return:   C_BOOK_NOT_FOUND if book not found, C_BAD_STATUS if book is not available, or C_OK for success
*/
int checkOutBook(LibraryType *lib, int bookId){
  BookType *b;
  
  if(findBook(&lib->books, bookId, &b) == C_OK){
    if(b->status == CHECKED_IN){
      b->status = CHECKED_OUT;
      return C_OK;
    }
    else if(b->status == CHECKED_OUT){
      return C_NOK;
    }
    else{
      return C_BAD_STATUS;
    }
  }
  else{
    return C_BOOK_NOT_FOUND;
  }
}

/*
  Function:  checkInBook
  Purpose:   checks book in
       in:   library
       in:   book id
      out:   checked book in that was currently checked out
   return:   C_BOOK_NOT_FOUND if book not found, C_BAD_STATUS if book is not available, or C_OK for success
*/
int checkInBook(LibraryType *lib, int bookId){
  BookType *b;
  
  if(findBook(&lib->books, bookId, &b) == C_OK){
    if(b->status == CHECKED_OUT){
      b->status = CHECKED_IN;
      return C_OK;
    }
    else if(b->status == CHECKED_IN){
      return C_NOK;
    }
    else{
      return C_BAD_STATUS;
    }
  }
  else{
    return C_BOOK_NOT_FOUND;
  } 
}

/*
  Function:  cleanupLibrary
  Purpose:   Deallocate the dynamically allocated memory
       in:   library collection in array
      out:   dynamically allocated memory is deallocated
   return:   nothing
*/
void cleanupLibrary(LibraryType *lib){
   cleanupList(&lib->books);
   free(lib);
}

//DONE//
