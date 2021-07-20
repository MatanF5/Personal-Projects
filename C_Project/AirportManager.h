#ifndef __AIR_MANAGER__
#define __AIR_MANAGER__

#include "Airport.h"
#include "listGen.h"

typedef struct
{
	LIST	allAirports;
	int			count;
}AirportManager;

int		initManager(AirportManager* pManager);
int		addAirport(AirportManager* pManager);
void	setAirport(Airport* pPort, AirportManager* pManager);
Airport* findAirportByCode(const AirportManager* pManager, const char* code);
int		checkUniqeCode(const char* code, const AirportManager* pManager);
void	printAirports(const AirportManager* pManager);
void	freeManager(AirportManager* pManager);
NODE* getNode(AirportManager* pManager, char* code);
int managerToFile(AirportManager* pManager);
void writeAirportToFile(FILE* f, Airport* pAir);
int readFromTextFile(AirportManager* pManager);
#endif