#include <stdio.h>
#include <stdlib.h>
#include "printMatrix.h"


void PrintMatrix(const int* mat, int rows, int cols)
{
	printf("\n");
	int i,j;
	for(i = 0; i < rows; i++)
	{	for (j = 0; j < cols; j++)
		{
			printf("%4d", *mat);
			mat++;
		}
		printf("\n");
	}
	printf("\n");
}
