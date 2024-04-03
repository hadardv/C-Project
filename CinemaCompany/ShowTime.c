#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ShowTime.h"

void printShowTime(const ShowTime* showTime)
{
	printMovie(&showTime->theMovie);
	printTheater(&showTime->theTheater);
	printDate(&showTime->date);
	printTime(&showTime->time);
}


