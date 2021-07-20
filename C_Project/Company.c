#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Company.h"
#include "Airport.h"
#include "General.h"


const char* sort[eNoSort] = { "Sort by Hour","Sort by Date" };

void	initCompany(Company* pComp)
{
	printf("-----------  Init Airline Company\n");
	pComp->name = getStrExactName("Enter company name");
	pComp->flightArr = NULL;
	pComp->flightCount = 0;
	pComp->sortOption = eNoSort;
	L_init(&pComp->allDates);
}

int	addFlight(Company* pComp, const AirportManager* pManager)
{
	if (pManager->count < 2)
	{
		printf("There are not enoght airport to set a flight\n");
		return 0;
	}
	pComp->flightArr = (Flight**)realloc(pComp->flightArr, (pComp->flightCount + 1) * sizeof(Flight*));
	if (!pComp->flightArr)
		return 0;
	pComp->flightArr[pComp->flightCount] = (Flight*)calloc(1, sizeof(Flight));
	if (!pComp->flightArr[pComp->flightCount])
		return 0;
	initFlight(pComp->flightArr[pComp->flightCount], pManager);

	NODE* p = &pComp->allDates.head;
	Date* da = &pComp->flightArr[pComp->flightCount]->date;
	char* pDate;
	pDate = (char*)malloc(11 * sizeof(char));
	if (!pDate)
		return 0;
	sprintf(pDate, "%d/%d/%d", da->day, da->month, da->year);
	if (L_find(p->next, pDate, strcmp) == NULL)
		L_insert(p, pDate);
	pComp->flightCount++;
	return 1;
}

void printCompany(const Company* pComp)
{

	printf("Company %s:\n", pComp->name);
	printf("Has %d flights\n", pComp->flightCount);
	printFlightArr(pComp->flightArr, pComp->flightCount);
	printf("These are the flights dates:\n");
	L_print(&pComp->allDates, printDateNew);
	printf("\n");
}

void printDateNew(const char* date)
{
	printf("%s\n", date);
}

void	printFlightsCount(const Company* pComp)
{
	char codeOrigin[CODE_LENGTH + 1];
	char codeDestination[CODE_LENGTH + 1];

	if (pComp->flightCount == 0)
	{
		printf("No flight to search\n");
		return;
	}

	printf("Origin Airport\n");
	getAirportCode(codeOrigin);
	printf("Destination Airport\n");
	getAirportCode(codeDestination);

	int count = countFlightsInRoute(pComp->flightArr, pComp->flightCount, codeOrigin, codeDestination);
	if (count != 0)
		printf("There are %d flights ", count);
	else
		printf("There are No flights ");

	printf("from %s to %s\n", codeOrigin, codeDestination);
}


void	freeCompany(Company* pComp)
{
	freeFlightArr(pComp->flightArr, pComp->flightCount);
	free(pComp->flightArr);
	free(pComp->name);
}

int companyToBFile(Company* pComp)
{
	FILE* f;
	f = fopen("company.bin", "wb");
	if (!f)
		return 0;
	size_t nameLength = strlen(pComp->name) + 1;
	if (fwrite(&nameLength, sizeof(int), 1, f) != 1)
	{
		fclose(f);
		return 0;
	}
	if (fwrite(pComp->name, sizeof(char), nameLength, f) != nameLength)
	{
		fclose(f);
		return 0;
	}
	if (fwrite(&(pComp->flightCount), sizeof(int), 1, f) != 1)
	{
		fclose(f);
		return 0;
	}
	if (fwrite(&(pComp->sortOption), sizeof(int), 1, f) != 1)
	{
		fclose(f);
		return 0;
	}
	for (int i = 0; i < pComp->flightCount; i++)
	{
		if (fwrite(pComp->flightArr[i], sizeof(Flight), 1, f) != 1)
		{
			fclose(f);
			return 0;
		}
	}
	fclose(f);
	return 1;

}

void    printFlightArr(Flight** pFlight, int size)
{
	generalArrayFunction(pFlight, size, sizeof(*pFlight), printPtrFlight);
}

void printPtrFlight(const Flight** flight)
{
	printFlight(*flight);
}

void    freeFlightArr(Flight** arr, int size)
{
	generalArrayFunction(arr, size, sizeof(*arr), freePtrFlight);
}

void freePtrFlight(Flight** flight)
{
	freeFlight(*flight);
}

int compareFlightByHour(const void* fl1, const void* fl2)
{
	const Flight* fly1 = *(const Flight**)fl1;
	const Flight* fly2 = *(const Flight**)fl2;
	return fly1->hour - fly2->hour;
}

int compareFlightbyDate(const void* d1, const void* d2)
{
	const Flight* date1 = *(const Flight**)d1;
	const Flight* date2 = *(const Flight**)d2;
	if (date1->date.year > date2->date.year)
		return 1;
	else if (date1->date.year < date2->date.year)
		return -1;
	else
	{
		if (date1->date.month > date2->date.month)
			return 1;
		else if (date1->date.month < date2->date.month)
			return -1;
		else
		{
			if (date1->date.day > date2->date.day)
				return 1;
			else if (date1->date.day < date2->date.day)
				return -1;
			else
				return 0;
		}
	}
}

void sortFlights(Company* pComp)
{
	int option;
	printf("\n\n");
	printf("Choose kind of sort:\n");
	for (int i = 0; i < eNoSort; i++)
		printf("please %d for %s\n", i + 1, sort[i]);
	scanf("%d", &option);
	char tav;
	scanf("%c", &tav);
	switch (option - 1)
	{
	case eHour:
		qsort(pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareFlightByHour);
		pComp->sortOption = eHour;
		break;
	case eDate:
		qsort(pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareFlightbyDate);
		pComp->sortOption = eDate;
		break;
	}

}


void searchFlight(Company* pComp)
{
	Flight* fly = (Flight*)malloc(sizeof(Flight));
	if (!fly)
		return;
	Flight* pFound = NULL;
	switch (pComp->sortOption)
	{
	case eHour:
		fly->hour = getFlightHour();
		pFound = bsearch(&fly, pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareFlightByHour);
		break;
	case eDate:
		getCorrectDate(&(fly->date));
		pFound = bsearch(&fly, pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareFlightbyDate);
		break;
	case eNoSort:
		printf("Not Sorted Cant Search\n");
		break;
	}
	if (!pFound)
		printf("Flight Not Found\n");
	else
	{
		printf("Flight Found, ");
		printFlight(*(Flight**)pFound);
	}
	free(fly);
}

int readFromBinaryFile(Company* pComp)
{
	int name;
	FILE* f = fopen("company.bin", "rb");
	if (!f)
		return 0;
	if (fread(&name, sizeof(int), 1, f) != 1)
	{
		fclose(f);
		return 0;
	}

	pComp->name = (char*)malloc(name * sizeof(char));
	if (!pComp->name)
	{
		fclose(f);
		return 0;
	}

	if (fread(pComp->name, sizeof(char), name, f) != name)
	{
		fclose(f);
		return 0;
	}
	if (fread(&(pComp->flightCount), sizeof(int), 1, f) != 1)
	{
		fclose(f);
		return 0;
	}
	if (fread(&(pComp->sortOption), sizeof(int), 1, f) != 1)
	{
		fclose(f);
		return 0;
	}
	pComp->flightArr = NULL;
	L_init(&pComp->allDates);
	for (int i = 0; i < pComp->flightCount; i++)
	{
		pComp->flightArr = (Flight**)realloc(pComp->flightArr, (pComp->flightCount + 1) * sizeof(Flight*));
		if (!pComp->flightArr)
		{
			fclose(f);
			return 0;
		}
		pComp->flightArr[i] = (Flight*)calloc(1, sizeof(Flight));
		if (!pComp->flightArr[i])
		{
			fclose(f);
			return 0;
		}
		if (fread(pComp->flightArr[i], sizeof(Flight), 1, f) != 1)
		{
			fclose(f);
			return 0;
		}
		NODE* p = &pComp->allDates.head;
		char* pDate;
		pDate = (char*)malloc(11 * sizeof(char));
		if (!pDate)
			return 0;
		sprintf(pDate, "%d/%d/%d", pComp->flightArr[i]->date.day, pComp->flightArr[i]->date.month, pComp->flightArr[i]->date.year);
		p = L_insert(p, pDate);
	}

	fclose(f);
	return 1;
}