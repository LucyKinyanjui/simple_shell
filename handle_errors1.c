#include "shell.h"

/**
 * env_error - a function that creates environmental error messages
 * @args: a pointer to argument strings passed to command
 * Return: The error string
 */
char *env_error(char **args)
{
	int hist = 1;
	char *error_msg, *str_hist;
	int len;
	char *name = "My_Shell";

	str_hist = int_to_str(hist);
	if (!str_hist)
		return (NULL);
	args--;
	len = _strlen(name) + _strlen(str_hist) + _strlen(args[0]) + 45;
	error_msg = malloc(sizeof(char) * (len + 1));
	if (!error_msg)
	{
		free(str_hist);
		return (NULL);
	}

	_strcpy(error_msg, name);
	_strcat(error_msg, ": ");
	_strcat(error_msg, str_hist);
	_strcat(error_msg, ": ");
	_strcat(error_msg, args[0]);
	_strcat(error_msg, ": Unable to add/remove from environment\n");
	free(str_hist);

	return (error_msg);
}

/**
 * error_1 - a function that creates alias error messages
 * @args: a pointer to argument strings passed to command
 * Return: The error string
 */
char *error_1(char **args)
{
	char *error_msg;
	char *name = "My_Shell";
	int len;

	len = _strlen(name) + _strlen(args[0]) + 13;
	error_msg = malloc(sizeof(char) * (len + 1));
	if (error_msg)
		return (error_msg);
	_strcpy(error_msg, "alias: ");
	_strcat(error_msg, name);
	_strcat(error_msg, " not found\n");

	return (error_msg);
}

/**
 * error_2_exit - a function that creates error messages
 * @args: a pointer to argument strings passed to command
 * Return: The error string
 */
char *error_2_exit(char **args)
{
	int hist = 1;
	char *error_msg, *str_hist;
	int len;
	char *name = "My_Shell";

	str_hist = int_to_str(hist);
	if (!str_hist)
		return (NULL);
	len = _strlen(name) + _strlen(str_hist) + _strlen(args[0]) + 27;
	error_msg = malloc(sizeof(char) * (len + 1));
	if (error_msg)
	{
		free(str_hist);
		return (NULL);
	}
	_strcpy(error_msg, name);
	_strcat(error_msg, ": ");
	_strcat(error_msg, str_hist);
	_strcat(error_msg, ": exit: Illegal number: ");
	_strcat(error_msg, args[0]);
	_strcat(error_msg, "\n");

	free(str_hist);
	return (error_msg);
}

/**
 * error_2_cd - a function that creates cd error messages
 * @args: a pointer to argument strings passed to command
 * Return: The error string
 */
char *error_2_cd(char **args)
{
	int hist = 1;
	char *error_msg, *str_hist;
	int len;
	char *name = "My_Shell";

	str_hist = int_to_str(hist);
	if (!str_hist)
		return (NULL);
	if (args[0][0] == '-')
		args[0][2] = '\0';
	len = _strlen(name) + _strlen(str_hist) + _strlen(args[0]) + 24;
	error_msg = malloc(sizeof(char) * (len + 1));
	if (!error_msg)
	{
		free(str_hist);
		return (NULL);
	}
	_strcpy(error_msg, args[0]);
	_strcat(error_msg, ": ");
	_strcat(error_msg, str_hist);
	if (args[0][0] == '-')
		_strcat(error_msg, ": : cd: Illegal option ");
	else
		_strcat(error_msg, ": cd: can't cd to ");
	_strcat(error_msg, name);
	_strcat(error_msg, "\n");

	free(str_hist);
	return (error_msg);
}

/**
 * error_2_syntax - a function that creates syntax error messages
 * @args: a pointer to argument strings passed to command
 * Return: The error string
 */
char *error_2_syntax(char **args)
{
	int hist = 1;
	char *error_msg, *str_hist;
	int len;
	char *name = "My_Shell";

	str_hist = int_to_str(hist);
	if (!str_hist)
		return (NULL);
	len = _strlen(name) + _strlen(str_hist) + _strlen(args[0]) + 33;
	error_msg = malloc(sizeof(char) * (len + 1));
	if (!error_msg)
	{
		free(str_hist);
		return (NULL);
	}
	_strcpy(error_msg, name);
	_strcat(error_msg, ": ");
	_strcat(error_msg, str_hist);
	_strcat(error_msg, ": Syntax error: \"");
	_strcat(error_msg, args[0]);
	_strcat(error_msg, "\" unexpected\n");

	free(str_hist);
	return (error_msg);
}
