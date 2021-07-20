#include "q1Functions.h"
#include <stdlib.h>
#include <stdio.h>
void Q1_fillRandomMatrix(int* mat, int size)
{
	int i,j;
	for(i = 0; i < size; i++)
	{	for (j = 0; j < size; j++)
		{
			*(mat + i * size +j) = 1 + (rand()) % 100;
		}
	}	
}

void Q1_Clockwise90(int* mat, int size)
{
	int i,j,temp;
	for(i = 0; i < size/2; i++)
	{	for (j = 0; j < (size/2 + size%2); j++)
		{
			temp = *(mat + i * size + j);
			*(mat + i * size + j) = *(mat + (size - j - 1) * size + i);
			*(mat + (size - j - 1) * size + i) = *(mat + (size - i -1) * size + (size - j - 1));
			*(mat + (size - i - 1) * size +(size - j - 1)) = *(mat + j * size +(size - i - 1));
			*(mat + j * size + (size - i - 1)) = temp;
		}
	}	
}

void Q1_CounterClockWise90(int* mat, int size)
{
	int i,j,temp;
	for(i = 0; i < size/2; i++)
	{	for (j = i; j < size-i-1; j++)
		{
			temp = *(mat + i * size + j);
			*(mat + i * size + j) = *(mat + j * size + (size - i -1));
			*(mat + j * size + (size - i -1)) = *(mat + (size - i -1) * size + (size - j - 1));
			*(mat + (size - i - 1) * size +(size - j - 1)) = *(mat + (size - j - 1) * size + i);
			*(mat + (size - j - 1) * size + i) = temp;
		}
	}
}
void Q1_FlipHorizontal(int* mat, int size)
{
	int i,j,temp;
	for(i = 0; i < size/2; i++)
	{	for (j = 0; j < size; j++)
		{
			temp = *(mat + i * size + j);
			*(mat + i * size + j) = *(mat + (size-i-1) * size + j);
			*(mat + (size-i-1) * size + j) = temp;
		}
	}
}

void Q1_FlipVertical(int* mat, int size)
{
	int i,j,temp;
	for(i = 0; i < size; i++)
	{	for (j = 0; j< size/2; j++)
		{
			temp = *(mat + i * size + j);
			*(mat + i * size + j) = *(mat + i * size + (size -1-j));
			*(mat + i * size + (size -1-j)) = temp;
		}
	}
}
