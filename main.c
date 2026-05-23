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
	char *lineptr = NULL, *c_argv[1024];
	size_t n = 0;
	ssize_t nchars_read;
	int i, exit_status = 0;

	(void)argc;
	while (1)
	{
		nchars_read = read_command(&lineptr, &n);
		if (nchars_read == -1)
			exit(exit_status);
		i = token_command(lineptr, c_argv);
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
		exit_status = exec_command(c_argv, envp, argv[0]);
	}
	free(lineptr);
	return (exit_status);
}
