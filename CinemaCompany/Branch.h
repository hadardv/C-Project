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

Movie* findAMovie(const Branch* branch);
Theater* findATheater(const Branch* branch);
ShowTime* findAShowTime(const Branch* branch);
ShowTime* findShowTimeByNum(const Branch* branch, int showTimeNum);
Movie* findMovieByName(const Branch* branch, const char* name);
Theater* findTheaterByNum(const Branch* branch, const int theaterNum);

int saveBranchToBinaryFile(const Branch* pBranch, FILE* fp);
int saveBranchToTxtFile(const Branch* pBranch, FILE* fp);


void printBranch(const Branch* branch);
void printDataBranch(const Branch* branch);
void printTheaterArr(const Branch* branch);
void printMoviesArr(const Branch* branch);
void printShowTimeArr(const Branch* branch);

void freeBranch(Branch* branch);
void freeTheaterArr(Branch* branch);
void freeMovieArr(Branch* branch);
void freeShowTimeArr(Branch* branch);

#endif 
