#pragma once
#ifndef __MYDATE__
#define __MYDATE__

#define MIN_YEAR 2024

typedef struct
{
	int			day;
	int			month;
	int			year;
}Date;

void	getDate(Date* pDate);
int		checkDate(char* date, Date* pDate);

int		saveDateToBinaryFile(const Date* pDate, FILE* fp);
Date*	loadDateFromTxtFile(FILE* fp);
Date*	loadDateFromBinaryFile(FILE* fp);

void	printDate(const Date* pDate);

#endif
