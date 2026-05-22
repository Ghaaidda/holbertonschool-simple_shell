# Holberton School - Simple Shell Project

This a basic command line interpreter it enables the user to excute UNIX commands.

## Compilation
Clone the repo
'''
git clone https://github.com/Ghaaidda/holbertonschool-simple_shell
'''
Go to shell directory
'''
cd holbertonschool-simple_shell
'''
Compile program with gcc
'''
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
'''
Run the program
'''
./hsh
'''
## Requirements
- GCC Compiler (GNU Compiler Collection)
## Examples
'''
$ ls
AUTHORS		exec_command.c	hsh		read_command.c	simpleshell.h
README.md	find_path.c	main.c		search_path.c	token_command.c
$ which ls
/bin/ls
$ /bin/ls
AUTHORS		exec_command.c	hsh		read_command.c	simpleshell.h
README.md	find_path.c	main.c		search_path.c	token_command.c
$ ls -l
total 144
-rw-r--r--  1 mcghaida  staff    137 May 22 15:24 AUTHORS
-rw-r--r--  1 mcghaida  staff    169 May 22 15:24 README.md
-rw-r--r--  1 mcghaida  staff   1028 May 22 15:24 exec_command.c
-rw-r--r--  1 mcghaida  staff    972 May 22 15:24 find_path.c
-rwxr-xr-x  1 mcghaida  staff  34768 May 22 15:36 hsh
-rw-r--r--  1 mcghaida  staff    944 May 22 15:24 main.c
-rw-r--r--  1 mcghaida  staff    675 May 22 15:24 read_command.c
-rw-r--r--  1 mcghaida  staff    828 May 22 15:24 search_path.c
-rw-r--r--  1 mcghaida  staff    452 May 22 15:24 simpleshell.h
-rw-r--r--  1 mcghaida  staff    490 May 22 15:24 token_command.c
'''
## Testing
Passed all Holberton School tests.
