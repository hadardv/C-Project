#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Branch.h"
#include "Company.h"
#include "general.h"
#include "fileHelper.h"


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

int saveBranchToBinaryFile(const Branch* pBranch, FILE* fp) {

	if (!writeIntToFile(pBranch->serialNum, fp, "Error writing serialNum"))
	{
		fclose(fp);
		return 0;
	}
	if (!writeStringToFile(pBranch->name, fp, "Error writing name"))
	{
		fclose(fp);
		return 0;
	}
	if (!writeStringToFile(pBranch->cityLocation, fp, "Error writing cityLocation"))
	{
		fclose(fp);
		return 0;
	}
	if (!writeIntToFile(pBranch->numOfTheaters, fp, "Error writing numOfTheaters"))
	{
		fclose(fp);
		return 0;
	}
	if (!writeIntToFile(pBranch->numOfMovies, fp, "Error writing numOfMovies"))
	{
		fclose(fp);
		return 0;
	}
	if (!writeIntToFile(pBranch->numOfShowTime, fp, "Error writing numOfShowTime"))
	{
		fclose(fp);
		return 0;
	}

	 
	for (int i = 0; i < pBranch->numOfMovies; i++) {
		if (!saveMovieToFile(pBranch->moviesArr[i], fp)) {
			printf("Error writing movie\n");
			fclose(fp);
			return 0;
		}
	}

	for (int i = 0; i < pBranch->numOfTheaters; i++) {
		if (!saveTheaterToFile(&pBranch->theaterArray[i], fp)) {
			printf("Error writing theater\n");
			fclose(fp); 
			return 0;
		}
	}

	for (int i = 0; i < pBranch->numOfShowTime; i++) {
		if (!saveShowTimeToFile(&pBranch->showTimeArray[i], fp)) {
			printf("Error writing showtime\n");
			fclose(fp); 
			return 0;
		}
	}
	return 1;
}

int saveBranchToTxtFile(const Branch* pBranch, FILE* fp)
{
	// Write simple fields with fprintf
	fprintf(fp, "Branch Serial Number: %d\n", pBranch->serialNum); 
	fprintf(fp, "Branch Name: %s\n", pBranch->name); 
	fprintf(fp, "Number Of Theaters: %d\n", pBranch->numOfTheaters); 
	fprintf(fp, "Number Of Movies: %d\n", pBranch->numOfMovies); 
	fprintf(fp, "Number Of Show Times: %d\n", pBranch->numOfShowTime); 

	fprintf(fp, "Movies:\n");
	for (int i = 0; i < pBranch->numOfMovies; i++) {
		fprintf(fp, "\tMovie name: %s\n", pBranch->moviesArr[i]->name);
		for (int j = 0; j < MAX_GENRES; j++)
		{
			if (pBranch->moviesArr[i]->genreArr[j] != -1)
				fprintf(fp, "\tMovie genres: %s ", MovieTypeStr[pBranch->moviesArr[i]->genreArr[j]]);
		}
		fprintf(fp, "Duration: %d\n", pBranch->moviesArr[i]->duration);
	}

	for (int i = 0; i < pBranch->numOfTheaters; i++) {
		fprintf(fp, "\tTheater number: %d\n", pBranch->theaterArray[i].theaterNumber);
		fprintf(fp, "Theater type: %s\n", TheaterTypeStr[pBranch->theaterArray[i].type]);
	}

	for (int i = 0; i < pBranch->numOfShowTime; i++) {
		fprintf(fp, "\tMovie name: %s\n", pBranch->showTimeArray[i].theMovie.name);
		fprintf(fp, "Theater: %d type: %s\n", pBranch->showTimeArray[i].theTheater.theaterNumber, TheaterTypeStr[pBranch->theaterArray[i].type]);
		fprintf(fp, "Date: %d.%d.%d\n", pBranch->showTimeArray[i].date.day, pBranch->showTimeArray[i].date.month, pBranch->showTimeArray[i].date.year); 
		fprintf(fp, "Time: %d:%d\n", pBranch->showTimeArray[i].time.hour, pBranch->showTimeArray[i].time.minuets); 

	}

	
	return 1; // Return success
}


Movie* findAMovie(const Branch* branch)
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
		fgets(movieName, MAX_STR_LEN, stdin); 
		movieName[strcspn(movieName, "\n")] = 0; 
		temp = findMovieByName(branch, movieName);
		if (!temp) printf("There is not such a movie, try again\n");
		} while (temp == NULL);
		return temp;
	}

ShowTime* findAShowTime(const Branch* branch)
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
		if (!temp) 
			printf("There is not such a movie, try again\n");
	} while (temp == NULL);
	return temp;
}

ShowTime* findShowTimeByNum(const Branch* branch, int showTimeNum)
{
	for (int i = 0; i < branch->numOfShowTime; i++)
	{
		if (branch->showTimeArray[i].serialNum == showTimeNum) return &branch->showTimeArray[i];
	}
	return NULL;
}



Movie* findMovieByName(const Branch* branch, const char* name)
{
	for (int i = 0; i < branch->numOfMovies; i++)
	{
		if (!strcmp(branch->moviesArr[i]->name,name)) return branch->moviesArr[i];
	}
	return NULL; 
}

Theater* findATheater(const Branch* branch)
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

Theater* findTheaterByNum(const Branch* branch, const int theaterNum)
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
	printf("\nThe theaters are: \n");
	generalArrayFunction(branch->theaterArray, branch->numOfTheaters, sizeof(Theater), printTheaterV);

}

void printMoviesArr(const Branch* branch)
{
	printf("\nThe Movies are: \n");
	generalArrayFunction(branch->moviesArr, branch->numOfMovies, sizeof(Movie*), printMovieV);

}

void printShowTimeArr(const Branch* branch)
{
	printf("\nThe show times are: \n");
	generalArrayFunction(branch->showTimeArray, branch->numOfShowTime, sizeof(ShowTime), printShowTimeV);
}


void freeBranch(Branch* branch) {
	if (branch == NULL) return;

	// Free the name
	if (branch->name != NULL) {
		free(branch->name);
		branch->name = NULL;
	}

	// Free the city location
	if (branch->cityLocation != NULL) {
		free(branch->cityLocation);
		branch->cityLocation = NULL;
	}

	// Free each Theater in the theaterArray
	if (branch->theaterArray != NULL) {
		freeTheaterArr(branch);
		branch->theaterArray = NULL;
	}

	// Free each Movie pointer in moviesArr
	if (branch->moviesArr != NULL) {
		freeMovieArr(branch);
		branch->moviesArr = NULL;
	}

	// Free each ShowTime in the showTimeArray
	if (branch->showTimeArray != NULL) {
		freeTheaterArr(branch);
		branch->showTimeArray = NULL; 
	}

	free(branch);
}


void freeTheaterArr(Branch* branch)
{
	generalArrayFunction(branch->theaterArray, branch->numOfTheaters, sizeof(Theater), freeTheater);
	
}

void freeShowTimeArr(Branch* branch)
{
	generalArrayFunction(branch->showTimeArray, branch->numOfShowTime, sizeof(ShowTime), freeShowTime);
}

void freeMovieArr(Branch* branch)
{
	generalArrayFunction(branch->moviesArr, branch->numOfMovies, sizeof(Movie*), freeMovie);
	
}





//void readMoviesFromTextfile(Movie* pMovie, FILE* fp)
//{	
//}



