#include "numberGame.h"
#include "printMatrix.h"
#include "q2Functions.h"
#include <stdio.h>

const int SHUFFEL_COUNT = 2;

void numberGame()
{
	printf("Please enter a number of rows and cols for matrix\n");
	int rows, cols, number;
	scanf("%d %d", &rows, &cols);
	int mat[rows][cols];
	do
	{
		gameStart((int*)mat, rows, cols, SHUFFEL_COUNT);
	} while (gameIsFinished((int*) mat, rows, cols));
	PrintMatrix((int*) mat, rows, cols);
	while (!gameIsFinished((int*) mat, rows, cols))
	{

		printf("Your step: ");
		scanf("%d", &number);
		printf("\n");
		if(gameMove((int*)mat, rows, cols, number) == 1)
			PrintMatrix((int*) mat, rows, cols);
		else
			printf("Invalid Step!\n");
	}
	printf("You win!!!\n\n");
}
