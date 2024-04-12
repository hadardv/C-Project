#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Branch.h"
#include "Company.h"
#include "general.h"
#include "fileHelper.h"
#include "macros.h"


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
		COLSE_FILE_RETURN_ZERO(fp);
	}
	if (!writeStringToFile(pBranch->name, fp, "Error writing name"))
	{
		COLSE_FILE_RETURN_ZERO(fp);
	}
	if (!writeStringToFile(pBranch->cityLocation, fp, "Error writing cityLocation"))
	{
		COLSE_FILE_RETURN_ZERO(fp);
	}
	if (!writeIntToFile(pBranch->numOfTheaters, fp, "Error writing numOfTheaters"))
	{
		COLSE_FILE_RETURN_ZERO(fp);
	}
	if (!writeIntToFile(pBranch->numOfMovies, fp, "Error writing numOfMovies"))
	{
		COLSE_FILE_RETURN_ZERO(fp);
	}
	if (!writeIntToFile(pBranch->numOfShowTime, fp, "Error writing numOfShowTime"))
	{
		COLSE_FILE_RETURN_ZERO(fp);
	}

	 
	for (int i = 0; i < pBranch->numOfMovies; i++) {
		if (!saveMovieToBinaryFile(pBranch->moviesArr[i], fp)) {
			printf("Error writing movie\n");
			COLSE_FILE_RETURN_ZERO(fp);
		}
	}

	for (int i = 0; i < pBranch->numOfTheaters; i++) {
		if (!saveTheaterToBinaryFileCompressed(&pBranch->theaterArray[i], fp)) {
			printf("Error writing theater\n");
			COLSE_FILE_RETURN_ZERO(fp);
		}

	}

	for (int i = 0; i < pBranch->numOfShowTime; i++) {
		if (!saveShowTimeToBinaryFile(&pBranch->showTimeArray[i], fp)) {
			printf("Error writing showtime\n");
			COLSE_FILE_RETURN_ZERO(fp);
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
		fprintf(fp, "Movie name: %s\n", pBranch->moviesArr[i]->name);
		for (int j = 0; j < MAX_GENRES; j++)
		{
			if (pBranch->moviesArr[i]->genreArr[j] != -1)
				fprintf(fp, "Movie genres: %s ", MovieTypeStr[pBranch->moviesArr[i]->genreArr[j]]);
		}
		fprintf(fp, "Duration: %d\n", pBranch->moviesArr[i]->duration);
	}

	for (int i = 0; i < pBranch->numOfTheaters; i++) {
		fprintf(fp, "Theater number: %d\n", pBranch->theaterArray[i].theaterNumber);
		fprintf(fp, "Theater type: %s\n", TheaterTypeStr[pBranch->theaterArray[i].type]);
	}

	for (int i = 0; i < pBranch->numOfShowTime; i++) {
		fprintf(fp, "Movie name: %s\n", pBranch->showTimeArray[i].theMovie.name);
		fprintf(fp, "Theater: %d type: %s\n", pBranch->showTimeArray[i].theTheater.theaterNumber, TheaterTypeStr[pBranch->theaterArray[i].type]);
		fprintf(fp, "Date: %d.%d.%d\n", pBranch->showTimeArray[i].date.day, pBranch->showTimeArray[i].date.month, pBranch->showTimeArray[i].date.year); 
		fprintf(fp, "Time: %d:%d\n", pBranch->showTimeArray[i].time.hour, pBranch->showTimeArray[i].time.minuets); 

	}

	
	return 1; // Return success
}

int loadBranchFromTxtFile(Branch* pBranch, FILE* fp)
{
	Movie* tempMovie;
	int tempSN=0;
	char tempName[MAX_STR_LEN];
	char tempLocation[MAX_STR_LEN];
	int tempNumTheaters = 0; 
	int tempNumMovies = 0; 
	int tempNumShowTimes = 0; 

	RETURN_ZERO(pBranch); 

	fscanf(fp, "%d", &pBranch->serialNum);
	myGets(tempName, MAX_STR_LEN, fp);
	pBranch->name = getDynStr(tempName); 
	myGets(tempLocation, MAX_STR_LEN, fp);
	pBranch->cityLocation = getDynStr(tempLocation);
	fscanf(fp, "%d", &pBranch->numOfTheaters);
	fscanf(fp, "%d", &pBranch->numOfMovies);
	fscanf(fp, "%d", &pBranch->numOfShowTime);

	pBranch->moviesArr = (Movie**)malloc(pBranch->numOfMovies * sizeof(Movie*));
	RETURN_ZERO(pBranch->moviesArr);
	pBranch->theaterArray = (Theater*)malloc(pBranch->numOfTheaters * sizeof(Theater));
	RETURN_ZERO(pBranch->theaterArray);
	pBranch->showTimeArray = (ShowTime*)malloc(pBranch->numOfShowTime * sizeof(ShowTime)); 
	RETURN_ZERO(pBranch->showTimeArray);


	for (int i = 0; i < pBranch->numOfMovies; i++)
	{
		tempMovie = loadMovieFromTxtFile(fp);
		if (!tempMovie) {
			// Free all previously allocated Movies
			for (int j = 0; j < i; j++) { 
				free(pBranch->moviesArr[j]->name); // Assuming 'name' was dynamically allocated 
				free(pBranch->moviesArr[j]); 
			}
			free(pBranch->moviesArr); // Free the array itself 
			return 0; 
		}
		pBranch->moviesArr[i] = tempMovie; 
		
	}

	for (int i = 0; i < pBranch->numOfTheaters; i++)
	{

		Theater* tempTheater = loadTheaterFromTxtFile(fp);
		RETURN_AND_FREE(pBranch->theaterArray);
	
		pBranch->theaterArray[i] = *tempTheater;
		pBranch->theaterArray[i].seats = setTheaterSeats(tempTheater);
		free(tempTheater); 
	}

	for (int i = 0; i < pBranch->numOfShowTime; i++) 
	{

		ShowTime* tempShowTime = loadShowTimeFromTxtFile(pBranch, fp);
		if (!tempShowTime)
		{
			free(pBranch->showTimeArray);
			return 0;
		}
		pBranch->showTimeArray[i] = *tempShowTime;  
		free(tempShowTime);
	}

	return 1;
}


ShowTime* loadShowTimeFromTxtFile(Branch* pBranch, FILE* fp)
{
	char tempMovieName[MAX_STR_LEN];
	char* tempName;
	int serialNum=0;
	Date tempDate;
	Time tempTime;
	int tempTheaterNum = 0;
	ShowTime* pShowTime = (ShowTime*)malloc(sizeof(ShowTime));
	RETURN_NULL(pShowTime);

	fscanf(fp, "%d", &pShowTime->serialNum); 

	myGets(tempMovieName, MAX_STR_LEN, fp);
	tempName = getDynStr(tempMovieName);
	pShowTime->theMovie = *findMovieByName(pBranch,tempName);

	fscanf(fp, "%d", &tempTheaterNum);
	pShowTime->theTheater = *findTheaterByNum(pBranch, tempTheaterNum);

	skipLine(fp);   
	skipLine(fp);  
	 tempDate = *loadDateFromTxtFile(fp);
	 tempTime = *loadTimeFromTxtFile(fp);

	 pShowTime->date = tempDate; 
	 pShowTime->time = tempTime;

	 return pShowTime;

}

int loadBranchFromBinaryFile(Branch* pBranch, FILE* fp)
{
	if (!pBranch || !fp) return 0;

	Movie* tempMovie; 

	if (!readIntFromFile(&pBranch->serialNum, fp, "Error reading serial number\n"))
	{
		fclose(fp);
		return 0;
	}

	pBranch->name = readStringFromFile(fp, "Error reading branch name\n");
	if (!pBranch->name) 
	{
		fclose(fp); 
		return 0; 
	}
	pBranch->cityLocation = readStringFromFile(fp, "Error reading branch city location\n");
	if (!pBranch->cityLocation)
	{
		fclose(fp); 
		return 0;
	}

	if (!readIntFromFile(&pBranch->numOfTheaters, fp, "Error reading number of theaters\n"))
	{
		fclose(fp);
		return 0;
	}
	if (!readIntFromFile(&pBranch->numOfMovies, fp, "Error reading number of movies\n"))
	{
		fclose(fp);
		return 0;
	}
	if (!readIntFromFile(&pBranch->numOfShowTime, fp, "Error reading number of show times\n"))
	{
		fclose(fp);
		return 0;
	}

	pBranch->moviesArr = (Movie**)malloc(pBranch->numOfMovies * sizeof(Movie*));
	RETURN_ZERO(pBranch->moviesArr);

	pBranch->theaterArray = (Theater*)malloc(pBranch->numOfTheaters * sizeof(Theater));
	RETURN_ZERO(pBranch->theaterArray);

	pBranch->showTimeArray = (ShowTime*)malloc(pBranch->numOfShowTime * sizeof(ShowTime));
	RETURN_ZERO(pBranch->showTimeArray);

	for (int i = 0; i < pBranch->numOfMovies; i++) { 
		tempMovie = loadMovieFromBinaryFile(fp);
		if (!tempMovie) {
			// Free all previously allocated Movies
			for (int j = 0; j < i; j++) {
				free(pBranch->moviesArr[j]->name); // Assuming 'name' was dynamically allocated 
				free(pBranch->moviesArr[j]);
			}
			free(pBranch->moviesArr); // Free the array itself 
			return 0;
		}
		pBranch->moviesArr[i] = tempMovie;
	}

	for (int i = 0; i < pBranch->numOfTheaters; i++)
	{
		Theater* tempTheater = readTheaterFromBinaryFileCompressed(fp);
		RETURN_AND_FREE(pBranch->theaterArray); 

		pBranch->theaterArray[i] = *tempTheater; 
		pBranch->theaterArray[i].seats = setTheaterSeats(tempTheater);
		free(tempTheater); 
	}

	for (int i = 0; i < pBranch->numOfShowTime; i++) 
	{

		ShowTime* tempShowTime = loadShowTimeFromBinaryFile(pBranch, fp);
		if (!tempShowTime) 
		{
			free(pBranch->showTimeArray); 
			return 0;
		}
		pBranch->showTimeArray[i] = *tempShowTime; 
		free(tempShowTime); 
	}

	return 1;
}

ShowTime* loadShowTimeFromBinaryFile(Branch* pBranch, FILE* fp)
{
	if (!fp || !pBranch) return NULL; 

	ShowTime* pShowTime = (ShowTime*)malloc(sizeof(ShowTime)); 
	if (!pShowTime) return NULL; 
	char* tempName = (char*)malloc(sizeof(char)); 

	if (!readIntFromFile(&pShowTime->serialNum, fp, "Error reading show time serial number from file"))
	{
		fclose(fp); 
		return 0;
	}
	
	tempName = readStringFromFile(fp, "Error reading movie name from file\n");
	if (!tempName) {
		free(pShowTime);
		return NULL; 
	}

	// Find the movie by name within the branch
	pShowTime->theMovie = *findMovieByName(pBranch, tempName);
	free(tempName); // Free the temporary movie name buffer 

	// Read theater number and find the theater within the branch
	int theaterNum;
	fread(&theaterNum, sizeof(theaterNum), 1, fp);
	pShowTime->theTheater = *findTheaterByNum(pBranch, theaterNum);

	// Read date and time directly
	pShowTime->date = *loadDateFromBinaryFile(fp);
	pShowTime->time = *loadTimeFromBinaryFile(fp);

	return pShowTime;
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

	// Free each Theater in the theaterArray if there is
	if (branch->theaterArray != NULL && branch->numOfTheaters>0) {
		freeTheaterArr(branch);
		branch->theaterArray = NULL;
	}

	// Free each Movie pointer in moviesArr
	if (branch->moviesArr != NULL && branch->numOfMovies > 0) {
		freeMovieArr(branch);
		branch->moviesArr = NULL;
	}

	// Free each ShowTime in the showTimeArray
	if (branch->showTimeArray != NULL && branch->numOfShowTime > 0) {
		freeShowTimeArr(branch);
		branch->showTimeArray = NULL; 
	}

	free(branch);
}


void freeTheaterArr(Branch* branch)
{
	//generalArrayFunction(branch->theaterArray, branch->numOfTheaters, sizeof(Theater), freeTheater);
	for (int i = 0; i < branch->numOfTheaters; i++) {
		freeTheater(&branch->theaterArray[i]); 
	}
	// After all theaters have been freed, free the theater array itself.
	free(branch->theaterArray);
}

void freeShowTimeArr(Branch* branch)
{
	generalArrayFunction(branch->showTimeArray, branch->numOfShowTime, sizeof(ShowTime), freeShowTime);
}

void freeMovieArr(Branch* branch)
{
	generalArrayFunction(branch->moviesArr, branch->numOfMovies, sizeof(Movie*), freeMovie);
	
}



