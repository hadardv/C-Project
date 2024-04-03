#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include "Company.h"
#include "general.h"


void initCompany(Company* comp)
{
	printf("--------------------\n");
	comp->name = getStrExactName("Enter Company name:\n");
	if (!L_init(&comp->branchList)) return ;
	comp->numOfBranches = 0; 
}

void initBranch(Branch* branch, Company* pComp)
{
	Branch* pBranchSN; 
	Branch* pBranchCity;
	do {
		branch->serialNum = getSerialNum();
		pBranchSN = findBranchBySN(pComp, branch->serialNum);
	} while (pBranchSN != NULL);

	do {
		branch->cityLocation = getStrExactName("Enter city location of the branch\n");
		pBranchCity = findBranchByCity(pComp, branch->cityLocation);
	} while (pBranchCity != NULL || !isAllLettersOrSpaces(branch->cityLocation));
	branch->name = setName(branch, pComp);
	branch->moviesArr = NULL;
	branch->theaterArray = NULL;
	branch->showTimeArray = NULL;
	branch->numOfTheaters = 0;
	branch->numOfMovies = 0;
}


int addBranch(Company* comp) {
	Branch* pBranch = (Branch*)malloc(sizeof(Branch));
	if (!pBranch) return 0;
	initBranch(pBranch, comp);

	if (!L_insert(&(comp->branchList.head), pBranch)) { 
		free(pBranch); 
		return 0;
	}
	L_print(&comp->branchList, printBranch);
	return 1;

}

char* setName(Branch* branch, Company* pComp)
{
	int totalLength = (int)strlen(pComp->name) + (int)strlen(branch->cityLocation) + 2;
	
	char* tempName = malloc(totalLength * sizeof(char));
	if (tempName == NULL) return NULL;
	 
	strcpy(tempName, pComp->name); 
	strcat(tempName, " ");
	strcat(tempName, branch->cityLocation); 
	 
	return tempName; 
}


int compareBranchSerialNum(const void* branch, const void* serialNum) {
	const Branch* pBranch = (Branch*)branch;
	const int sn = *(int*)serialNum;

	if (pBranch->serialNum < sn) return -1;
	if (pBranch->serialNum > sn) return 1; 
	return 0; // equal
		
}

int compareBranchCity(const void* branch, const void* city) {
	const Branch* pBranch = (Branch*)branch;
	const char* pCity = (char*)city;
	return strcmp(pBranch->cityLocation, pCity);
}

Branch* findBranchByCity(Company* comp, char* city)
{
	NODE* node = L_find(comp->branchList.head.next, &city, compareBranchCity); 
	if (node != NULL) { 
		return (Branch*)node->key; // If the node is found, return the branch  
	}
	else {
		return NULL; // If the node is not found, return NULL  
	}
}


Branch* findBranchBySN(Company* comp, int serialNumber) {
	NODE* node = L_find(comp->branchList.head.next, &serialNumber, compareBranchSerialNum);
	if (node != NULL) { 
		return (Branch*)node->key; // If the node is found, return the branch 
	}
	else {
		return NULL; // If the node is not found, return NULL 
	}
}

Branch* findABranch(Company* comp) {
	printf("Choose a branch from the list, type its serial number\n");
	printCompany(comp);
	Branch* temp = NULL;
	char input[256]; // Buffer to store the input
	int sn;

	do {
		if (fgets(input, sizeof(input), stdin) == NULL) { 
			return NULL; 
		}

		if (sscanf(input, "%d", &sn) == 1) { 
			temp = findBranchBySN(comp, sn);
			if (!temp) {
				printf("There is not such a branch, try again\n");
			}
		}
		else {
			printf("Invalid input. Please enter a valid serial number.\n");
		}
	} while (temp == NULL);

	return temp;
}

int addTheater(Company* comp)
{
	if (comp->branchList.head.next == NULL)
	{
		printf("There are not enough branches to add a theater\n");
		return 0;
	}

	Theater* pTheater = (Theater*)calloc(1, sizeof(Theater));
	if (!pTheater) return 0;

	Branch* pBranch = findABranch(comp); 

	initTheater(pTheater, pBranch->theaterArray, pBranch->numOfTheaters);


	pBranch->theaterArray = (Theater*)realloc(pBranch->theaterArray, (pBranch->numOfTheaters + 1) * sizeof(Theater));
	if (!pBranch->theaterArray)
	{
		free(pTheater); 
		return 0;
	}
	pBranch->theaterArray[pBranch->numOfTheaters] = *pTheater;
	pBranch->numOfTheaters++;
	printTheaterArr(pBranch);
	return 1;
}


int addMovie(Company* comp)
{
	Branch* pBranch = findABranch(comp);

	if (pBranch->moviesArr == NULL)
	{
		pBranch->numOfMovies = 0;
	}

	if (pBranch->numOfTheaters < 1)
	{
		printf("There are not enough Theaters to add a movie\n");
		return 0;
	}

	size_t newSize = (size_t)(pBranch->numOfMovies + 1) * sizeof(Movie*);
	Movie** temp = realloc(pBranch->moviesArr, newSize);
	if (!temp) {
		printf("Failed to allocate memory for new movie.\n");
		return 0;
	} 

	pBranch->moviesArr = temp;
	pBranch->moviesArr[pBranch->numOfMovies] = (Movie*)malloc(sizeof(Movie));
	if (!pBranch->moviesArr[pBranch->numOfMovies]) {
		printf("Failed to allocate memory for movie details.\n");
		return 0;
	}
	Movie* pMovie = pBranch->moviesArr[pBranch->numOfMovies];  // Pointer to the new movie
	initMovie(pMovie, pBranch->moviesArr, pBranch->numOfMovies);
	pBranch->numOfMovies++;
	//pBranch->moviesArr[pBranch->numOfMovies] = pMovie; 
	return 1; 
}

int addShowTime(Company* comp)
{ 
	Branch* pBranch = findABranch(comp);

	if (pBranch->showTimeArray == NULL)
	{
		//pBranch->showTimeArray = NULL;
		pBranch->numOfShowTime = 0;
	}

	size_t newSize = (size_t)(pBranch->numOfShowTime + 1) * sizeof(ShowTime);  
	ShowTime* temp = realloc(pBranch->showTimeArray, newSize);	  
	if (!temp) { 
		printf("Failed to allocate memory for new show time.\n");
		return 0;
	}
	pBranch->showTimeArray = temp;  

	ShowTime* pShowTime = &pBranch->showTimeArray[pBranch->numOfShowTime]; 
	initShowTime(pShowTime, pBranch);
	pBranch->showTimeArray[pBranch->numOfShowTime] = *pShowTime; 
	pBranch->numOfShowTime++;
	return 1;
}

void printCompany(Company* comp) {
	printf("%s\n", comp->name);
	printf("------------------\n");
	NODE* current = comp->branchList.head.next;
	while (current != NULL) {
		printBranch((Branch*)current->key); 
		current = current->next;
	}
}

void printSpecificBranch(Company* comp)
{
	Branch* pBranch = findABranch(comp);
	printDataBranch(pBranch); 
}

void freeCompany(Company* comp) {
	free(comp->name);
	L_free(&comp->branchList, freeBranch); 
}
