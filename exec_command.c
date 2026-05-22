#include "simpleshell.h"
/**
* exec_command - forks and executes a command
* @c_argv: command and arguments array
* @envp: environment variables
* @prg_name: programe name for error message
*
* Return: exit status or 127 if command not found
*/
pid_t exec_command(char **c_argv, char **envp, char *prg_name)
{
	pid_t pid;
	char *fullcommand;
	int status, exit_status = 0;

	/* full path commands handeling logic */
	fullcommand = find_path(c_argv[0], envp);
	if (fullcommand == NULL)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", prg_name, c_argv[0]);
		return (127);
	}
	/* child process creation */
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		free(fullcommand);
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(fullcommand, c_argv, envp) == -1)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", prg_name, c_argv[0]);
			free(fullcommand);
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

	return (exit_status);
}
