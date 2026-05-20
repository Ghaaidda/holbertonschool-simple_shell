#include "simpleshell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


char *tok_line(char *c){
	char *line = c;
	char *token;
	
	token = strtok(line, " ");
	return(token);
}
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
	int i;
	int maxargs = 64;
	char *delim = " \t\r\n\a";
	char *token = NULL;
	char *fullcommand;
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
		token = tok_line(cmd_ptr);

		i = 0;
		while (token !=  NULL && i < maxargs - 1)
		{
			c_argv[i] = token;
			i++;
			token = strtok(NULL, delim);
		}

		c_argv[i] = NULL;

		if (c_argv[0] == NULL)
			continue;

		fullcommand = find_path(c_argv[0], envp);
		if (fullcommand == NULL)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", argv[0], c_argv[0]);
			continue;
		}

		/* child process creation*/
		pid = fork();
		if (pid == -1)
		{
			perror("fork failed");
			free(fullcommand);
			free(lineptr);
			return (EXIT_FAILURE);
		}

		if (pid == 0)
		{
			if (execve(fullcommand, c_argv, envp) == -1)
			{
				fprintf(stderr, "%s: 1: %s: not found\n", argv[0], cmd_ptr);
				free(fullcommand);
				free(lineptr);
				exit(127);
			}
		}
		else
		{
			/* parent process waiting */
			wait(&status);
			free(fullcommand);
		}
	}

	/* no memory leaks */
	free(lineptr);
	return (EXIT_SUCCESS);
}
