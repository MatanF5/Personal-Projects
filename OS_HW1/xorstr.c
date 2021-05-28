#include <stdio.h>
#include <stdlib.h>
#include "mystrlib.h"

#define LINELEN (4)

int main(int argc, char *argv[])
{
	char str1[LINELEN + 1];
	char str2[LINELEN + 1];

	if (argc != 1)
	{
		fprintf(stderr, "Usage: %s\n", argv[0]);
		exit (-1);
	}
	while (1)
	{
		if (mygets(str1, LINELEN) == NULL)
			break;
		if (mygets(str2, LINELEN) == NULL)
			break;
		printf("%d\n", mystrxor(str1, str2));
		fflush(stdout);
	} 
	return 0;
}
