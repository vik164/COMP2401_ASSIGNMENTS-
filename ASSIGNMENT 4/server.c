#include "defs.h"
#include <unistd.h>
#include <signal.h>

int listenSocket;

int main()
{
   int clientSocket;
   char nameOfLib[MAX_STR];
   LibraryType *lib;

   initLibrary(&lib, nameOfLib);
   setupServerSocket(&listenSocket);
   printf("Waiting for connection request... \n");

   signal(SIGUSR1, handleSig1);
   
   acceptConnection(listenSocket, &clientSocket);
   serveOneClient(clientSocket, lib);

  return 0;
}

/*
  Function:  serveOneClient
  Purpose:   handles request sent by client to server 
   in:       client socket
   in:       library
   out:      the servers response
   return:   nothing
*/
void serveOneClient(int clientSocket, LibraryType *lib){
  char rvcClient[MAX_STR];
  char newstr[MAX_BUFF*MAX_STR] = "";
  char str[MAX_STR];
  int id;
  int response;
  int num;
  
  printf("...connected \n");
 
  while(1) {
    printf("Waiting for message... \n");
    rcvData(clientSocket, rvcClient);
    printf("...received \n");
    sscanf(rvcClient, "%d %d", &num, &id);
    
    printf("client sent:  %s\n\n", rvcClient);
    
    if(num == REQ_RET_BOOKS){
      formatBooks(&lib->books, newstr);
      sendData(clientSocket, newstr);
      strcpy(newstr, "");
    }
    else if(num == REQ_CHECK_OUT){
      response = checkOutBook(lib, id);
      
      if(response == C_OK){
        strcpy(str,"BOOK CHECKED OUT\n");
      }
      else if(response == C_NOK){
        strcpy(str,"ERROR: Book id was already checked out\n");
      }
      else if(response == C_BOOK_NOT_FOUND){
        strcpy(str,"ERROR: Book id does not exist\n");
      }
      else if(response == C_BAD_STATUS){
        strcpy(str,"ERROR: Book id is not available for check out\n");
      }
      
      sendData(clientSocket, str);
    }
    else if(num == REQ_CHECK_IN){   
      response = checkInBook(lib, id);
      
      if(response == C_OK){
        strcpy(str,"BOOK CHECKED IN\n");
      }
      else if(response == C_NOK){
        strcpy(str,"ERROR: Book id was already checked in\n");
      }
      else if(response == C_BOOK_NOT_FOUND){
        strcpy(str,"ERROR: Book id does not exist\n");
      }
      else if(response == C_BAD_STATUS){
        strcpy(str,"ERROR: Book id is not available for check out\n");
      }

      sendData(clientSocket, str);
    }
    else if(num == REQ_CLOSE){
      printf("Shutting down...\n");
      close(clientSocket);
      closeAll(lib);
      printf("...done\n");
      exit(0);
      break;
    }    
  } 
}


void closeAll(LibraryType *lib){
  close(listenSocket);
  cleanupLibrary(lib);
}

void handleSig1(int i){
  close(listenSocket);
  exit(SIGUSR1);
}

//DONE//

