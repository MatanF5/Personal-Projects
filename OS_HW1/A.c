#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/wait.h>
#include "mystrlib.h"

int main(int argc, char *argv[])
{
	do
	{
		char word1[MAX_LEN + 1];
		char word2[MAX_LEN + 1];
		int result;
		pid_t check;
		printf("Enter The First String:\n");
		mygets(word1, MAX_LEN);
		printf("Enter The Second String:\n");
		mygets(word2, MAX_LEN);
		fflush(stdin);

		check = fork();

		if (check < 0)
		{
			fprintf(stderr, "fork failed\n");
			exit(EXIT_FAILURE);
		}

		else if (check == 0)  // Child
		{
			char *args[] = { "argsxorstr", word1, word2, NULL };
			execve(args[0], args, NULL);
		}

		else  // Parent
		{
			int status;
			wait(&status);
			result = WEXITSTATUS(status);
			printf("\nXor result: %d\n", result);
		}
	} while (1);

	return EXIT_SUCCESS;
}
