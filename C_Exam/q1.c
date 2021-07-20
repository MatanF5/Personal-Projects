#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "q1.h"


void Q1()
{

	char str1[] = "This is";
	char str2[] = "A good day";
	char str3[] = "abcdefghijklmnopqrstuvwxyz";
	int size;
	int index;
	int indexMost;
	char** allStr = createArrStrings(&size, &index, str1, str2, str3, NULL);
	printf("\n----- The Strings ------------\n");
	printAllStrings(allStr, size);
	printf("\n----- The Longest String ------------\n");
	printf("index of the string:%d, %s\n", index, allStr[index]);
	printf("\n----- The most words String ------------\n");
	indexMost = mostSpaceString(allStr, size);
	printf("index of the string:%d, %s\n", indexMost, allStr[indexMost]);
	freeArr(allStr, size);
}


char** createArrStrings(int* size, int* index, char* str, ...)
{
	if (!str)
		return NULL;
	va_list lst;
	int count = 0;
	size_t max = 0;
	int indx;
	va_start(lst, index);
	char** allStrings;
	allStrings = (char**)malloc(sizeof(char*)*(count + 1));
	if (!allStrings)
		return NULL;
	char* temp = va_arg(lst, char*);
	while (temp != NULL)
	{
		allStrings[count] = getDynStr(temp);
		if (strlen(temp) > max)
		{
			indx = count;
			max = strlen(temp);
		}
		count++;
		allStrings = (char**)realloc(allStrings, sizeof(char*)*(count + 1));
		if (!allStrings)
			return NULL;
		temp = va_arg(lst, char*);
	}
	va_end(lst);
	*size = count;
	*index = indx;
	return allStrings;
}

char* getDynStr(char* str)
{
	char* theStr;
	theStr = (char*)malloc((strlen(str) + 1) * sizeof(char));
	if (!theStr)
		return NULL;
	strcpy(theStr, str);
	return theStr;
}

void printAllStrings(char** arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%s\n", arr[i]);
	}
}

void freeArr(char** arr, int size)
{
	for (int i = 0; i < size; i++)
		free(arr[i]);
	free(arr);

}

int mostSpaceString(char** allStrings, int size)
{
	int count = 0;
	int max = 0;
	int index;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < strlen(allStrings[i]); j++)
		{
			if ((allStrings[i])[j] == ' ')
				count++;
		}
		if (count > max)
		{
			index = i;
			max = count;
		}
		count = 0;
	}
	return index;
}