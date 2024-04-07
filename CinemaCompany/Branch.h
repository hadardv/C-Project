#ifndef __BRANCH__
#define __BRANCH__

#include "Theater.h"
#include "Movie.h"
#include "ShowTime.h"


typedef struct
{
	int serialNum;
	char* name;
	char* cityLocation;
	Theater* theaterArray;
	int numOfTheaters;
	Movie** moviesArr;
	int numOfMovies;
	ShowTime* showTimeArray;
	int numOfShowTime;

}Branch;

void initShowTime(ShowTime* showTime, Branch* branch);
int getSerialNum();
Movie* findAMovie(Branch* branch);
Theater* findATheater(Branch* branch);
ShowTime* findAShowTime(Branch* branch);
ShowTime* findShowTimeByNum(Branch* branch, int showTimeNum);
Movie* findMovieByName(Branch* branch, char* name);
Theater* findTheaterByNum(Branch* branch, int theaterNum);
//void readMoviesFromTextfile(Movie* pMovie, FILE* fp);
void printBranch(const Branch* branch);
void printDataBranch(const Branch* branch);
void printTheaterArr(const Branch* branch);
void printMoviesArr(const Branch* branch);
void printShowTimeArr(const Branch* branch);
void freeBranch(Branch* branch);
void freeTheaterArr(Branch* branch);
//void freeMovieArr(Branch* branch);

#endif 
