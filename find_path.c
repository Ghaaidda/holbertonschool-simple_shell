
#include <stdlib.h>
#include <string.h>
char *find_path(char *command, char **envp)
{
	char *tokens;
	char *path;
	char *filepath;
	char *pathcp;
	int i;
	
	if (strchr(command, '/') != NULL)
		return(NULL);

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
	pathcp = strdup(path);
	if (pathcp == NULL)
		return(NULL);
	tokens = strtok(pathcp, ":");
	while (tokens != NULL)
		filepath = malloc(strlen(tokens) + strlen(command) + 2);

}
