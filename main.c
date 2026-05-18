#include "simpleshell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
* main - shell process entry point
* @argc: number of shell program arguments
* @argv: shell program arguments
* @envp: shell program environment variables
*
* Return: 0 on success, 1 on failure
*/
int main(int argc, char *argv[], char **envp)
{
	char *lineptr = NULL;
	size_t len = 0;
	ssize_t command;
	pid_t pid;
	int status;
	(void)argc;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("$ ");
			fflush(stdout);
		}

		command = getline(&lineptr, &len, stdin);
		if (command == -1)
		{
			free(lineptr);
			return (EXIT_SUCCESS);
		}

		if (command > 0 && lineptr[command - 1] == '\n')
		{
			lineptr[command - 1] = '\0';
		}
	
		if (lineptr[0] == '\0')
			continue;

		char *c_argv[2];
		c_argv[0] = lineptr;
		c_argv[1] = NULL;

		pid = fork();
		/* FIX 2: fork failure returns -1, not 1 */
		if (pid == -1)
		{
			perror("fork failed");
			free(lineptr);
			return (EXIT_FAILURE);
		}

		if (pid == 0)
		{
			if (execve(c_argv[0], c_argv, envp) == -1)
			{
				fprintf(stderr, "%s: 1: %s: not found\n", argv[0], lineptr);
				free(lineptr);
				exit(127);
			}
		}
		else
		{
			wait(&status);
		}
	}
	free(lineptr);
	return (EXIT_SUCCESS);
}

