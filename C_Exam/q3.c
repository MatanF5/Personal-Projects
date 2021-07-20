#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "q3.h"

#define FILE_NAME "accounts_comp.bin"
//#define FILE_NAME "accounts.bin"

void Q3()
{

	int count;

	AccountInfo* arr = createAccountArrFromFile(FILE_NAME,&count);

	printf("\n\n--------- after read ----------\n\n");
	printAcountInfoArr(arr, count);

	free(arr);

}

AccountInfo* createAccountArrFromFile(const char* fileName, int* pCount)
{
	FILE* fp;
	int res;
	fp = fopen(fileName, "rb");
	if (!fp)
		return NULL;
	unsigned char data;
	AccountInfo* arr = NULL;
	if (fread(&data, sizeof(unsigned char), 1, fp) != 1)
		return NULL;
	*pCount = data;
	arr = (AccountInfo*)malloc(sizeof(AccountInfo)*((*pCount) + 1));
	if (!arr)
		return NULL;
	for (int i = 0; i < *pCount; i++)
	{
		res = readAccountFromFile(&(arr[i]), fp);
		if (res == 0)
		{
			fclose(fp);
			return NULL;
		}
	}
	fclose(fp);
	return arr;

}

int readAccountFromFile(AccountInfo* pAcc, FILE* fp)
{
	BYTE data[3];
	if(fread(&data,sizeof(BYTE),3,fp) != 3)
		return 0;
	pAcc->bankCode = (data[0] >> 5);
	pAcc->branch = (data[0] & 0x1f ) << 4 | (data[1] >> 4);
	pAcc->number = (data[1] & 0xf) << 8 | data[2];
	return 1;
}

void printAcountInfo(const AccountInfo* pInfo)
{
	printf("Account: bank %d branch %d number %d\n", pInfo->bankCode, pInfo->branch, pInfo->number);
	
}

void printAcountInfoArr(const AccountInfo* arr, int count)
{
	printf("There are %d accounts\n", count);
	for (int i = 0; i < count; i++)
		printAcountInfo(&arr[i]);
	printf("\n");
}
