// Dmitry Inke
// Matan Fridlis
#include <stdio.h>
#include <stdlib.h>
#include "pictureManipulation.h"
#include "numberGame.h"
#include <time.h>

int main()
{
	srand(time(0));
	char choice;
	int flag = 1;
	do
	{
		printf("Please choose one of the following options\n");
		printf("P/p - Picture Manipulation\n");
		printf("N/n- Number Game\n");
		printf("E/e - Quit\n\n");
		printf("Enter your choice: ");
		scanf("%c",&choice);
		switch (choice)
		{
		case 'P':
		case 'p':
			pictureManipulation();
			break;

		case 'N':
		case 'n':
			numberGame();
			break;
		case 'E':
		case 'e':
			printf("Bye bye!\n");
			flag = 0;
			break;
		default:
			printf("Wrong input\n\n");
			break;
		}
		choice = getchar();
	} while (flag != 0);
	return 0;
}
