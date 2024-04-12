#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Movie.h"
#include "general.h"
#include "fileHelper.h"
#include "macros.h"



void initMovie(Movie* pMovie,Movie** movieArr,int numOfMovies)
{
	
	int choice = 0;
	int i = 0;
	memset(pMovie->genreArr, -1, sizeof(pMovie->genreArr));
	pMovie->name = getMovieName(movieArr,numOfMovies);
	do {
		pMovie->genreType = getMovieGenre();
		//if (!pMovie->genreType) continue;
		pMovie->genreArr[i] = pMovie->genreType;
		i++;
		printf("A movie can have maximum 2 genres, if you want to add another genre press 0, else press -1\n");
		scanf("%d", &choice);
	} while (!choice && i<2);
	pMovie->duration = setDuration(); 
	pMovie->ageLimit = setAgeLimit(pMovie->genreArr); 
}

eGenre getMovieGenre()
{
		int choice = 0;
		do {
			printf("Enter one of the following types\n");
			for (int i = 0; i < numberOfTypes; i++)
				printf("%d for %s\n", i+1, MovieTypeStr[i]);
			scanf("%d", &choice);
			choice = choice - 1;
		} while (choice < 0 || choice >= numberOfTypes);
	return (eGenre)choice;
}

eGenre convertStringToGenre(const char* genreStr) {
	for (int i = 0; i < numberOfTypes; i++) {
		if (strcmp(genreStr, MovieTypeStr[i]) == 0) {
			return (eGenre)i;
		}
	}
	return -1; // In case the genre is not found, consider handling this error appropriately
}


int	saveMovieToBinaryFile(const Movie* pMovie, FILE* fp)
{
	if (!writeStringToFile(pMovie->name, fp, "Error writing movie name"))
	{
		COLSE_FILE_RETURN_ZERO(fp);
	}

		//fwrite(&pMovie->genreType, sizeof(pMovie->genreType), 1, fp);

		for (int i = 0; i < MAX_GENRES; i++) {
			fwrite(&pMovie->genreArr[i], sizeof(pMovie->genreArr[i]), 1, fp);
		}

		if (!writeIntToFile(pMovie->duration, fp, "Error writing duration"))
		{
			COLSE_FILE_RETURN_ZERO(fp);
		}
		

		return 1;
}

Movie* loadMovieFromBinaryFile(FILE* fp) 
{
	if (!fp) return NULL;

	Movie* pMovie = (Movie*)malloc(sizeof(Movie));
	if (!pMovie) return NULL;

	// Read the movie name
	pMovie->name = readStringFromFile(fp,"Error reading movie name from file\n");
	if (!pMovie->name) {
		free(pMovie);
		return NULL;
	}
	// Initialize genres
	for (int i = 0; i < MAX_GENRES; i++) {
		pMovie->genreArr[i] = -1;
	}

	// Read genres as separate enum values
	int genreIndex;
	for (int i = 0; i < MAX_GENRES; i++) {
		fread(&genreIndex, sizeof(genreIndex), 1, fp);
		if (genreIndex >= 0 && genreIndex < numberOfTypes) {
			pMovie->genreArr[i] = genreIndex;
		}
	}
	pMovie->genreType = pMovie->genreArr[0]; // Assuming the first genre is the primary genre 

	fread(&pMovie->duration, sizeof(pMovie->duration), 1, fp); 
	pMovie->ageLimit = setAgeLimit(pMovie->genreArr); 

	return pMovie; 
}


Movie* loadMovieFromTxtFile(FILE* fp)
{
	char tempN[MAX_STR_LEN];
	char genreStr[MAX_STR_LEN]; 
	int tempDuration=0;
	Movie* pMovie = (Movie*)malloc(sizeof(Movie)); 
	RETURN_NULL(pMovie);
	 
	memset(pMovie->genreArr, -1, sizeof(pMovie->genreArr)); 
	myGets(tempN, MAX_STR_LEN, fp);
	pMovie->name = getDynStr(tempN); 

	// Reading genres line
	if (!myGets(genreStr, MAX_STR_LEN, fp)) { 
		printf("Error reading movie genre\n");
		return NULL;
	}

	// Split genreStr into individual genres and convert them
	char* token = strtok(genreStr, " "); // Splitting by space to get the first genre 
	int genreCount = 0;
	while (token != NULL && genreCount < MAX_GENRES) {
		eGenre tempGenre = convertStringToGenre(token);
		if (tempGenre == -1) {
			printf("Invalid genre: %s\n", token);
			return NULL;
		}
		pMovie->genreArr[genreCount++] = tempGenre;

		token = strtok(NULL, " ");
	}
	if (genreCount > 0) {
		pMovie->genreType = pMovie->genreArr[0]; 
	}


	fscanf(fp, "%d", &pMovie->duration);
	pMovie->ageLimit = setAgeLimit(pMovie->genreArr);

	return pMovie; 

}

char* getMovieName(Movie** movieArr, int numOfMovies)
{
	char* name;
	int flag = 0;
	do {
		name = getStrExactName("Enter the movie name\n");
		RETURN_NULL(name);
		flag = isMovieUnique(movieArr, numOfMovies, name);
	} while (!flag);
	return name;
}

int isMovieUnique(Movie** movieArr, int numOfMovies, char* name)
{
	for (int i = 0; i < numOfMovies; i++)
	{
		if (!strcmp(movieArr[i]->name, name)) return 0;
	}
	return 1;
}

int setAgeLimit(eGenre* genreArr)
{
	int maxAgeLimit = 0 ;
	int tempAgeLimit = 0;
	for (int i = 0; i < MAX_GENRES; i++)
	{
		if (genreArr[i] == 3) // 3 is Horror
			tempAgeLimit = 16;
		else if(genreArr[i] == 5) // 5 is Romance
			tempAgeLimit = 13;
		if (tempAgeLimit > maxAgeLimit) maxAgeLimit = tempAgeLimit;
	}
	return maxAgeLimit;
}

int setDuration()
{
	int duration = 0;
	printf("Enter the duration of the movie\n");
	scanf("%d", &duration);
	return duration;
}

void printMovie(const Movie* pMovie)
{
	printf("\t%s\n", pMovie->name);
	printf("Genres: ");
	printGenres(pMovie->genreArr);
	printf("Duration: %d minuets \tAge Limit: %d years\n", pMovie->duration, pMovie->ageLimit);
}

void printMovieV(void* pMovie)
{
	const Movie* temp = *(Movie**)pMovie;
	printMovie(temp);
}

void printGenres(const eGenre* genreArr)
{
	 
	for (int i = 0; i < MAX_GENRES; i++)
	{
		if (genreArr[i] != -1 ) 
			printf("%s\t",MovieTypeStr[genreArr[i]]); 
	}
}

void freeMovie(Movie* pMovie)
{
	free(pMovie->name);
}
