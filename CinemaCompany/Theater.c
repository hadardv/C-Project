#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Theater.h"
#include "general.h"

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


	// Allocate the rows
	//theater->seats = (int**)calloc(rows, sizeof(int*));
	//if (theater->seats == NULL) return;

	//// Allocate each row
	//for (int i = 0; i < rows; i++) {
	//	theater->seats[i] = (int*)calloc(cols, sizeof(int));
	//	if (theater->seats[i] == NULL) return; 
	//}
	theater->seats = (int**)malloc(rows * sizeof(int*));
	if (theater->seats == NULL) {
		// Handle allocation failure
		return;
	}

	// Allocate columns for each row
	for (int i = 0; i < rows; i++) {
		theater->seats[i] = (int*)calloc(cols, sizeof(int)); // calloc initializes to 0
		if (theater->seats[i] == NULL) {
			// Handle allocation failure
			// Remember to free previously allocated rows before returning
			return;
		}

		theater->maximumCapacity = rows * cols;
		theater->theaterNumber = theaterCount + 1;
	}
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
	} while (!checkIfSeatIsEmpty(theater, wantedRow-1, wantedCol-1));
	
	sprintf(theSeat, "Row: %d, Col: %d", wantedRow, wantedCol);
	theater->seats[wantedRow-1][wantedCol-1] = 1; /// problem is here

	return theSeat; 

}

int checkIfSeatIsEmpty(Theater* theater,int wantedRow,int wantedCol) 
{
	//// need here to check bounds
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
		printf("%d ", col + 1); // Column numbers start from 1
	}
	printf("\n");

	for (int i = 0; i < rows; i++) {
		printf("%d ", i + 1); // Print the row number on the left, starting from 1
		for (int j = 0; j < cols; j++) {
			// Assuming 0 for unoccupied and any other value for occupied seats
			if (theater->seats[i][j] == 0) {
				printf("_ "); // Unoccupied seat
			}
			else {
				printf("X "); // Occupied seat
			}
		}
		printf("\n"); // New line at the end of each row
	}
}



void printTheater(const Theater* theater)
{
	printf("Number of theater: %d\tType of theater: %s\n", theater->theaterNumber, TheaterTypeStr[theater->type]);
}

void freeTheater(Theater* theater)
{
	free(theater->seats); 
	free(theater);  
}
