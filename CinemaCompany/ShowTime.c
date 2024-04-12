#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ShowTime.h"
#include "general.h"
#include "macros.h"
#include "fileHelper.h"

void printShowTime(const ShowTime* showTime)
{
	printf("\n\nserial number: %d\n",showTime->serialNum);
	printMovie(&showTime->theMovie);
	printTheater(&showTime->theTheater);
	printDate(&showTime->date);
	printTime(&showTime->time);
}

void printShowTimeV(void* val)
{
	printShowTime((const ShowTime*)val);
}

int	saveShowTimeToBinaryFile(const ShowTime* pShowTime, FILE* fp)
{
    if (!pShowTime || !fp) return 0;

	if (!writeIntToFile(pShowTime->serialNum, fp, "Error writing theater number"))
	{
		COLSE_FILE_RETURN_ZERO(fp); 
	}

	if (!writeStringToFile(pShowTime->theMovie.name, fp, "Error writing movie name"))
	{
		COLSE_FILE_RETURN_ZERO(fp);
	}

	if (!writeIntToFile(pShowTime->theTheater.theaterNumber, fp, "Error writing theater number"))
	{
		COLSE_FILE_RETURN_ZERO(fp);
	}

	saveDateToBinaryFile(&pShowTime->date, fp);
	//fwrite(&pShowTime->date, sizeof(pShowTime->date), 1, fp); 
	saveTimeToBinaryFile(&pShowTime->time, fp);

	//fwrite(&pShowTime->time, sizeof(pShowTime->time), 1, fp); 

    return 1;
}


void freeShowTime(ShowTime* showTime)
{
	freeMovie(&showTime->theMovie);
}


