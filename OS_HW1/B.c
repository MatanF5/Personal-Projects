#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "mystrlib.h"

void checkTest(int parentToChild[], int childToParent[]);

int main(int argc, char *argv[])
{
	int parentToChild[2], childToParent[2];
	pid_t check;

	if (pipe(parentToChild) == -1 || pipe(childToParent) == -1)
	{
		fprintf(stderr, "pipe failed\n");
		exit(EXIT_FAILURE);
	}

	check = fork();

	if (check < 0)	// Child Process
	{
		fprintf(stderr, "fork failed\n");
		exit(EXIT_FAILURE);
	}
	else if (check == 0)
	{
		checkTest(parentToChild, childToParent);
	}
	else
	{
		if (close(childToParent[1]) == -1)
		{
			fprintf(stderr, "Child to parent 1 close failed\n");
			exit(EXIT_FAILURE);
		}

		if (close(parentToChild[0]) == -1)
		{
			fprintf(stderr, "Parent to child 0 close failed\n");
			exit(EXIT_FAILURE);
		}

		while (!feof(stdin))
		{
			char word1[MAX_LEN + 1], word2[MAX_LEN + 1], temp[MAX_LEN + 1];

			printf("Enter The First String:\n");
			mygets(word1, MAX_LEN);

			printf("Enter The Second String:\n");
			mygets(word2, MAX_LEN);

			fflush(stdin);

			strcat(word1, "\n");
			strcat(word2, "\n");

			write(parentToChild[1], word1, strlen(word1));
			write(parentToChild[1], word2, strlen(word2));

			read(childToParent[0], temp, sizeof(temp));
			printf("%s", temp);

			memset(temp, 0, sizeof(temp));
		}
	}
	return EXIT_SUCCESS;
}

void checkTest(int parentToChild[], int childToParent[])
{
	if (parentToChild[0] != fileno(stdin))
	{
		if (dup2(parentToChild[0], fileno(stdin)) == -1)
		{
			fprintf(stderr, "Parent to child 0 dup2 failed\n");
			exit(EXIT_FAILURE);
		}
	}

	if (close(childToParent[0]) == -1)
	{
		fprintf(stderr, "Child to parent 0 close failed\n");
		exit(EXIT_FAILURE);
	}

	if (close(parentToChild[0]) == -1)
	{
		fprintf(stderr, "Parent to child 0 close failed\n");
		exit(EXIT_FAILURE);
	}

	if (childToParent[1] != fileno(stdout))
	{
		if (dup2(childToParent[1], fileno(stdout)) == -1)
		{
			fprintf(stderr, "dup2 failed\n");
			exit(EXIT_FAILURE);
		}
	}

	if (close(parentToChild[1]) == -1)
	{
		fprintf(stderr, "Parent to child 1 close failed\n");
		exit(EXIT_FAILURE);
	}

	if (close(childToParent[1]) == -1)
	{
		fprintf(stderr, "Child to parent 1 close failed\n");
		exit(EXIT_FAILURE);
	}

	char *args[] = { "xorstr", NULL };
	execve(args[0], args, NULL);
}
