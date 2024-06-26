#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Date.h"
#include "general.h"
#include "fileHelper.h"
#include "macros.h"


const int DAY_MONTHS[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
#define SEPERATOR '.'

void getDate(Date* pDate)
{
	char date[MAX_STR_LEN];
	int ok = 1;

	do {
		printf("Enter Movie Date dd%cmm%cyyyy  minimum year %d\t",
			SEPERATOR, SEPERATOR, MIN_YEAR);
		myGets(date, MAX_STR_LEN, stdin);
		ok = checkDate(date, pDate);
		if (!ok)
			printf("Error try again\n");
	} while (!ok);
}

int	 checkDate(char* date, Date* pDate)
{
	int day, month, year;
	if (strlen(date) != 10)
		return 0;
	if ((date[2] != SEPERATOR) || (date[5] != SEPERATOR))
		return 0;
	sscanf(date, "%d%*c%d%*c%d", &day, &month, &year);
	if (day < 1 || month < 1 || month > 12 || year < MIN_YEAR)
		return 0;

	if (day > DAY_MONTHS[month - 1])
		return 0;

	pDate->day = day;
	pDate->month = month;
	pDate->year = year;

	return 1;
}

int		saveDateToBinaryFile(const Date* pDate, FILE* fp)
{

	if (!writeIntToFile(pDate->day, fp, "Error writing day to file"))
	{
		fclose(fp);
		return 0;
	}
	if (!writeIntToFile(pDate->month, fp, "Error writing month to file"))
	{
		fclose(fp);
		return 0;
	}
	if (!writeIntToFile(pDate->year, fp, "Error writing year to file"))
	{
		fclose(fp);
		return 0;
	}
	return 1;

}

Date* loadDateFromTxtFile(FILE* fp) {

	Date* pDate = (Date*)malloc(sizeof(Date));
	RETURN_NULL(pDate);
	
	char dateStr[256];
	char* tempDateStr;

	myGets(dateStr, MAX_STR_LEN, fp);
	tempDateStr = getDynStr(dateStr);
	checkDate(tempDateStr, pDate);

	return pDate;
}

Date* loadDateFromBinaryFile(FILE* fp)
{
	Date* pDate = (Date*)malloc(sizeof(Date));
	if (!pDate)
	{
		fclose(fp);
		return NULL;
	}

	if (!readIntFromFile(&pDate->day, fp, "Error reading day\n"))
	{
		fclose(fp);
		return NULL;
	}
	if (!readIntFromFile(&pDate->month, fp, "Error reading month\n"))
	{
		fclose(fp);
		return NULL;
	}
	if (!readIntFromFile(&pDate->year, fp, "Error reading year\n"))
	{
		fclose(fp);
		return NULL;
	}

	return pDate;
}

void printDate(const Date* pDate)
{
	printf("Date: %d.%d.%d\t", pDate->day, pDate->month, pDate->year);
}