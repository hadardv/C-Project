#ifndef __SHOWTIME__
#define __SHOWTIME__

#include "Date.h"
#include "Time.h"
#include "Movie.h"
#include "Theater.h"



typedef struct
{
	int serialNum;
	Date date;
	Time time;
	Movie theMovie; 
	Theater theTheater;
	

}ShowTime;

void printShowTime(const ShowTime* showTime);
void printShowTimeV(void* val);

int	saveShowTimeToBinaryFile(const ShowTime* pShowTime, FILE* fp);

void freeShowTime(ShowTime* showTime);

#endif