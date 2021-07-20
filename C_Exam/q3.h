#pragma once

typedef unsigned char BYTE;

typedef struct
{
	int bankCode;
	int branch;
	int number;
}AccountInfo;


void Q3();
typedef unsigned char BYTE;
AccountInfo* createAccountArrFromFile(const char* fileName, int* pCount);

void printAcountInfo(const AccountInfo* pInfo);
void printAcountInfoArr(const AccountInfo* arr, int count);
int readAccountFromFile(AccountInfo* pAcc, FILE* fp);
