#include "shell.h"

/**
  * locate_args - gets command from standard input
  * @stream: command storage buffer
  * @execRet: last executed command return value
  * Return: stored command pointer, Null otherwise
  */
char *locate_args(char *stream, int *execRet)
{
	int history = 0;
	size_t numb = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (stream)
	{
		free(stream);
	}
	read = getline_fn(&stream, &numb, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		history++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (locate_args(stream, execRet));
	}
	stream[read - 1] = '\0';
	var_substitute(&stream, execRet);
	lineHandler(&stream, read);
	return (stream);
}
/**
  * argsRunner - does command execution calls
  * @args: pointer to argument strings
  * @first: The first string argument
  * @execRet: the last executed command parent process return value
  * Return: last executed command parent process return value
  */
int argsRunner(char **args, char **first, int *execRet)
{
	int history = 0;
	int itr;
	int retVal;
	int (*builtin_cmd)(char **args, char **first);

	builtin_cmd = locate_custom(args[0]);
	if (builtin_cmd)
	{
		retVal = builtin_cmd(args + 1, first);
		if (retVal != TERMINATE)
			*execRet = retVal;
	}
	else
	{
		*execRet = execute_cmd(args, first);
		retVal = *execRet;
	}
	history++;
	for (itr = 0; args[itr]; itr++)
		free(args[itr]);
	return (retVal);
}
/**
  * argsHandler - locates, calls and carrys out the command execution
  * @execRet: the last executed command parent process return value
  * Return: EOF or -1 or exit value of the last executed command
  */
int argsHandler(int *execRet)
{
	int retVal = 0, itr;
	char **args, *stream = NULL, **first;

	stream = locate_args(stream, execRet);
	if (!stream)
		return (EOF_CUSTOM);
	args = strtok_fn(stream, " ");
	free(stream);
	if (!args)
		return (retVal);
	if (argsChecker(args) != 0)
	{
		*execRet = 2;
		argsFree(args, args);
		return (*execRet);
	}
	first = args;
	for (itr = 0; args[itr]; itr++)
	{
		if (_strncmp(args[itr], ";", 1) == 0)
		{
			free(args[itr]);
			args[itr] = NULL;
			retVal = argsCaller(args, first, execRet);
			args = &args[++itr];
			itr = 0;
		}
	}
	if (args)
		retVal = argsCaller(args, first, execRet);
	free(first);
	return (retVal);
}
/**
  * argsChecker - locates if there are any leading symbols or operators
  * @args: pointer to argument strings
  * Return: -2 or 0
  */
int argsChecker(char **args)
{
	size_t itr;
	char *curr, *next;

	for (itr = 0; args[itr]; itr++)
	{
		curr = args[itr];
		if (curr[0] == ';' || curr[0] == '&' || curr[0] == '|')
		{
			if (itr == 0 || curr[1] == ';')
				return (write_error(&args[itr], 2));
			next = args[itr + 1];
			if (next && (next[0] == ';' || next[0] == '&' || next[0] == '|'))
				return (write_error(&args[itr + 1], 2));
		}
	}
	return (0);
}
