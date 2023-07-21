#include "shell.h"

/**
 * run_cmd_error - a function that prints an error if the file cant open
 * @file_path: the path to the file that fails to open
 * Return: 127 error
 */
int run_cmd_error(char *file_path)
{
	int len;
	char *error_msg;
	int hist = 0;
	char *str_hist;
	char *name = "./hsh";

	str_hist = int_to_str(hist);
	if (!str_hist)
		return (127);

	len = _strlen(name) + _strlen(str_hist) + _strlen(file_path) + 16;
	error_msg = malloc(sizeof(char) * (len + 1));
	if (!error_msg)
	{
		free(str_hist);
		return (127);
	}

	_strcpy(error_msg, name);
	_strcat(error_msg, ": ");
	_strcat(error_msg, str_hist);
	_strcat(error_msg, ": Can't open ");
	_strcat(error_msg, file_path);
	_strcat(error_msg, "\n");

	free(str_hist);
	write(STDERR_FILENO, error_msg, len);
	free(error_msg);
	return (127);
}
