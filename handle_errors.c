#include "shell.h"

/**
 * number_length - A function that returns the length of a number
 * @num: the number whose length is to be returned
 * Return: The number length
 */
int number_length(int num)
{
	int len = 1;
	unsigned int num1;

	if (num < 0)
	{
		len++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}
	while (num1 > 9)
	{
		len++;
		num1 /= 10;
	}
	return (len);
}

/**
 * generate_error - a function that writes error message to stderr
 * @args: Arguments
 * @err_val: value of the error
 * Return: the error value
 */
int generate_error(char **args, int err_val)
{
	char *error_msg;

	switch (err_val)
	{
		case -1:
			error_msg = env_error(args);
			break;
		case 1:
			error_msg = error_1(args);
			break;
		case 2:
			if (*args[0] == 'e')
				error_msg = error_2_exit(++args);
			else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
				error_msg = error_2_syntax(args);
			else
				error_msg = error_2_cd(args);
			break;
		case 126:
			error_msg = error_126(args);
			break;
		case 127:
			error_msg = error_127(args);
			break;
	}
	write(STDERR_FILENO, error_msg, _strlen(error_msg));
	if (error_msg)
		free(error_msg);
	return (err_val);
}

/**
 * int_to_str - Converts an integer to a string
 * @num: the integer to convert
 * Return: The converted string
 */
char *int_to_str(int num)
{
	unsigned int num1;
	char *buffer;
	int len = number_length(num);

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);
	buffer[len] = '\0';
	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}
	len--;
	do {
		buffer[len] = (num1 % 10) + '0';
		num1 /= 10;
		len--;
	} while (num1 > 0);

	return (buffer);
}
