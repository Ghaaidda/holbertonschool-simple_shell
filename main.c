#include "simpleshell.h"

/**
 * main - shell process entry point
 * @argc: number of shell process arguments
 * @argv: shell process arguments
 * @envp: environment variables
 *
 * Return: 0 on success, exit code on failure
 */
int main(int argc, char **argv, char **envp)
{
	char *lineptr = NULL, *fullcommand = NULL, *token;
	size_t n = 0;
	ssize_t nchars_read;
	char *c_argv[1024];
	int i, status, exit_status = 0;
	pid_t pid;

	(void)argc;

	while (1)
	{
		/* interactive prompt */
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		nchars_read = getline(&lineptr, &n, stdin);
		if (nchars_read == -1) /* Handle EOF (Ctrl+D) */
		{
			free(lineptr);
			exit(exit_status);
		}

		/* remove trailing newline character */
		if (nchars_read > 0 && lineptr[nchars_read - 1] == '\n')
			lineptr[nchars_read - 1] = '\0';

		/* tokenize command*/
		i = 0;
		token = strtok(lineptr, " \t\r\n\a");
		while (token != NULL && i < 1023)
		{
			c_argv[i] = token;
			token = strtok(NULL, " \t\r\n\a");
			i++;
		}
		c_argv[i] = NULL;

		if (c_argv[0] == NULL)
			continue;

		/* handle exit built-in */
		if (strcmp(c_argv[0], "exit") == 0)
		{
			free(lineptr);
			exit(exit_status);
		}

		/* handle env built-in */
		if (strcmp(c_argv[0], "env") == 0)
		{
			for (i = 0; envp[i] != NULL; i++)
			{
				printf("%s\n", envp[i]);
			}
			continue;
		}

		/* full path commands handeling logic */
		fullcommand = find_path(c_argv[0], envp);
		if (fullcommand == NULL)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", argv[0], c_argv[0]);
			exit_status = 127;
			continue;
		}

		/* child process creation */
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
				fprintf(stderr, "%s: 1: %s: not found\n", argv[0], c_argv[0]);
				free(fullcommand);
				free(lineptr);
				exit(127);
			}
		}
		else
		{
			wait(&status);
			free(fullcommand);
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
		}
	}

	free(lineptr);
	return (exit_status);
}
