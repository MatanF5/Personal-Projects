#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AirportManager.h"

int	initManager(AirportManager* pManager)
{
	printf("-----------  Init airport Manager\n");
	pManager->count = 0;
	L_init(&pManager->allAirports);
	int count=0;
	do {
		printf("How many airport?\t");
		scanf("%d", &count);
	} while (count < 0);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	if (count == 0)
		return 1;

	for (int i = 0; i < count; i++)
	{
		addAirport(pManager);
	}
	
	return 1;
}


int	addAirport(AirportManager* pManager)
{
	Airport* pA;
	Airport* pA2;
	NODE* head = pManager->allAirports.head.next;
	pA = (Airport*)malloc(sizeof(Airport));
	if (!pA)
		return 0;
	setAirport(pA, pManager);
	if (head != NULL)
	{
		pA2 = head->key;
		if (strcmp(pA->code, pA2->code) < 0)
		{
			pManager->allAirports.head.next = L_push(head, pA);
			pManager->count++;
			return 1;
		}
	}
	NODE* p = getNode(pManager, pA->code);
	L_insert(p, pA);
	pManager->count++;
	return 1;
}

NODE* getNode(AirportManager* pManager,char* code)
{
	Airport* pA;
	NODE* pNode = pManager->allAirports.head.next;
	if (pNode == NULL)
		return &pManager->allAirports.head;
	while (pNode->next != NULL)
	{
		pA = pNode->next->key;
		if (strcmp(code, pA->code) < 0)
			return pNode;
		pNode = pNode->next;	
	}
	return pNode;
}

void  setAirport(Airport* pPort, AirportManager* pManager)
{
	while (1)
	{
		getAirportCode(pPort->code);
		if (checkUniqeCode(pPort->code, pManager))
			break;

		printf("This code already in use - enter a different code\n");
	}

	initAirportNoCode(pPort);
}

Airport* findAirportByCode(const AirportManager* pManager, const char* code)
{
	 const NODE* temp = pManager->allAirports.head.next;
	 Airport* pA;
	while(temp != NULL)
	{
		pA = temp->key;
		if (isAirportCode(pA, code))
			return temp->key;
		temp = temp->next;
	}
	return NULL;
}

int checkUniqeCode(const char* code,const AirportManager* pManager)
{
	Airport* port = findAirportByCode(pManager, code);

	if (port != NULL)
		return 0;

	return 1;
}

void	printAirports(const AirportManager* pManager)
{

	printf("there are %d airports\n", pManager->count);
	L_print(&pManager->allAirports, printAirport);
	printf("\n");

}

void	freeManager(AirportManager* pManager)
{
	L_free(&pManager->allAirports,freeAirport);
}

int managerToFile(AirportManager* pManager)
{
	FILE* f = fopen("airport_authority.txt", "w");
	NODE* pAir = pManager->allAirports.head.next;
	Airport* temp;
	if (!f)
		return 0;
	fprintf(f, "%d\n", pManager->count);
	
	while(pAir != NULL)
	{
		temp = pAir->key;
		writeAirportToFile(f, temp);
		pAir = pAir->next;
	}
	fclose(f);
	return 1;
}

void writeAirportToFile(FILE* f, Airport* pAir)
{
	fprintf(f,"%s\n", pAir->name);
	fprintf(f,"%s\n", pAir->country);
	fprintf(f,"%s\n", pAir->code);
	fprintf(f,"\n");
}

int readFromTextFile(AirportManager* pManager)
{
	Airport* airport;
	FILE* f = fopen("airport_authority.txt", "r");
	if (!f)
		return 0;
	L_init(&pManager->allAirports);
	fscanf(f, "%d\n", &(pManager->count));
	char tempName[MAX_STR_LEN];
	char tempCountry[MAX_STR_LEN];
	NODE* temp = &pManager->allAirports.head;
	for (int i = 0; i < pManager->count; i++)
	{
		airport = (Airport*)malloc(sizeof(Airport));
		if (!airport)
		{
			fclose(f);
			return 0;
		}

		fgets(tempName, MAX_STR_LEN, f);
		tempName[strlen(tempName) - 1] = '\0';
		airport->name = _strdup(tempName);
		fgets(tempCountry, MAX_STR_LEN, f);
		tempCountry[strlen(tempCountry) - 1] = '\0';
		airport->country = _strdup(tempCountry);
		fscanf(f, "%s\n", &airport->code);
		L_insert(temp, airport);
		temp = temp->next;
	}
	fclose(f);
	return 1;
}