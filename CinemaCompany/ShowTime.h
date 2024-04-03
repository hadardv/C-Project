#ifndef __SHOWTIME__
#define __SHOWTIME__

#include "Date.h"
#include "Time.h"
#include "Movie.h"
#include "Theater.h"


typedef struct
{
	Date date;
	Time time;
	Movie theMovie; 
	Theater theTheater;

}ShowTime;

void printShowTime(const ShowTime* showTime);

#endif