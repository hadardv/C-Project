#ifndef __THEATER__
#define __THEATER__


typedef enum {
	eVIP, eRegular,e3D, eNumOfTypes
} eTheaterType;

static const char* TheaterTypeStr[eNumOfTypes]
= { "VIP", "Regular", "3D" };



typedef struct
{
	int theaterNumber;
	int maximumCapacity;
	int* seats;
	eTheaterType	type; 
}Theater;

void initTheater(Theater* theater,Theater* theaterArr, int theaterCount);
eTheaterType getTheaterType();
void printTheater(const Theater* theater);
void freeTheater(Theater* theater);

#endif 
