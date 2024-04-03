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
char* getMovieName(Movie** movieArr, int numOfMovies);
int isMovieUnique(Movie** movieArr, int numOfMovies,char* name);
int setAgeLimit(eGenre* genreArr);
int setDuration();
void printMovie(const Movie* pMovie);
void printGenres(const eGenre* genreArr);
//void doesBestSeller(Movie* pMovie);
//void numOfTickets(Movie* pMovie);

#endif 

