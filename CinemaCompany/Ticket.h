#ifndef __TICKET__
#define __TICKET__

#include "Costumer.h"
#include "ShowTime.h"

typedef struct
{
	char* seatNum;
	double price;
	ShowTime theShowTime;
	Costumer theCostumer;

}Ticket;

void setPrice(Ticket* pTicket);
void checkForDiscount(Ticket* pTicket);
int checkAgeLimit(Ticket* pTicket);
#endif 
