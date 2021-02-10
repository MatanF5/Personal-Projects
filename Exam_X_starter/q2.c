#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "q2.h"


void Q2()
{
	LIST lst;
	NODE* find;
	initListOfOrder(&lst);
	printAllOrders(&lst);
	printf("\n ------- The list ------------\n");
	printAllOrders(&lst);
	printf("\n ------- The list after delete last ------------\n");
	deleteLastOrder(&lst);
	printAllOrders(&lst);
	char barcode[9];
	printf("Enter barcode(9 chars) to search:\n");
	scanf("%s", barcode);
	find = getOrderByBarcode(&lst, barcode);
	if(find != NULL)
		printOrder(find->key);
	else
		printf("Order Not Found\n");
	L_free(&lst, freeOrder);

}


int	initListOfOrder(LIST* plst)
{
	L_init(plst);
	int count;
	Order* pTemp;
	NODE* pN = &plst->head;

	printf("How many orders in list\n");
	scanf("%d", &count);

	for (int i = 0; i < count; i++)
	{
		pTemp = (Order*)malloc(sizeof(Order));
		if (!pTemp)
			return 0;
		initOrderFromUser(pTemp);
		pN = L_insert(pN, pTemp);
	}

	return 1;
}


int		initOrderFromUser(Order* pOrder)
{
	printf("Please enter order name, barcode (%d chars) and price\n",LEN);
	char temp[255];
	scanf("%s %s %f", temp, pOrder->barcode, &pOrder->price);
	pOrder->name = _strdup(temp);
	if (!pOrder->name)
		return 0;
	
	return 1;
}

NODE* getOrderByBarcode(LIST* plst,const char* barcode)
{
	NODE* pN = plst->head.next;
	NODE* found = L_find(pN, barcode, compareBarcode);
	if (found != NULL)
		printf("Order found!  ");
	return found;
}

int compareBarcode(const Order* bar1, const char* bar2)
{
	return strcmp(bar1->barcode, bar2);

}

void printAllOrders(const LIST* plst)
{
	L_print(plst, printOrder);
}

void printOrder(const Order* pOrder)
{
	printf("Order name is:%s, Barcode:%s , price:%.2f\n", pOrder->name, pOrder->barcode, pOrder->price);
}

void deleteLastOrder(LIST* plst)
{
	NODE* pN = &plst->head;
	while (pN->next->next != NULL)
		pN = pN->next;
	L_delete(pN, freeOrder);
}
void freeOrder(Order* pOrder) 
{
	free(pOrder->name);
}