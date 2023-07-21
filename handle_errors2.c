#include "shell.h"

/**
 * error_126 - a function that creates permission denied error messages
 * @args: a pointer to arguments passed to the command
 * Return: the error string
 */
char *error_126(char **args)
{
	int hist = 1;
	char *error_msg, *str_hist;
	char *name = "My_Shell";
	int len;

	str_hist = int_to_str(hist);
	if (!str_hist)
		return (NULL);
	len = _strlen(name) + _strlen(str_hist) + _strlen(args[0]) + 24;
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
	_strcat(error_msg, ": Permission denied\n");

	free(str_hist);
	return (error_msg);
}

/**
 * error_127 - a function that creates error messages for command not found
 * @args: a pointer to arguments passed to the command
 * Return: the error string
 */
char *error_127(char **args)
{
	int hist = 1;
	char *error_msg, *str_hist;
	int len;
	char *name = "My_Shell";

	str_hist = int_to_str(hist);
	if (!str_hist)
		return (NULL);
	len = _strlen(name) + _strlen(str_hist) + _strlen(args[0]) + 16;
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
	_strcat(error_msg, ": not found\n");

	free(str_hist);
	return (error_msg);
}
