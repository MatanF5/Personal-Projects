#include "printMatrix.h"
#include "pictureManipulation.h"
#include "q1Functions.h"
#include <stdio.h>


void pictureManipulation()
{
	printf("Please enter size of matrix\n");
	int size; 
	scanf("%d", &size);	
	int mat[size][size];
	Q1_fillRandomMatrix((int*)mat, size);
	PrintMatrix((int*)mat, size, size);

	int flag = 1;
	int result;
	do
	{
		printf("Please choose one of the following options\n");
		printf("1 - 90 degree clockwise\n");
		printf("2 - 90 degree counter clockwise\n");
		printf("3 - Flip Horizontal\n");
		printf("4 - Flip Vertical\n");
		printf("-1 - Quit\n");
		scanf("%d",&result);
		switch (result)
		{
		case 1:
		{
			Q1_Clockwise90((int*) mat,size);
			printf("\n--------- picture after manipulation ---------\n");
			PrintMatrix((int*)mat, size, size);
			printf("\n");
			break;
		}
		case 2:
		{
			Q1_CounterClockWise90((int*) mat,size);
			printf("\n--------- picture after manipulation ---------\n");
			PrintMatrix((int*)mat, size, size);
			printf("\n");
			break;
		}
		case 3:
		{
			Q1_FlipHorizontal((int*) mat,size);
			printf("\n--------- picture after manipulation ---------\n");
			PrintMatrix((int*)mat, size, size);
			printf("\n");
			break;
		}
		case 4:
		{
			Q1_FlipVertical((int*) mat,size);
			printf("\n--------- picture after manipulation ---------\n");
			PrintMatrix((int*)mat, size, size);
			printf("\n");
			break;
		}
		case -1:
			flag = 0;
			break;
		default:
			printf("Wrong input\n\n");
			break;

		}
	} while (flag != 0);
}	 

