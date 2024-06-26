#ifndef __MOVIE__
#define __MOVIE__

#define MAX_GENRES 2 

typedef enum {
	eAction, eDrama, eComedy, eHorror,eFantasy,eRomance,eKids, numberOfTypes
} eGenre;

static const char* MovieTypeStr[numberOfTypes]
= {"Action", "Drama", "Comedy", "Horror","Fantasy","Romance","Kids"};

typedef struct
{
	char* name;
	eGenre genreType;
	eGenre genreArr[MAX_GENRES];
	int duration;
	int ageLimit;
	

}Movie;

void initMovie(Movie* pMovie, Movie** movieArr, int numOfMovies);
eGenre getMovieGenre();
eGenre convertStringToGenre(const char* genreStr);

char* getMovieName(Movie** movieArr, int numOfMovies);
int isMovieUnique(Movie** movieArr, int numOfMovies,char* name);
int setAgeLimit(eGenre* genreArr);
int setDuration();

int	saveMovieToBinaryFile(const Movie* pMovie, FILE* fp);
Movie* loadMovieFromBinaryFile(FILE* fp);
Movie* loadMovieFromTxtFile(FILE* fp);

void printMovie(const Movie* pMovie);
void printMovieV(void* pMovie);
void printGenres(const eGenre* genreArr);
void freeMovie(Movie* pMovie);

#endif 

