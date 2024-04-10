#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Time.h"
#include "general.h"
#include "macros.h"

#define TIME_SEPERATOR ':'

void	getTime(Time* pTime)
{
	char time[MAX_STR_LEN];
	int ok = 1;

	do {
		printf("Enter movie time hh%cmm\t",TIME_SEPERATOR);
		myGets(time, MAX_STR_LEN, stdin);
		ok = checkTime(time, pTime);
		if (!ok)
			printf("Error try again\n");
	} while (!ok);
}

int	 checkTime(char* time, Time* pTime)
{
	int hour, minuets; 
	if (strlen(time) != 5)
		return 0;
	if (time[2] != TIME_SEPERATOR) return 0;
	sscanf(time, "%d%*c%d", &hour, &minuets);
	if (hour < 0 || hour > 23 || minuets < 0 || minuets > 59)
		return 0;

	pTime->hour = hour;
	pTime->minuets = minuets;
	

	return 1;
}

int		saveTimeToFile(const Time* pTime, FILE* fp)
{
	if (fwrite(pTime, sizeof(Time), 1, fp) != 1)
	{
		printf("Error write date\n");
		return 0;
	}

	return 1;

}

Time* loadTimeFromTxtFile(FILE* fp) {
	Time* pTime = (Time*)malloc(sizeof(Time));
	RETURN_NULL(pTime);
	char timeStr[MAX_STR_LEN]; 

	
	if (fgets(timeStr, sizeof(timeStr), fp) != NULL) {
		timeStr[strcspn(timeStr, "\n")] = 0;

		
		sscanf(timeStr, "%d:%d", &pTime->hour, &pTime->minuets);
	}

	return pTime;
}

void printTime(const Time* pTime)
{
	printf("Time: %d:%d", pTime->hour, pTime->minuets);
}
