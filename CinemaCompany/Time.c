#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Time.h"
#include "general.h"

#define TIME_SEPERATOR ':'

void	getTime(Time* pTime)
{
	char time[MAX_STR_LEN];
	int ok = 1;

	do {
		printf("Enter movie time hh%cmm\t",TIME_SEPERATOR);
		myGets(time, MAX_STR_LEN);
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

void printTime(const Time* pTime)
{
	printf("Time: %d:%d", pTime->hour, pTime->minuets);
}
