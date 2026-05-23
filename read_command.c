#include "simpleshell.h"

/**
* read_command - reads a command line from stdin
* @lineptr: double pointer to input buffer
* @n: pointer to the size of the buffer
*
* Return: number of characters read or -1 on EOF
*/
ssize_t read_command(char **lineptr, size_t *n)
{
	ssize_t nchars_read;

	/* interactive prompt */
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
	nchars_read = getline(lineptr, n, stdin);

	if (nchars_read == -1) /* Handle EOF (Ctrl+D) */
	{
		free(*lineptr);
		return (-1);
	}

	/* remove trailing newline character */
	if (nchars_read > 0 && (*lineptr)[nchars_read - 1] == '\n')
		(*lineptr)[nchars_read - 1] = '\0';

	return (nchars_read);
}
