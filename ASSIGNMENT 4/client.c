#include "defs.h"
/*
    VIKRANT KUMAR 101195442

    This program allows the user to sign in and sign out books at a library.
*/

int main()
{
  int choice = -1;
  int clientSocket;
  char strSend[MAX_STR];
  char allBooks[MAX_BUFF*MAX_STR] = "";
  char str[MAX_STR];
  char InOutStr[MAX_STR];
  int id;
 
  setupClientSocket(&clientSocket);

  while (1) {

   clientMenu(&choice);

   switch(choice) {

      case 1:   // Print books
                sprintf(strSend, "%d", REQ_RET_BOOKS);          
                sendData(clientSocket, strSend);
                rcvData(clientSocket, allBooks);
                
                printf("%s", allBooks);
                strcpy(allBooks, "");
        break;

      case 2:   // Check out a book
               printf("PLease enter id: ");
               fgets(str, sizeof(str), stdin);
               sscanf(str, "%d", &id); 
               
               sprintf(strSend, "%d %d", REQ_CHECK_OUT, id);
               sendData(clientSocket, strSend);
               rcvData(clientSocket, InOutStr);
               
               printf("%s", InOutStr);
        break;

      case 3:   // Check in a book
               printf("PLease enter id: ");
               fgets(str, sizeof(str), stdin);
               sscanf(str, "%d", &id); 
               
               sprintf(strSend, "%d %d", REQ_CHECK_IN, id);
               sendData(clientSocket, strSend);
               rcvData(clientSocket, InOutStr);
               
               printf("%s", InOutStr);
        break;

      case 0:   // Close everything
                sprintf(strSend, "%d", REQ_CLOSE);
                sendData(clientSocket, strSend);
                return 0;
        break;

      default:
        printf("ERROR:  invalid option\n");
    }
  }

  return 0;
}

void clientMenu(int* choice)
{
  int c = -1;
  int numOptions = 3;
  char str[MAX_STR];

  printf("\nMAIN MENU\n");
  printf("  (1) Print books\n");
  printf("  (2) Check out a book\n");
  printf("  (3) Check in a book\n");
  printf("  (0) Exit\n\n");

  printf("Please enter your selection: ");
  fgets(str, sizeof(str), stdin);
  str[strcspn(str, "\n")] = 0;
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
