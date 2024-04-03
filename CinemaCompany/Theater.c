#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Theater.h"

void initTheater(Theater* theater, Theater* theaterArr, int theaterCount)
{
	theater->type = getTheaterType();
	if (!(strcmp(TheaterTypeStr[theater->type], "Regular")))
		theater->maximumCapacity = 50;

	if (!(strcmp(TheaterTypeStr[theater->type], "VIP")))
		theater->maximumCapacity = 20;
	
	if (!(strcmp(TheaterTypeStr[theater->type], "3D")))
		theater->maximumCapacity = 30;

	///// here
	theater->seats = (int*)calloc(theater->maximumCapacity, sizeof(int));
	if (theater->seats == NULL) return;
	theater->theaterNumber = theaterCount+1;
}


eTheaterType getTheaterType()
{
	int choice = 0;
	do {
		printf("Enter one of the following types\n");
		for (int i = 0; i < eNumOfTypes; i++)
			printf("%d for %s\n", i, TheaterTypeStr[i]);
		scanf("%d", &choice);
	} while (choice < 0 || choice >= eNumOfTypes);
	return (eTheaterType)choice;
}

void printTheater(const Theater* theater)
{
	printf("Number of theater: %d\tType of theater: %s\n", theater->theaterNumber, TheaterTypeStr[theater->type]);
}

void freeTheater(Theater* theater)
{
	free(theater->seats); 
	free(theater);  
}
