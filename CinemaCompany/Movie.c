#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Movie.h"
#include "general.h"



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

char* getMovieName(Movie** movieArr, int numOfMovies)
{
	char* name;
	int flag = 0;
	do {
		name = getStrExactName("Enter the movie name\n");
		if (!name) return 0;
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
	printf("%s\n", pMovie->name);
	printf("Genres: ");
	printGenres(pMovie->genreArr);
	printf("Duration: %d minuets \tAge Limit: %d years\n", pMovie->duration, pMovie->ageLimit);
}

void printGenres(const eGenre* genreArr)
{
	// this function doesn't print action because its 0!!! 
	for (int i = 0; i < MAX_GENRES; i++)
	{
		if (genreArr[i] != -1)
			printf("%s\t",MovieTypeStr[genreArr[i]]); 
	}
}
