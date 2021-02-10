#pragma once



void Q1();
char** createArrStrings(int* size,int* index, char* str, ...);
char* getDynStr(char* str);
void printAllStrings(char** arr, int size);
void freeArr(char** arr, int size);
int mostSpaceString(char** allStrings, int size);
