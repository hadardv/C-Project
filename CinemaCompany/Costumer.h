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

#endif 