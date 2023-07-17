#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>
#include <stddef.h>
#include <error.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define END_OF_FILE -2

#define EXIT -3

extern char **environ;

/**
 * struct list_s - A new struct type defining a linked list
 * @path: A directory path
 * @next: A pointer to another struct list_s
 */
typedef struct list_s
{
	char *path;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - A new struct type defining builtin commands
 * @name: buitin command name
 * @cmd_fn: A function pointer to the builtin command function
 */
typedef struct builtin_s
{
	char *name;
	int (*cmd_fn)(char **argv, char **front);
} buitin_t;

/**
 * struct alias_s - aliases struct
 * @name: The name of the alias
 * @val: The value of the alias
 * @next: A pointer to another struct alias_s
 */
typedef struct alias_s
{
	char *name;
	char *val;
	struct alias_s *next;
} alias_t;
alias_t *aliases;
alias_t *add_alias_end(alias_t **head, char *name, char *val);

void shell_prompt(int sign);
int exec_cmd(char **args, char **front);
char **dup_env(void);
void env_free(void);
char **get_env(const char *var);
int main(int argc, char *argv[]);
int number_length(int num);
int generate_error(char **args, int err_val);
char *int_to_str(int num);


#endif
