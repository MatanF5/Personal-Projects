#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#include "mystrlib.h"

int main(void)
{
	pid_t check;
	char* mMap = (char*)mmap(NULL, sizeof(char) * 128, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (mMap == MAP_FAILED)
		exit(EXIT_FAILURE);
	*mMap = 0;

	check = fork();

	if (check < 0)
	{
		fprintf(stderr, "fork failed\n");
		exit(EXIT_FAILURE);
	}

	while (!feof(stdin))
	{
		if (check == 0)  
		{
			if (*mMap == 1)
			{
				*(mMap + 1) = mystrxor(mMap + 2, mMap + (strlen(mMap + 2) + 3));
				*mMap = 2;
			}
		}

		else  
		{

			if (*mMap == 0)
			{

				printf("Enter The First String:\n");
				mygets(mMap + 2, MAX_LEN);
				printf("Enter The Second String:\n");
				mygets(mMap + (strlen(mMap + 2) + 3), MAX_LEN);

				fflush(stdin);
				*mMap = 1;
			}
			else if (*mMap == 2)
			{
				printf("Xor result: %d\n", *(mMap + 1));
				*mMap = 0;
			}
		}
	}
	return EXIT_SUCCESS;
}