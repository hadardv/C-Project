#ifndef __THEATER__
#define __THEATER__

typedef unsigned char BYTE;

typedef enum {
	eVIP, eRegular,e3D, eNumOfTypes
} eTheaterType;

static const char* TheaterTypeStr[eNumOfTypes]
= { "VIP", "Regular", "3D" };



typedef struct
{
	int theaterNumber;
	int maximumCapacity;
	int** seats;
	eTheaterType	type; 
}Theater;

void initTheater(Theater* theater,Theater* theaterArr, int theaterCount);
eTheaterType getTheaterType();
eTheaterType convertStringToTheaterType(const char* typeStr);
void setCapacity(Theater* pTheater);
int** setTheaterSeats(Theater* theater);

char* setSeat(Theater* theater);
int checkIfSeatIsEmpty(Theater* theater, int wantedRow, int wantedCol);
eTheaterType convertIntToTheaterType(int typeInt);

//int	saveTheaterToBinaryFile(const Theater* pTheater, FILE* fileName);
Theater* loadTheaterFromTxtFile(FILE* fp);
Theater* loadTheaterFromBinaryFile(FILE* fp);
int saveTheaterToBinaryFileCompressed(const Theater* pTheater, FILE* fp);
Theater* readTheaterFromBinaryFileCompressed(FILE* fp);


void printTheater(const Theater* theater);
void printTheaterV(void* val);
void printSeatMap(const Theater* theater);
void freeTheater(Theater* theater);

#endif 
