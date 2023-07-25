#include "shell.h"

/**
  * find_args -  a function that gets command from standard input
  * @line: command storage buffer
  * @exec_ret: last executed command return value
  * Return: stored command pointer, Null otherwise
  */
char *find_args(char *line, int *exec_ret)
{
	int hist = 0;
	size_t num = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (line)
	{
		free(line);
	}
	read = _getline(&line, &num, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (find_args(line, exec_ret));
	}
	line[read - 1] = '\0';
	change_var(&line, exec_ret);
	handle_line(&line, read);
	return (line);
}
/**
  * run_args - a function that does command execution calls
  * @args: pointer to argument strings
  * @first: The first string argument
  * @exec_ret: the last executed command parent process return value
  * Return: last executed command parent process return value
  */
int run_args(char **args, char **first, int *exec_ret)
{
	int hist = 0;
	int i;
	int ret_val;
	int (*builtin)(char **args, char **first);

	builtin = find_builtin_cmd(args[0]);
	if (builtin)
	{
		ret_val = builtin(args + 1, first);
		if (ret_val != EXIT)
			*exec_ret = ret_val;
	}
	else
	{
		*exec_ret = run_cmd(args, first);
		ret_val = *exec_ret;
	}
	hist++;
	for (i = 0; args[i]; i++)
		free(args[i]);
	return (ret_val);
}
/**
  * handle_arguments -  a function that locates, calls
  * and carrys out the command execution
  * @exec_ret: the last executed command parent process return value
  * Return: EOF or -1 or exit value of the last executed command
  */
int handle_arguments(int *exec_ret)
{
	int ret_val = 0, i;
	char **args, *line = NULL, **first;

	line = find_args(line, exec_ret);
	if (!line)
		return (END_OF_FILE);
	args = str_tok(line, " ");
	free(line);
	if (!args)
		return (ret_val);
	if (check_args(args) != 0)
	{
		*exec_ret = 2;
		args_free(args, args);
		return (*exec_ret);
	}
	first = args;
	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret_val = call_args(args, first, exec_ret);
			args = &args[++i];
			i = 0;
		}
	}
	if (args)
		ret_val = call_args(args, first, exec_ret);
	free(first);
	return (ret_val);
}
/**
  * check_args - a function that locates if there are any
  * leading symbols or operators
  * @args: pointer to argument strings
  * Return: -2 or 0
  */
int check_args(char **args)
{
	size_t i;
	char *curr, *next;

	for (i = 0; args[i]; i++)
	{
		curr = args[i];
		if (curr[0] == ';' || curr[0] == '&' || curr[0] == '|')
		{
			if (i == 0 || curr[1] == ';')
				return (generate_error(&args[i], 2));
			next = args[i + 1];
			if (next && (next[0] == ';' || next[0] == '&' || next[0] == '|'))
				return (generate_error(&args[i + 1], 2));
		}
	}
	return (0);
}
