#ifndef __GENERAL__
#define __GENERAL__

#define MAX_STR_LEN 255


char* getStrExactName(const char* msg);
char* myGets(char* buffer, int size, FILE* source);
char* getDynStr(char* str);
void generalArrayFunction(void* arr, int size, int typeSize, void(*func)(void* element));
int isAllLettersOrSpaces(const char* str);

#endif