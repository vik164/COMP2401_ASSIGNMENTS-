#include "defs.h"

/*
  Function:  initList
  Purpose:   initialize array
       in:   collection of book array
      out:   array set to NULL
   return:   nothing
*/
void initList(BookListType *list){
  list->head = NULL;
  list->tail = NULL;
}

/*
  Function:  initBook
  Purpose:   dynamically allocates memory
       in:   book id
       in:   book title
       in:   book author
       in:   book year of publish
       in:   book status type
       in:   new book pointee
      out:   dynamically allocates memory and initializes it for new book
   return:   nothing
*/
void initBook(int i, char *t, char *a, int y, BookStatusType st,BookType **book){
  BookType* books = (BookType*) malloc(sizeof(BookType));

  books->id = i;
  strcpy(books->title,t);
  strcpy(books->author,a);
  books->year = y;
  books->status = st; 
  
  *book = books;
}

/*
  Function:  addBook
  Purpose:   add book to array
   in:       book collection
   in:       new book to add
   out:      book added to book collection
   return:   nothing
*/
void addBook(BookListType *list, BookType *b){
   NodeType *nodeCurrent;
   NodeType *nodePervious;
   NodeType *nodeNew;
   
   nodeCurrent = list->head;
   nodePervious = NULL;
   
   while (nodeCurrent != NULL) {
     if(strcmp(b->title, nodeCurrent->data->title)<0){
       break;
     }
     nodePervious = nodeCurrent;     
     nodeCurrent = nodeCurrent->next;
   }
  
   nodeNew = malloc(sizeof(NodeType));
   nodeNew->data = b;
   nodeNew->next = NULL;

   if (nodePervious == NULL){ 
     list->head = nodeNew;
   }
   else{
     nodePervious->next = nodeNew;
   }
   nodeNew->next = nodeCurrent;
 
   if ((nodeCurrent != NULL)){
     list->tail = nodeNew;
   }
   
   nodeCurrent = list->head;
   while (nodeCurrent != NULL) {
     if(nodeCurrent->next == NULL){
       list->tail = nodeCurrent;
     }
     nodeCurrent = nodeCurrent->next;
   }
}

/*
  Function:  findBook
  Purpose:   find book 
   in:       book collection array
   in:       book id
   in:       book
   out:      return book if found
   return:   C_OK for success, C_NOK for failure
*/
int findBook(BookListType *list, int id, BookType **b){
   NodeType *nodeCurrent;
   
   nodeCurrent = list->head;

  while(nodeCurrent != NULL){
    if(nodeCurrent->data->id == id){
      *b = nodeCurrent->data;
      return C_OK;
    }
    nodeCurrent = nodeCurrent->next;
  }
  return C_NOK; 
}

/*
  Function:  formatBook
  Purpose:   Formats book
       in:   book
       in:   formated book
      out:   stores new formated book in outStr 
   return:   nothing
*/
void formatBook(BookType *b, char *outStr){
  char status[MAX_STR];
  convertStatus(b->status, status);
  sprintf(outStr, "ID: %-5d Title: %-40s Author: %-20s Year: %-5d Status: %-5s\n",b->id,b->title,b->author,b->year,status);
 
}

/*
  Function:  convertStatus
  Purpose:   convert status to string
       in:   the book status
       in:   converted status
      out:   returns corresponding string
   return:   nothing
*/
void convertStatus(BookStatusType stat, char *statStr){
  if(stat == CHECKED_IN){
    strcpy(statStr, "Checked In");
  }
  else if(stat == CHECKED_OUT){
    strcpy(statStr,"Checked Out");
  }
  else if(stat == UNDER_REPAIR){
    strcpy(statStr,"Under Repair");
  }
  else if(stat == LOST){
    strcpy(statStr,"LOST");
  }
  else{
    strcpy(statStr,"INVAILD");
  }
}

/*
  Function:  formatBooks
  Purpose:   Formats all books
       in:   book list
       in:   formated long string 
      out:   stores all formated books in outStr 
   return:   nothing
*/
void formatBooks(BookListType *list, char *outStr){
  char str[MAX_ARR] = "";
  char str2[MAX_ARR] = "";
  
  NodeType *nodeCurrent;
  nodeCurrent = list->head;
  
  while(nodeCurrent != NULL){
    formatBook(nodeCurrent->data, str);
    strcat(outStr, str);
    nodeCurrent = nodeCurrent->next;
  }
  
  formatBook(list->head->data, str2);
  char head[MAX_STR] = "---HEAD ";
  strcat(head, str2);
  strcat(outStr,head);
  
  formatBook(list->tail->data, str2);
  char tail[MAX_STR] = "---TAIL ";
  strcat(tail, str2);
  strcat(outStr,tail);
}

/*
  Function:  cleanupList
  Purpose:   Deallocate the dynamically allocated memory
       in:   book collection in array
      out:   dynamically allocated memory is deallocated
   return:   nothing
*/
void cleanupList(BookListType *list){
   NodeType *nodeCurrent;
   NodeType *nodeNext;

   nodeCurrent = list->head;

   while (nodeCurrent != NULL) {
     nodeNext = nodeCurrent->next;
     free(nodeCurrent->data);
     free(nodeCurrent);
     nodeCurrent = nodeNext;
  }
}

//DONE//
