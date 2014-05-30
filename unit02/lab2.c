/*
  Author:  Chris Ottersen
  Program: lab2.c
  Date:    24 JAN 2013
  VERSION: 1.5
*/
#include <stdlib.h>
#include"CommonHeader.h"

#include "LinkedList.h"
#include "Contact.h"
typedef enum MAIN_MENU_CHOICE_P MAIN_MENU_CHOICE;
MAIN_MENU_CHOICE mainMenu();

enum MAIN_MENU_CHOICE_P 
{ 
  EXIT_PROGRAM      = 0 ,
  ADD_CONTACT       = 1 ,
  MODIFY_CONTACT    = 2 , 
  DELETE_CONTACT    = 3 ,
  PRINT_RECORD      = 4 ,
  PRINT_BY_CRITERIA = 5 ,
  PRINT_ALL         = 6
};

int main(int argc, char* argv)
{
  LIST* list;
  int choice;

  FunctionPointers nodeFunctionPointers;
  ListDataPointers listDataPointers;
  char* fileAddress = "contacts.data";

      nodeFunctionPointers.newValue	= (void *(*)())                                   &newContact;
   nodeFunctionPointers.deleteValue	= (int (*)(void *value))                          &deleteContact;                                                                                                                                                                                                               
     nodeFunctionPointers.saveValue	= (int (*)(FILE *file, void *value))              &saveContact;
     nodeFunctionPointers.loadValue	= (void *(*)(FILE *file))                         &loadContact;
          nodeFunctionPointers.edit	= (int (*)(void *value))                          &editContact;
   nodeFunctionPointers.compareFind = (int (*)(void *value, int type, void *target))  &contactCompareFind;
   nodeFunctionPointers.compareSort = (int (*)(void *value, void *key))               &contactCompareSort;
      nodeFunctionPointers.toString = (int (*)(void* value, char* string, int type))  &contactToString;
          listDataPointers.findMenu	= (int (*)())                                     &findMenu;
            listDataPointers.prompt	= (int (*)(int type, void* input))                &prompt;
       listDataPointers.tableHeader	=                                                 &contactTableHeader;
       listDataPointers.fileAddress =                                                  fileAddress;

  list = newLinkedList(&listDataPointers, &nodeFunctionPointers);
  choice = 1;
  while(choice)
  {
    char* inputBuf;
    //void *input;
    CONTACT_FIELD type;

    
    choice = mainMenu();
    switch(choice)
    {
      case ADD_CONTACT: 
              newElement(list, NULL);
              break;
      case MODIFY_CONTACT: 
              modifyElement(list, MODIFY);
				      break;
      case DELETE_CONTACT: 
              modifyElement(list, REMOVE);
              break;
      case PRINT_RECORD: 
              printElement(list);
              break;
      case PRINT_BY_CRITERIA: 
              inputBuf = valueBufferC;
              inputBuf[0] = '\0';

              type = printByMenu();
              if(type == 1) break;

              prompt(type, inputBuf);
              printList(list, (FIND_BY) type, inputBuf);

              inputBuf[0] = '\0';
              break;
      case PRINT_ALL: 
              printList(list, BY_KEY, NULL);
              break;
      case EXIT_PROGRAM: 
              saveList(list);
              deleteList(list);
    }
    PAUSE
  }

}

/*
  mainMenu
  description
    displays main menu and collects user's choice.
  params:
    void
  return: 
    int   menu choice
*/
MAIN_MENU_CHOICE mainMenu()
{
  MAIN_MENU_CHOICE choice;
  CLEAR
  printf("WELCOME TO CONTACT LINKED LIST MENU!!\n\n");
  printf("1. Inserting a new structure into the link list.\n");
  printf("2. Modifying an existing structure in the link list.\n");
  printf("3. Delete an existing structure from the list.\n");
  printf("4. Print a specific name and phone number (first occurance).\n");
  printf("5. Print a specific name and phone number (all fitting criteria).\n");
  printf("6. Print all names and phone numbers.\n");
  printf("0. Exit from program.\n");
  scanf("%d", &choice);
  FLUSH
  while(choice > 6 || choice < 0)
  {
    CLEAR
    printf("WELCOME TO CONTACT LINKED LIST MENU!!\n\n");
    printf("   input '%d' invalid; input must be among those listed.\n", choice);
    printf("1. Inserting a new structure into the link list.\n");
    printf("2. Modifying an existing structure in the link list.\n");
    printf("3. Delete an existing structure from the list.\n");
    printf("4. Print a specific name and phone number (first occurance).\n");
    printf("5. Print a specific name and phone number (all fitting criteria).\n");
    printf("6. Print all names and phone numbers.\n");
    printf("0. Exit from program.\n");
    scanf("%d", &choice);
    FLUSH
  }

  return choice;

}

