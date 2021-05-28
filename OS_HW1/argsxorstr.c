#include <stdio.h>
#include <stdlib.h>
#include "mystrlib.h"

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s [str1] [str2]\n", argv[0]);
		exit (-1);
	}
	return mystrxor(argv[1], argv[2]); 
}
