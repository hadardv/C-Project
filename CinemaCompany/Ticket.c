#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Ticket.h"
#define REGULAR_PRICE 48
#define VIP_PRICE 145
#define THREED_PRICE 70


void setPrice(Ticket* pTicket)
{
	if (!strcmp(TheaterTypeStr[pTicket->theShowTime.theTheater.type], "Regular"))
		pTicket->price = REGULAR_PRICE; 
	if (!strcmp(TheaterTypeStr[pTicket->theShowTime.theTheater.type], "VIP"))
		pTicket->price = VIP_PRICE; 
	if (!strcmp(TheaterTypeStr[pTicket->theShowTime.theTheater.type], "3D"))
		pTicket->price = THREED_PRICE; 
}

void checkForDiscount(Ticket* pTicket)
{
	if (pTicket->theCostumer.age < 2)
	{
		pTicket->price = 0; // toddlers enter for free
	}
	if (pTicket->theCostumer.age <= 21 && pTicket->theCostumer.age >= 18)
	{
		pTicket->price = pTicket->price * 0.5; // discount for soliders
	}
	if (pTicket->theCostumer.age > 65)
	{
		pTicket->price = pTicket->price * 0.3; // discount for above elders
	}
}

int checkAgeLimit(Ticket* pTicket)
{
	if (pTicket->theCostumer.age < pTicket->theShowTime.theMovie.ageLimit)
	{
		printf("The movie %s has an age limit of %d \n", pTicket->theShowTime.theMovie.name, pTicket->theShowTime.theMovie.ageLimit);
		return 0;
	}
	return 1;
}

void printReceipt(Ticket* pTicket)
{
	printf("Costumer id: ");
	printCostumer(&pTicket->theCostumer);
	printf("Price: %f\n",pTicket->price);
	printf("Seat number: %s\n",pTicket->seatNum);
	printf("The show time:");
	printShowTime(&pTicket->theShowTime);


}



