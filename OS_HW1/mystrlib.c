
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mystrlib.h"

char *mygets(char *buf, int len)
{
	char *retval;

	retval = fgets(buf, len, stdin);
	buf[len] = '\0';
	if (buf[strlen(buf)-1] == 10) /* trim \r */
		buf[strlen(buf)-1] = '\0';
	else if(retval) while(getchar() != '\n'); /* get to eol */

	return retval;
}

int mystrxor(char *str1, char *str2)
{
	char retval;
	int len;
	int i;

	retval = '\0';
	len = strlen(str1);
	for (i = 0; i < len ; i++)
	{
		retval = retval ^ str1[i];
	}
	len = strlen(str2);
	for (i = 0; i < len ; i++)
	{
		retval = retval ^ str2[i];
	}
	return (int)(retval);
}


