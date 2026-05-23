#include "simpleshell.h"
/**
 * search_path - searches for a command in PATH directories
 * @command: command to search for
 * @path: PATH value
 *
 * Return: command path or NULL if not found
 */
char *search_path(char *command, char *path)
{
	char *tokens, *filepath, *pathcp;

	pathcp = strdup(path);
	if (pathcp == NULL)
		return (NULL);
	tokens = strtok(pathcp, ":");
	while (tokens != NULL)
	{
		/* allocate space for path + / + command + null */
		filepath = malloc(strlen(tokens) + strlen(command) + 2);
		if (filepath == NULL)
		{
			free(pathcp);
			return (NULL);
		}
		strcpy(filepath, tokens);
		strcat(filepath, "/");
		strcat(filepath, command);

		if (access(filepath, X_OK) == 0)
		{
			free(pathcp);
			return (filepath);
		}
		free(filepath);
		tokens = strtok(NULL, ":");
	}
	free(pathcp);
	return (NULL);
}
