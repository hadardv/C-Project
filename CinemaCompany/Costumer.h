#ifndef __COSTUMER__
#define __COSTUMER__

#include "list.h"


typedef struct
{
	int id;
	int age;

}Costumer;

Costumer initCostumer(Costumer* pCostumer);
int setAge();
int setId();
int isValidId(int id);
int saveCostumerToFile(const Costumer* costumer, const char* fileName);
int saveCompressedCostumerToFile(const Costumer* costumer, const char* fileName);
void printCostumer(const Costumer* costumer);

#endif 