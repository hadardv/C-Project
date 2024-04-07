#ifndef __COMPANY__
#define __COMPANY__

#include "list.h"
#include "Branch.h"
#include "Ticket.h"

typedef struct
{
	LIST branchList; 
	char* name;
	int numOfBranches;
	Ticket* ticketSales;
	int numOfTickets;

}Company;

void initCompany(Company* comp);  
void initBranch(Branch* branch, Company* comp);
int initTicket(Ticket* pTicket, Company* comp,Branch* pBranch);
int addBranch(Company* comp);
int addTheater(Company* comp);
int addMovie(Company* comp);
int addShowTime(Company* comp);
void buyTicket(Company* comp);
char* setName(Branch* branch, Company* pComp);
int compareBranchSerialNum(void* data, void* serialNum);
int compareBranchCity(const void* branch, const void* city);
Branch* findBranchBySN(Company* comp, int serialNumber);
Branch* findBranchByCity(Company* comp, char* city);
Branch* findABranch(Company* comp);
void printCompany(Company* comp); 
void printSpecificBranch(Company* comp);
ShowTime chooseShowTime(Company* comp,Branch* pBranch);
void freeCompany(Company* comp); 

#endif 



