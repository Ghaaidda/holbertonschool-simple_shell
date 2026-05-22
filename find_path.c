#include "simpleshell.h"
/**
 * find_path - finds a command within the PATH environment variable
 * @command: command entered by user
 * @envp: environment variables
 *
 * Return: string of full command or NULL if not found
 */
char *find_path(char *command, char **envp)
{
	char *path = NULL;
	int i;

	if (command == NULL)
		return (NULL);

	/* if command is in a full path format */
	if (strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}
	/* get PATH variable in the environment array */
	i = 0;
	while (envp[i] != NULL)
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5;
			break;
		}
		i++;
	}
	/* handle if PATH doesnt exits or its empty */
	if (path == NULL || *path == '\0')
	{
		/* only execute if its an explicit path */
		if (strchr(command, '/') != NULL && access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}
	return (search_path(command, path));
}
