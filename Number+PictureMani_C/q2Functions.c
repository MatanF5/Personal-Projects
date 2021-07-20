#include "q2Functions.h"
#include <stdlib.h>
#include <stdio.h>

int zeroRow;
int zeroCollumn;

void gameStart(int *mat, int rows, int cols, const int SHUFFEL_COUNT)
{
	int i, j, k = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			*(mat + i * cols + j) = i * cols + j+1;
		}
	}
	*(mat + (rows - 1) * cols + (cols - 1)) = 0;
	zeroRow = rows - 1;
	zeroCollumn = cols - 1;
	while (k < SHUFFEL_COUNT)
	{
		k += gameUpdate((int*) mat, rows, cols, (enum Move) (rand() % 4));
	}
}
int gameUpdate(int *mat, int rows, int cols, enum Move move)
{
	const int dy[] = { -1, 1, 0, 0 };
	const int dx[] = { 0, 0, -1, 1 };
	int i = zeroRow + *(dy + move);
	int j = zeroCollumn + *(dx + move);
	if (i >= 0 && i < rows && j >= 0 && j < cols)
	{
		*(mat + zeroRow * cols + zeroCollumn) = *(mat + i * cols + j);
		*(mat + i * cols + j) = 0;
		zeroRow = i;
		zeroCollumn = j;
		return 1;
	}
	return 0;
}

int gameMove(int *mat, int rows, int cols, int number)
{
	if(zeroRow > 0 && *(mat + (zeroRow-1) * cols + zeroCollumn) == number)
		return gameUpdate(mat, rows, cols, MOVE_UP);
	else if (zeroRow < rows -1 && *(mat + (zeroRow+1) * cols + zeroCollumn) == number)
		return gameUpdate(mat, rows, cols, MOVE_DOWN);
	else if (zeroCollumn > 0 && *(mat + zeroRow * cols +(zeroCollumn-1)) == number)
		return gameUpdate(mat, rows, cols, MOVE_LEFT);
	else if (zeroCollumn < cols -1 && *(mat + zeroRow * cols + (zeroCollumn+1)) == number)
		return gameUpdate(mat, rows, cols, MOVE_RIGHT);
	return 0;
}

int gameIsFinished(int* mat, int rows, int cols)
{
	int i, j, k = 1;
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{
			if((k < rows*cols) && *(mat + i * cols +j) != k++)
			{
				return 0;
			}
		}
	}
	return 1;
}
