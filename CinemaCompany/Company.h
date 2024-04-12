#ifndef __COMPANY__
#define __COMPANY__

#include "list.h"
#include "Branch.h"
#include "Ticket.h"

typedef enum { date, movieName, showTimeTime, none, nOfTypes } sortType;
static const char* sortTilte[nOfTypes] = { "Date", "Movie Name", "Show time time" , "none" };

typedef struct
{
	sortType    type;
	LIST branchList; 
	char* name;
	/*Ticket* ticketSales;
	int numOfTickets;*/

}Company;

void initCompany(Company* comp);  
void initBranch(Branch* branch, Company* comp);
int initTicket(Ticket* pTicket, Company* comp,Branch* pBranch);
sortType getSortType();
char* setName(Branch* branch, Company* pComp);

int addBranch(Company* comp);
int addMovie(Company* comp);
int addTheater(Company* comp);
int addShowTime(Company* comp);
int	addNewBranchToList(LIST* branchList, Branch* pBranch);

int removeBranch(Company* comp);
void buyTicket(Company* comp);
int	getBranchescount(const Company* comp);

int saveCompanyToBinaryFile(const Company* comp, const char* fileName);
int saveCompanyToTxtFile(const Company* comp, const char* fileName);
int loadCompanyFromTxtFile(Company* comp, const char* fileName);
int loadCompanyFromBinaryFile(Company* comp, const char* fileName);


int compareShowTimeByDate(const void* v1, const void* v2);
int compareShowTimeByMovieName(const void* v1, const void* v2);
int compareShowTimeByTime(const void* v1, const void* v2);
int compareBranchSerialNum(const void* data, const void* serialNum);
int compareBranchCity(const void* branch, const void* city);

Branch* findBranchBySN(const Company* comp, int serialNumber);
Branch* findBranchByCity(const Company* comp, char* city);
Branch* findABranch(const Company* comp);
void findShowTime(const Company* comp);

void sortShowTime(Company* comp);
ShowTime chooseShowTime(const Company* comp, const Branch* pBranch);

void printCompany(const Company* comp);
void printSpecificBranch(const Company* comp);

void freeCompany(Company* comp); 

//int numOfTicketsForAMovie(Movie* pMovie, Company* comp);
//void doesBestSeller(Movie** movieArr, int numOfMovies, Company* comp);
#endif 



