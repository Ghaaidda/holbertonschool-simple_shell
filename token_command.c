#include "simpleshell.h"

/**
* token_command - tokenizes a commmand line into arguments
* @lineptr: inbut command line string
* @c_argv: array to store command arguments
*
* Return: number of arguments
*/
int token_command(char *lineptr, char **c_argv)
{
	char *token;
	int i;

	/* tokenize command*/
	token = strtok(lineptr, " \t\r\n\a");
	i = 0;
	while (token != NULL && i < 1023)
	{
		c_argv[i] = token;
		token = strtok(NULL, " \t\r\n\a");
		i++;
	}
	c_argv[i] = NULL;

	return (i);
}
