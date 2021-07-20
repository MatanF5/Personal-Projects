#ifndef __COMP__
#define __COMP__

#include "Flight.h"
#include "AirportManager.h"

typedef enum
{
	eHour, eDate, eNoSort
} SorteNums;

typedef struct
{
	char*		name;
	int			flightCount;
	Flight**	flightArr;
	LIST allDates;
	SorteNums sortOption;

}Company;


void	initCompany(Company* pComp);
int		addFlight(Company* pComp,const AirportManager* pManager);
void	printCompany(const Company* pComp);
void	printFlightsCount(const Company* pComp);
void	printFlightArr(Flight** pFlight, int size);
void	freeFlightArr(Flight** arr, int size);
void	freeCompany(Company* pComp);
void printDateNew(const char* date);
int companyToBFile(Company* pComp);
void printPtrFlight(const Flight** flight);
void freePtrFlight(Flight** flight);
int compareFlightByHour(const void* fl1, const void* fl2);
int compareFlightbyDate(const void* d1, const void* d2);
void sortFlights(Company* pComp);
void searchFlight(Company* pComp);
int readFromBinaryFile(Company* pComp);
#endif

