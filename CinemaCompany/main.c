#include <stdio.h>
#include <stdlib.h>
#include "general.h"
#include "Company.h"

typedef enum
{
	eAddBranch, eAddTheater, eAddMovie, eAddShowTime, ePrintCompany,
	ePrintBranchData, eBuyTicket, eNofOptions
} eMenuOptions;

const char* str[eNofOptions] = { "Add Branch","Add Theater","Add Movie","Add Show Time",
								"Print Company","Print Branch Data","Buy Ticket" };

#define EXIT			-1
int menu();

int main() {
	Company	cinemaCompany;
	//Branch branch;
	
	initCompany(&cinemaCompany);

	int option;
	int stop = 0;


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
			buyTicket(&cinemaCompany); 
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