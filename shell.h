#ifndef _SHELL_H_
#define _SHELL_H_

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
list_t *add_node_end(list_t **head, char *path);

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
int run_cmd(char *file_path, int *exec_ret);
int run_cmd_error(char *file_path);
char **dup_env(void);
void env_free(void);
char **get_env(const char *var);
int main(int argc, char *argv[]);
int number_length(int num);
int generate_error(char **args, int err_val);
char *int_to_str(int num);
char *env_error(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
char *get_cmd(char *command);
char *path_fill(char *path);
list_t *get_dir(char *path);
void args_free(char **args, char **head);
char get_pid(void);
char *env_val(char *env, int len);
void change_var(char **line, int *exec_ret);
int _strlen(const char *str);
char *_strcpy( char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strchr(char *str, char chr);
int _strspn(char *str, char *prefix);
int _strcmp(char *str1, char str2);
int _strncmp(const char *str1, const char *str2, size_t n);
int tok_length(char *str, char *deli);
int count_tokens(char *str, char *deli);
char **str_tok(char *str, char *deli);
void free_alias_list(alias_t *head);
void free_list(list_t *head);
void handle_line(char **line, ssize_t read);
ssize_t get_new_length(char *line);
void search_logical_ops(char *line, ssize_t *new_length);
char *find_args(char *line, int *exec_ret);
int run_args(char **args, char **first, int *exec_ret);
int handle_arguments(int *exec_ret);
int check_args(char **args);

#endif
