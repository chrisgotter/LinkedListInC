//so that visual studios will stop telling me that there is something wrong with string functions 
#define _CRT_SECURE_NO_WARNINGS
#define BUFFER 300
//standard windows specific system commands
#ifdef _WIN32
  #define PAUSE system("pause");
  #define CLEAR system("cls");
  #define FLUSH fflush(stdin);
//more generic substitutes
#else 
  #define PAUSE printf("Press 'Enter' to continue: ... ");\
	              FLUSH
  #define CLEAR system("clear");
  #define FLUSH while ( getchar() != '\n');

#endif
//buffer variables which have made global to reduce the need to generate such arrays
char valueBufferA[BUFFER];
char valueBufferB[BUFFER];
char valueBufferC[BUFFER];