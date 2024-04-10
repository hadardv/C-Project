#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ShowTime.h"

void printShowTime(const ShowTime* showTime)
{
	printf("serial number: %d\n",showTime->serialNum);
	printMovie(&showTime->theMovie);
	printTheater(&showTime->theTheater);
	printDate(&showTime->date);
	printTime(&showTime->time);
}

void printShowTimeV(void* val)
{
	printShowTime((const ShowTime*)val);
}

int	saveShowTimeToFile(const ShowTime* pShowTime, FILE* fp)
{
	if (fwrite(pShowTime, sizeof(ShowTime), 1, fp) != 1)
	{
		printf("Error write date\n");
		return 0;
	}
	return 1;

}

void freeShowTime(ShowTime* showTime)
{
	freeMovie(&showTime->theMovie);
	freeTheater(&showTime->theTheater);
}


