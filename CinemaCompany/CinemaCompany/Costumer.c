#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include "Costumer.h"
#include "general.h"
#include "macros.h"

Costumer initCostumer(Costumer* pCostumer)
{
	pCostumer->age = setAge();
	pCostumer->id = setId();
	return *pCostumer;
}

int setAge() {
	int age;
	do {
		printf("Enter your age\n");
		scanf("%d", &age);
	} while (age < 0 || age>120);
		return age; 
}

int setId() {
	int id;
	do {
		printf("Enter your id\n");
		scanf("%d", &id);
	} while (!isValidId);
		return id; 
}

int isValidId(int id)
{
	int checkDigit = 0, idWithoutCkeckDigit =0,sum = 0;
	checkDigit = id % 10;
	idWithoutCkeckDigit = id / 10;
	for (int i = 1; i <= 8; i++)
	{
		if ((i % 2) != 0)
		{
			if ((idWithoutCkeckDigit % 10) * 2 >= 10)
				sum += ((idWithoutCkeckDigit % 10 * 2) % 10) + 1;
			else 
				sum += (idWithoutCkeckDigit % 10) * 2;
		}
		else
		{
			sum += idWithoutCkeckDigit % 10;
		}
		idWithoutCkeckDigit /= 10;
	}
	if (10 - (sum % 10) == checkDigit)
		return 1;
	else
	{
		printf("id is not valid\n");
		return 0;
	}
}

int saveCostumerToFile(const Costumer* costumer, const char* fileName) {
	FILE* fp = fopen(fileName, "wb"); 
	RETURN_ZERO(fp);
	

	if (fwrite(costumer, sizeof(Costumer), 1, fp) != 1) {
		printf("Failed to write costumer to file.\n");
		fclose(fp);
		return 0; 
	}

	fclose(fp); 
	return 1; 
}

void printCostumer(const Costumer* costumer)
{
	printf("%d\n", costumer->id);
}

