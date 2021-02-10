#pragma once
#include "GeneralList.h"

#define LEN 9

typedef struct
{
	char*	name;
	char	barcode[LEN + 1];
	float	price;
}Order;

void Q2();

int		initListOfOrder(LIST* plst);
int		initOrderFromUser(Order* pOrder);
int compareBarcode(const Order* bar1,const char* bar2);
NODE* getOrderByBarcode(LIST* plst, const char* barcode);
void printOrder(const Order* pOrder);
void printAllOrders(const LIST* plst);
void freeOrder(Order* pOrder); 
void deleteLastOrder(LIST* plst);
