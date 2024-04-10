#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include "Company.h"
#include "general.h"
#include "fileHelper.h"
#include "macros.h"


void initCompany(Company* comp)
{
	printf("--------------------\n");
	comp->name = getStrExactName("Enter Company name:\n");
	if (!L_init(&comp->branchList)) return ; 
	comp->ticketSales = NULL;
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
	branch->numOfShowTime = 0;
}

int initTicket(Ticket* pTicket,Company* comp,Branch* pBranch)
{
	initCostumer(&pTicket->theCostumer); 
	int choice=0;
	do {
		pTicket->theShowTime = chooseShowTime(comp, pBranch);
		if (&pTicket->theShowTime == NULL)
		{
			return 0;
		}
		if (!checkAgeLimit(pTicket))
		{
			printf("To cancel the order press -1,to choose another show time press 1\n");
			scanf("%d", &choice);
			if (choice == -1)
				return 0;
		}
	} while (choice == 1);
	setPrice(pTicket);
	pTicket->seatNum = setSeat(&pTicket->theShowTime.theTheater);
	return 1;
}

int saveCompanyToBinaryFile(const Company* comp, const char* fileName)
{
	FILE* fp;

	fp = fopen(fileName, "w");
	RETURN_ZERO(fp);
	

	fprintf(fp, "%s\n", comp->name);
	 
	int count = getBranchescount(comp);
	fprintf(fp, "%d\n", count); 
	if (count > 0)
	{
		NODE* pN = comp->branchList.head.next; //first Node

		Branch* pTemp; 
		while (pN != NULL) 
		{
			pTemp = (Branch*)pN->key ;
			if (!saveBranchToBinaryFile(pTemp, fp))
			{
				printf("Error write branch\n");
				fclose(fp);
				return 0;
			}
			pN = pN->next;
		}
	}
	fclose(fp); 
	return 1;

}

int saveCompanyToTxtFile(const Company* comp, const char* fileName)
{
	FILE* fp;

	fp = fopen(fileName, "w");
	
	RETURN_ZERO(fp);


	fprintf(fp, "%s\n", comp->name);

	int count = getBranchescount(comp);
	fprintf(fp, "%d\n", count);
	if (count > 0)
	{
		NODE* pN = comp->branchList.head.next; //first Node

		Branch* pTemp;
		while (pN != NULL)
		{
			pTemp = (Branch*)pN->key;
			if (!saveBranchToTxtFile(pTemp, fp))
			{
				printf("Error write branch\n");
				fclose(fp);
				return 0;
			}
			pN = pN->next;
		}
	}
	fclose(fp);
	return 1;

}

int loadCompanyFromTxtFile(Company* comp, const char* fileName)
{
	FILE* fp; 

	fp = fopen(fileName, "r");
	RETURN_ZERO(fp);
	
	L_init(&comp->branchList); 
	int count;
	char compName[MAX_STR_LEN];

	myGets(compName, MAX_STR_LEN, fp); 
	comp->name = getDynStr(compName); 

	fscanf(fp, "%d", &count); 
	//clean the buffer
	fgetc(fp); 

	Branch* pBranch;
	for (int i = 0; i < count; i++) 
	{
		pBranch = (Branch*)calloc(1, sizeof(Branch)); 
		if (!pBranch)
			break;
		if (!loadBranchFromTxtFile(pBranch, fp)) 
		{
			printf("Error loading Branch from file\n");
			fclose(fp); 
			free(pBranch); 
			L_free(&comp->branchList,freeBranch);
			return 0;
		}
		if (!addNewBranchToList(&comp->branchList, pBranch))
			printf("Error adding the branch to the list\n");
	}
	return 1;
}

int addNewBranchToList(LIST* branchList, Branch* pBranch) {
	if (!branchList || !pBranch) {
		return 0;
	}
	NODE* tempN = &(branchList->head); 
	while (tempN->next != NULL) {
		tempN = tempN->next;
	}
	if (!L_insert(tempN, pBranch))
		return 0;

	return 1;
}


int		getBranchescount(const Company* comp)
{
	int count = 0;
	NODE* pN = comp->branchList.head.next; //first Node

	while (pN != NULL)
	{
		count++;
		pN = pN->next;
	}
	return count;
}


int addBranch(Company* comp) {
	Branch* pBranch = (Branch*)malloc(sizeof(Branch));
	RETURN_ZERO(pBranch);

	initBranch(pBranch, comp);

	if (!L_insert(&(comp->branchList.head), pBranch)) { 
		free(pBranch); 
		return 0;
	}
	L_print(&comp->branchList, printBranch);
	return 1;

}

int removeBranch(Company* comp) {
	printf("which branch do you want to remove? removing a branch will delete its data.\n");
	Branch* pBranch = findABranch(comp);
	if (pBranch == NULL) {
		printf("Branch not found.\n");
		return 0; 
	}

	NODE* tempN = &comp->branchList.head; 
	NODE* prevN = NULL;
	while (tempN != NULL && tempN->key != pBranch) {
		prevN = tempN;
		tempN = tempN->next;
	}

	if (tempN == NULL) { 
		printf("Branch not found in the list.\n");
		return 0; 
	}

	if (prevN == NULL) {
		comp->branchList.head = *tempN->next;
	}
	else {
		prevN->next = tempN->next;
	}

	L_delete(tempN->key, freeBranch);

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

void	sortShowTime(Company* comp)
{
	Branch* pBranch = findABranch(comp); 
	printf("How would you like to sort the array?\n");
	sortType type = getSortType();
	if (type == 0) qsort(pBranch->showTimeArray, pBranch->numOfShowTime, sizeof(ShowTime), compareShowTimeByDate); // sort by date
	if (type == 1) qsort(pBranch->showTimeArray, pBranch->numOfShowTime, sizeof(ShowTime), compareShowTimeByMovieName); // sort by destination code 
	if (type == 2) qsort(pBranch->showTimeArray, pBranch->numOfShowTime, sizeof(ShowTime), compareShowTimeByTime); // sort by date  

}

void	findShowTime(const Company* comp)
{
	Branch* pBranch = findABranch(comp);
	ShowTime* pShowTime = (ShowTime*)malloc(sizeof(ShowTime)); 
	if (!pShowTime) return ;
	ShowTime* tempShowTime = (ShowTime*)malloc(sizeof(ShowTime));
	if (!tempShowTime) return ;
	sortType type = getSortType();
	if (type == 0)
	{
		printf("enter date to search:\n");
		Date* d = (Date*)malloc(sizeof(Date));
		if (!d) return ;
		getDate(d);
		tempShowTime->date = *d;
		pShowTime = bsearch(tempShowTime,pBranch->showTimeArray,pBranch->numOfShowTime, sizeof(ShowTime), compareShowTimeByDate);
	}

	if (type == 1)
	{
		
		Movie* movieTemp = (Movie*)malloc(sizeof(Movie));
		if (!movieTemp) return ;
		movieTemp->name = getStrExactName("enter movie name to search : \n");
		tempShowTime->theMovie = *movieTemp;
		pShowTime = bsearch(tempShowTime, pBranch->showTimeArray, pBranch->numOfShowTime, sizeof(ShowTime), compareShowTimeByMovieName);

	}
	if (type == 2)
	{

		printf("enter time to search:\n");
		Time* t = (Time*)malloc(sizeof(Time));
		if (!t) return ;
		getTime(t);
		tempShowTime->time = *t;
		pShowTime = bsearch(tempShowTime, pBranch->showTimeArray, pBranch->numOfShowTime, sizeof(ShowTime), compareShowTimeByTime);
	}
	if (!pShowTime)
	{
		printf("Show time was not found\n");
		return;
	}
	else
	{
		printf("Show time was found\n");
		printShowTime(pShowTime);
	}
	if (type == 3) printf("Canno't search in the unsorted array"); // don't sort
	
}

sortType getSortType()
{
	int option;
	printf("\n\n");
	do {
		printf("Choose one of the options\n");
		for (int i = 0; i < nOfTypes; i++)
			printf("%d for %s\n", i, sortTilte[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= nOfTypes);
	getchar();
	return (sortType)option;
}

int compareShowTimeByDate(const void* v1, const void* v2) {
	const ShowTime s1 = *(const ShowTime*)v1; 
	const ShowTime s2 = *(const ShowTime*)v2;

	// Compare year
	if (s1.date.year != s2.date.year) {
		return s1.date.year - s2.date.year;
	}
	// If year is the same, compare month
	if (s1.date.month != s2.date.month) {
		return s1.date.month - s2.date.month;
	}
	// If month is also the same, compare day
	return s1.date.day - s2.date.day;
}


int compareShowTimeByMovieName(const void* v1, const void* v2)
{
	const ShowTime s1 = *(const ShowTime*)v1;
	const ShowTime s2 = *(const ShowTime*)v2;

	return strcmp(s1.theMovie.name,s2.theMovie.name);
}


int compareShowTimeByTime(const void* v1, const void* v2)
{
	const ShowTime s1 = *(const ShowTime*)v1;
	const ShowTime s2 = *(const ShowTime*)v2;

	// Compare hour
	if (s1.time.hour != s2.time.hour) {
		return s1.time.hour - s2.time.hour;
	}
	// If hour is the same, compare minuets
	return s1.time.minuets - s2.time.minuets;
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

Branch* findBranchByCity(const Company* comp, char* city)
{
	NODE* node = L_find(comp->branchList.head.next, &city, compareBranchCity); 
	if (node != NULL) { 
		return (Branch*)node->key; 
	}
	else {
		return NULL; 
	}
}


Branch* findBranchBySN(const Company* comp, int serialNumber) {
	NODE* node = L_find(comp->branchList.head.next, &serialNumber, compareBranchSerialNum);
	if (node != NULL) { 
		return (Branch*)node->key; // If the node is found, return the branch 
	}
	else {
		return NULL; // If the node is not found, return NULL 
	}
}

Branch* findABranch(const Company* comp) {
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
	return 1; 
}

int addShowTime(Company* comp)
{ 
	Branch* pBranch = findABranch(comp);

	if (pBranch->showTimeArray == NULL)
	{
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

void buyTicket(Company* comp)
{

	Branch* pBranch = findABranch(comp); 

	if (pBranch->showTimeArray == NULL) 
	{
		pBranch->numOfShowTime = 0; 
	} 

	if (pBranch->numOfShowTime == 0) 
	{
		printf("There are not show times\n");
		return;
	}

	if (comp->ticketSales == NULL)
	{
		comp->numOfTickets = 0;
	}

	size_t newSize = (size_t)(comp->numOfTickets + 1) * sizeof(Ticket);
	Ticket* temp = realloc(comp->ticketSales, newSize);
	if (!temp) {
		printf("Failed to allocate memory for new ticket.\n");
		return;
	}
	comp->ticketSales = temp;

	Ticket* pTicket = &comp->ticketSales[comp->numOfTickets]; 
	if (initTicket(pTicket, comp, pBranch))
	{
		comp->ticketSales[comp->numOfTickets] = *pTicket;
		comp->numOfTickets++;
	}
	else
	{
		printf("Order cancelled\n");
	}

	printSeatMap(&pTicket->theShowTime.theTheater); 
	printf("---- Receipt ----\n");
	printReceipt(pTicket);

}

ShowTime chooseShowTime(const Company* comp, const Branch* pBranch)
{
	ShowTime* pShowTime = findAShowTime(pBranch);
	return *pShowTime;

}

//void doesBestSeller(Company* comp)
//{
//	NODE* tempN = &comp->branchList.head;
//	Branch* tempBranch = tempN->next->key;
//	int sales = 0;
//	for (int i = 0; i < comp->numOfBranches; i++)
//	{
//		for(int i=0;i<tempBranch->numOfMovies;i++)
//			sales = numOfTicketsForAMovie(tempBranch->moviesArr[i],comp);
//
//	}
//}
//
//int numOfTicketsForAMovie(Movie* pMovie, Company* comp)
//{
//	int counter = 0;
//	for (int i = 0; i < comp->numOfTickets; i++)
//	{
//		if (!strcmp(comp->ticketSales[i].theShowTime.theMovie.name, pMovie->name))
//			counter++;
//	}
//	return counter;
//}



void printCompany(const Company* comp) {
	printf("%s\n", comp->name);
	printf("------------------\n");
	NODE* current = comp->branchList.head.next;
	while (current != NULL) {
		printBranch((Branch*)current->key); 
		current = current->next;
	}
}

void printSpecificBranch(const Company* comp)
{
	Branch* pBranch = findABranch(comp);
	printDataBranch(pBranch); 
}

void freeCompany(Company* comp) {
	free(comp->name);
	L_free(&comp->branchList, freeBranch); 
}
