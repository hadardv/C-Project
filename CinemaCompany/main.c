#include <stdio.h>
#include <stdlib.h>
#include "general.h"
#include "Company.h"

typedef enum
{
	eAddBranch, eAddTheater, eAddMovie, eAddShowTime, ePrintCompany,
	ePrintBranchData, eBuyTicket,eRemoveBranch,eSortShowTime,eSearchShowTime, eNofOptions
} eMenuOptions;

const char* str[eNofOptions] = { "Add Branch","Add Theater","Add Movie","Add Show Time",
								"Print Company","Print Branch Data","Buy Ticket","Remove Branch","Sort Show Time" ,"Search Show Time" };

#define EXIT			-1
#define COMPANY_TXT_FILE_NAME "cinema_company.txt"
#define COMPANY_BINARY_FILE_NAME "cinema_company.bin"


int menu();

int main() {
	Company	cinemaCompany;
	//Branch branch;
	
	initCompany(&cinemaCompany);

	int option;
	int stop = 0;
	int num = 0;



	do
	{
		option = menu();
		switch (option)
		{
		case eAddBranch:
			if (!addBranch(&cinemaCompany))
				printf("Error adding Branch\n");
			break;

		case eAddTheater:
			if (!addTheater(&cinemaCompany)) 
				printf("Error adding Theater\n");
			break;

		case eAddMovie:
			if (!addMovie(&cinemaCompany))
				printf("Error adding movie\n");
			break;

		case eAddShowTime:
			if (!addShowTime(&cinemaCompany))
				printf("Error adding show time\n");
			break;

		case ePrintCompany:
			printCompany(&cinemaCompany);
			break;

		case ePrintBranchData:
			printSpecificBranch(&cinemaCompany);
			break;

		case eBuyTicket:
			printf("How many tickets do you want to buy?");
			scanf("%d", &num);
			for (int i=0; i<num; i++)
				buyTicket(&cinemaCompany); 
			break;

		case eRemoveBranch:
				removeBranch(&cinemaCompany);
			break;

		case eSortShowTime:
			sortShowTime(&cinemaCompany);
			break;

		case eSearchShowTime:
			findShowTime(&cinemaCompany);
			break;

		case EXIT:
			printf("Bye bye\n");
			stop = 1;
			break;

		default:
			printf("Wrong option\n");
			break;
		}
	} while (!stop);

	saveCompanyToTxtFile(&cinemaCompany, COMPANY_TXT_FILE_NAME);
	saveCompanyToBinaryFile(&cinemaCompany, COMPANY_BINARY_FILE_NAME);


}

int menu() 
{
	int option;
	printf("\n\n");
	printf("Please choose one of the following options\n");
	for (int i = 0; i < eNofOptions; i++)
		printf("%d - %s\n", i, str[i]);
	printf("%d - Quit\n", EXIT);
	scanf("%d", &option);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	return option;
}