#ifndef __TICKET__
#define __TICKET__

#include "Costumer.h"
#include "ShowTime.h"

typedef struct
{
	int seatNum;
	float price;
	ShowTime theShowTime;
	Costumer theCostumer;
	Ticket** ticketSales; 

}Ticket;

//int initTicket(Ticket* pTicket);
//int checkForDiscount(Ticket* pTicket);
//int checkIfSeatTaken(Ticket* pTicket);
//int checkAgeLimit(Ticket* pTicket);
#endif 
