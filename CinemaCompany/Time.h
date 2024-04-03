
#ifndef __MYTIME__
#define __MYTIME__




typedef struct
{
	int			hour;
	int			minuets;

}Time;

void	getTime(Time* pDate); 
int		checkTime(char* time, Time* pDate); 
void	printTime(const Time* pDate); 


#endif 