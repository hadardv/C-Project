#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Theater.h"
#include "general.h"
#include "fileHelper.h"
#include "macros.h"

void initTheater(Theater* theater, Theater* theaterArr, int theaterCount)
{
	int rows=0, cols=0;
	theater->type = getTheaterType();
	if (!(strcmp(TheaterTypeStr[theater->type], "Regular")))
	{
		rows = 10; cols = 10;
	}

	if (!(strcmp(TheaterTypeStr[theater->type], "VIP")))
	{
		rows = 5; cols = 5;
	}

	if (!(strcmp(TheaterTypeStr[theater->type], "3D")))
	{
		rows = 7; cols = 7;
	}

	theater->seats = (int**)malloc(rows * sizeof(int*));
	if (theater->seats == NULL) {
		return;
	}

	// Allocate columns for each row
	for (int i = 0; i < rows; i++) {
		theater->seats[i] = (int*)calloc(cols, sizeof(int)); // calloc initializes to 0
		if (theater->seats[i] == NULL) {
			return;
		}
		
		theater->maximumCapacity = rows * cols;
		theater->theaterNumber = theaterCount + 1;

	}
}

int** setTheaterSeats(Theater* theater)
{
	int rows = 0, cols = 0;
	if (!(strcmp(TheaterTypeStr[theater->type], "Regular")))
	{
		rows = 10; cols = 10;
	}

	if (!(strcmp(TheaterTypeStr[theater->type], "VIP")))
	{
		rows = 5; cols = 5;
	}

	if (!(strcmp(TheaterTypeStr[theater->type], "3D")))
	{
		rows = 7; cols = 7;
	}

	theater->seats = (int**)malloc(rows * sizeof(int*));
	if (theater->seats == NULL) {
		return NULL; 
	}

	// Allocate columns for each row
	for (int i = 0; i < rows; i++) {
		theater->seats[i] = (int*)calloc(cols, sizeof(int)); // calloc initializes to 0
		if (theater->seats[i] == NULL) {
			return NULL; 
		}
	}
	return theater->seats;
}

void setCapacity(Theater* pTheater)
{
	int rows = 0, cols = 0;
	if (!(strcmp(TheaterTypeStr[pTheater->type], "Regular")))
	{
		rows = 10; cols = 10;
	}

	if (!(strcmp(TheaterTypeStr[pTheater->type], "VIP")))
	{
		rows = 5; cols = 5;
	}

	if (!(strcmp(TheaterTypeStr[pTheater->type], "3D")))
	{
		rows = 7; cols = 7;
	}
	pTheater->maximumCapacity = rows * cols;
}

eTheaterType convertStringToTheaterType(const char* typeStr) {
	for (int i = 0; i < eNumOfTypes; i++) {
		if (strcmp(typeStr, TheaterTypeStr[i]) == 0) {
			return (eTheaterType)i;
		}
	}
	return -1; // Indicating failure to find a match
}

int saveTheaterToBinaryFileCompressed(const Theater* pTheater, FILE* fp)
{
	
	BYTE data[1] = { 0 };
	data[0] = pTheater->theaterNumber << 2 | pTheater->type;

	if (fwrite(&data, sizeof(BYTE), 1, fp) != 1)
		return 0;
	return 1;
}

Theater* readTheaterFromBinaryFileCompressed(FILE* fp)
{
	Theater* pTheater = (Theater*)malloc(sizeof(Theater));
	BYTE data[1] = { 0 };

	if (fread(&data, sizeof(BYTE), 1, fp) != 1)
		return NULL;

	// Extract the theater type from the 2 least significant bits
	pTheater->type = (eTheaterType)(data[0] & 0x03); // Mask with 0b00000011 to get the last 2 bits 

	// Extract the theater number from the 6 most significant bits
	pTheater->theaterNumber = (data[0] >> 2) & 0x3F; // Shift right by 2 bits and mask with 0b00111111

	return pTheater;
}


Theater* loadTheaterFromTxtFile(FILE* fp)
{
	char typeStr[MAX_STR_LEN];
	Theater* pTheater = (Theater*)malloc(sizeof(Theater));
	if (!pTheater)
		return NULL;

	fscanf(fp, "%d", &pTheater->theaterNumber); 
	fgets(typeStr, sizeof(typeStr), fp); // Dummy read to consume the rest of the line 

	// Read the theater type as a string
	if (fgets(typeStr, sizeof(typeStr), fp) == NULL) {
		printf("Error reading theater type\n");
		return NULL;
	}
	typeStr[strcspn(typeStr, "\n")] = 0;
	eTheaterType tempType = convertStringToTheaterType(typeStr); 
	if (tempType == -1) { 
		printf("Invalid theater type: %s\n", typeStr); 
		return NULL;
	}
	pTheater->type = tempType;
	setCapacity(pTheater);

	return pTheater;
}

eTheaterType convertIntToTheaterType(int typeInt) {
	if (typeInt >= 0 && typeInt < eNumOfTypes) {
		return (eTheaterType)typeInt;
	}
	else {
		return -1; // Indicate an invalid type 
	}
}

Theater* loadTheaterFromBinaryFile(FILE* fp)
{
	if (!fp) return NULL;

	Theater* pTheater = (Theater*)malloc(sizeof(Theater));
	if (!pTheater) return NULL;

	if (!readTheaterFromBinaryFileCompressed(fp)) 
	{
		fclose(fp);
		return NULL;
	}

	
	setCapacity(pTheater); 

	return pTheater;
}


char* setSeat(Theater* theater)
{
	int wantedRow;
	int wantedCol; 
	char* theSeat=malloc(20 * sizeof(char));
	if (theSeat == NULL) { 
		return NULL;
	}
	do {
		printf("Choose a seat, type desired row and col \n");
		printSeatMap(theater);
		scanf("%d %d", &wantedRow, &wantedCol);
	} while (!checkIfSeatIsEmpty(theater, wantedRow, wantedCol));
	
	sprintf(theSeat, "Row: %d, Col: %d", wantedRow, wantedCol);
	theater->seats[wantedRow-1][wantedCol-1] = 1; 

	return theSeat; 

}

int checkIfSeatIsEmpty(Theater* theater,int wantedRow,int wantedCol) 
{
	int rows = (int)sqrt(theater->maximumCapacity);
	int cols = rows;
	if (theater->seats[wantedRow-1][wantedCol-1] == 0)
		return 1; // Unoccupied seat

	printf("Seat is taken\n");
	return 0; //occupied seat
			
}


eTheaterType getTheaterType() 
{
	int choice = 0;
	do {
		printf("Enter one of the following types\n");
		for (int i = 0; i < eNumOfTypes; i++)
			printf("%d for %s\n", i, TheaterTypeStr[i]);
		scanf("%d", &choice);
	} while (choice < 0 || choice >= eNumOfTypes);
	return (eTheaterType)choice;
}

void printSeatMap(const Theater* theater) {
	if (theater == NULL || theater->seats == NULL) {
		printf("Theater or seats are not initialized.\n");
		return;
	}

	int rows = (int)sqrt(theater->maximumCapacity);
	int cols = rows;

	printf("Seat Map for Theater %d (%s):\n  ", theater->theaterNumber, TheaterTypeStr[theater->type]);

	// Print column headers
	for (int col = 0; col < cols; col++) {
		printf("%d ", col + 1); 
	}
	printf("\n");

	for (int i = 0; i < rows; i++) {
		printf("%d ", i + 1); 
		for (int j = 0; j < cols; j++) {
			
			if (theater->seats[i][j] == 0) {
				printf("_ "); // Unoccupied seat
			}
			else if(theater->seats[i][j] == 1) {
				printf("X "); // Occupied seat
			}
		}
		printf("\n"); 
	}
}



void printTheater(const Theater* theater)
{
	printf("Number of theater: %d\tType of theater: %s\n", theater->theaterNumber, TheaterTypeStr[theater->type]);
}

void printTheaterV(void* val)
{
	printTheater((const Theater*)val);
}

void freeTheater(Theater* theater)
{

	/*free(theater->seats);  
	free(theater); */ 

	// Assuming 'seats' is a dynamically allocated 2D array.
	if (theater->seats != NULL) { 
		//for (int i = 0; i < theater->maximumCapacity; i++) { 
		//	if (&theater->seats[i] != NULL) { 
		//		free(&theater->seats[i]); // Free each row of seats .
		//	}
		//}
		free(theater->seats); // Free the array of pointers to rows. 
	theater->seats = NULL; 

	}
}
