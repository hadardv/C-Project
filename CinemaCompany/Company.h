#ifndef __COMPANY__
#define __COMPANY__

#include "list.h"
#include "Branch.h"

typedef struct
{
	LIST branchList; 
	char* name;
	int numOfBranches; 
}Company;

void initCompany(Company* comp);  
void initBranch(Branch* branch, Company* comp);
//int	insertNewBranchToList(LIST* pBranchList, Branch* pBranch);
int addBranch(Company* comp);
int addTheater(Company* comp);
int addMovie(Company* comp);
int addShowTime(Company* comp);
char* setName(Branch* branch, Company* pComp);
int checkUniqeSN(Company* comp, int serialNumber);
//int checkUniqeCity(Company* comp, char* city);
int compareBranchSerialNum(void* data, void* serialNum);
int compareBranchCity(const void* branch, const void* city);
Branch* findBranchBySN(Company* comp, int serialNumber);
Branch* findBranchByCity(Company* comp, char* city);
Branch* findABranch(Company* comp);
void printCompany(Company* comp); 
void printSpecificBranch(Company* comp);
void freeCompany(Company* comp); 

#endif 



