
#ifndef __MYTIME__
#define __MYTIME__




typedef struct
{
	int			hour;
	int			minuets;

}Time;

void	getTime(Time* pTime); 
int		checkTime(char* time, Time* pTime); 

int		saveTimeToBinaryFile(const Time* pTime, FILE* fp);
Time*	loadTimeFromTxtFile(FILE* fp);
Time*	loadTimeFromBinaryFile(FILE* fp);

void	printTime(const Time* pTime); 




#endif 