#ifndef SIMPLESHELL_H
#define SIMPLESHELL_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


char *find_path(char *command, char **envp);
ssize_t read_command(char **lineptr, size_t *n);
int token_command(char *lineptr, char **c_argv);
pid_t exec_command(char **c_argv, char **envp, char *prg_name);
char *search_path(char *command, char *path);

#endif
