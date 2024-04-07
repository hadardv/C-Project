#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Branch.h"
#include "Company.h"
#include "general.h"


void initShowTime(ShowTime* showTime, Branch* branch)
{
	
	Movie* movie = findAMovie(branch); 
	showTime->theMovie = *movie; 
	Theater* theater = findATheater(branch); 
	showTime->theTheater = *theater;  
	getDate(&showTime->date); 
	getTime(&showTime->time); 
	showTime->serialNum = branch->numOfShowTime + 1;

}

Movie* findAMovie(Branch* branch)
{
	if (branch->numOfMovies < 1)
	{
		printf("There are not movies\n");
		return NULL;
	}

	printf("Choose movie from the list, type it's name:\n");
	printMoviesArr(branch);
	Movie* temp = NULL;
	char movieName[MAX_STR_LEN];
	do {
		fgets(movieName, MAX_STR_LEN, stdin); // Use fgets to read the input
		movieName[strcspn(movieName, "\n")] = 0; // Remove the trailing newline character
		temp = findMovieByName(branch, movieName);
		if (!temp) printf("There is not such a movie, try again\n");
		} while (temp == NULL);
		return temp;
	}

ShowTime* findAShowTime(Branch* branch)
{
	if (branch->numOfShowTime < 1)
	{
		printf("There are not Show Times\n");
		return NULL;
	}

	printf("Choose show time from the list, type it's serial num:\n");
	printShowTimeArr(branch);
	ShowTime* temp = NULL;
	int sn;
	do {
		scanf("%d", &sn);
		temp = findShowTimeByNum(branch, sn);
		if (!temp) printf("There is not such a movie, try again\n");
	} while (temp == NULL);
	return temp;
}

ShowTime* findShowTimeByNum(Branch* branch, int showTimeNum)
{
	for (int i = 0; i < branch->numOfShowTime; i++)
	{
		if (branch->showTimeArray[i].serialNum == showTimeNum) return &branch->showTimeArray[i];
	}
	return NULL;
}



Movie* findMovieByName(Branch* branch, char* name) 
{
	for (int i = 0; i < branch->numOfMovies; i++)
	{
		if (!strcmp(branch->moviesArr[i]->name,name)) return branch->moviesArr[i];
	}
	return NULL; 
}

Theater* findATheater(Branch* branch)
{
	if (branch->numOfTheaters < 1)
	{
		printf("There are not Theaters\n");
		return NULL;
	}
	printf("Choose theater from the list, type it's number:\n");
	printTheaterArr(branch);
	Theater* temp = NULL;
	int theaterNum; 
	do {
		scanf("%d", &theaterNum);
		temp = findTheaterByNum(branch, theaterNum);
		if (!temp) printf("There is not such a theater, try again\n");
	} while (temp == NULL);
	return temp;
}

Theater* findTheaterByNum(Branch* branch, int theaterNum)
{
	for (int i = 0; i < branch->numOfTheaters; i++)
	{
		if (branch->theaterArray[i].theaterNumber == theaterNum) return &branch->theaterArray[i];
	}
	return NULL;
}

int getSerialNum()
{
	int sn;
	do {
		printf("Enter serial number for the branch, between 1-999\n");
		scanf("%d",&sn);
	} while (sn < 1 || sn > 999);
	return sn;
}


void printBranch(const Branch* branch)
{
	printf("Serial Number: %d\tName: %s\n", branch->serialNum, branch->name);
}

void printDataBranch(const Branch* branch) {
	printf("\n-----------------\n");
	printBranch(branch);
	printTheaterArr(branch);
	printf("The movies are:\n");
	printMoviesArr(branch);
	printf("\n-----------------\n");
	printShowTimeArr(branch);
}

void printTheaterArr(const Branch* branch)
{
	printf("The theaters are: \n");
	for (int i = 0; i < branch->numOfTheaters; i++)
	{
		printTheater(&branch->theaterArray[i]);
	}

}

void printMoviesArr(const Branch* branch)
{
	for (int i = 0; i < branch->numOfMovies; i++)
	{
		printMovie(branch->moviesArr[i]);
	}
}

void printShowTimeArr(const Branch* branch)
{

	for (int i = 0; i < branch->numOfShowTime; i++)
	{
		printf("The Show Times to the movie are:\n");
		printShowTime(&branch->showTimeArray[i]);
	}
}



void freeBranch(Branch* branch)
{
	free(branch->name);
	free(branch->cityLocation);
}

void freeTheaterArr(Branch* branch)
{
	for (int i = 0; i < branch->numOfTheaters; i++)
	{
		freeTheater(&branch->theaterArray[i]);
	}
	free(branch->theaterArray);
}





//void readMoviesFromTextfile(Movie* pMovie, FILE* fp)
//{	
//}



