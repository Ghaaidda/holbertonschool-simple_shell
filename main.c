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
	ssize_t nread;
	pid_t pid;
	int status;
	char *c_argv[2];
	char *cmd_ptr;
	size_t j;
	(void)argc;

	while (1)
	{
		/* interactive mode */
		if (isatty(STDIN_FILENO))
		{
			printf("$ ");
			fflush(stdout); /* skip stdout buffer */
		}

		/* read user input */
		nread = getline(&lineptr, &len, stdin);
		if (nread == -1)
		{
			free(lineptr);
			return (EXIT_SUCCESS);
		}

		/* preprosessing: remove trailing newline */
		if (nread > 0 && lineptr[nread - 1] == '\n')
		{
			lineptr[nread - 1] = '\0';
		}

		/* alias pointer to protect original allocation */
		cmd_ptr = lineptr;

		/* skip leading spaces and tabs */
		while (*cmd_ptr == ' ' || *cmd_ptr == '\t')
		{
			cmd_ptr++;
		}

		/* if line was entirely empty or spaces, loop back */
		if (*cmd_ptr == '\0')
			continue;

		/* find the end of a command */
		j = 0;
		while (cmd_ptr[j] != ' ' && cmd_ptr[j] != '\t' && cmd_ptr[j] != '\0')
		{
			j++;
		}

		cmd_ptr[j] = '\0';

		/* child process creation*/
		c_argv[0] = cmd_ptr;
		c_argv[1] = NULL;

		pid = fork();
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
				fprintf(stderr, "%s: 1: %s: not found\n", argv[0], cmd_ptr);
				free(lineptr);
				exit(127);
			}
		}
		else
		{
			/* parent process waiting */
			wait(&status);
		}
	}

	/* no memory leaks */
	free(lineptr);
	return (EXIT_SUCCESS);
}
