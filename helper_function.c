#include "shell.h"

/**
  * argsFree - frees args memory
  * @args: pointer to argument strings
  * @first: The first argument
  */
void argsFree(char **args, char **first)
{
	size_t itr;

	for (itr = 0; args[itr]; itr++)
		free(args[itr]);
	free(first);
}
/**
  * locate_pid - locates the current process id
  * Description - This function opens the stat file, which is a
  *	space-delimited file containing information about the current process.
  *	The first word in the file is the PID (Process ID). The function reads
  *	the PID into a buffer and replaces the space at the end with a null byte.
  * Return: current process id, Null otherwise
  */
char *locate_pid(void)
{
	size_t itr = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cannot read the file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[itr] != ' ')
		itr++;
	buffer[itr] = '\0';

	close(file);
	return (buffer);
}
/**
  *env_value - returns value of environmental variable
  * @env_id: env variable to search for
  * @length: env variable length
  * Return: env variable value, NULL otherwise
  */
char *env_value(char *env_id, int length)
{
	char **variable_addr;
	char *substitute = NULL, *tmp, *variable;

	variable = malloc(length + 1);
	if (!variable)
		return (NULL);
	variable[0] = '\0';
	_strncat(variable, env_id, length);
	variable_addr = locate_env(variable);
	if (variable_addr != NULL)
	{
		tmp = *variable_addr;
		while (*tmp != '=')
			tmp++;
		tmp++;
		if (*tmp)
		{
			substitute = malloc(_strlen(tmp) + 1);
			if (substitute)
				_strcpy(substitute, tmp);
		}
	}
	free(variable);
	return (substitute);
}
/**
  * var_substitute - does variable replacement
  * @stream: pointer to input strings
  * @execRet: pointer to last executed command return value
  */
void var_substitute(char **stream, int *execRet)
{
	int a, b = 0, length;
	char *substitute = NULL, *prev_ln = NULL, *current_ln;

	prev_ln = *stream;
	for (a = 0; prev_ln[a]; a++)
	{
	if (prev_ln[a] == '$' && prev_ln[a + 1] && prev_ln[a + 1] != ' ')
	{
	if (prev_ln[a + 1] == '$')
	{
		substitute = locate_pid();
		b = a + 2;
	}
	else if (prev_ln[a + 1] == '?')
	{
		substitute = intToStr(*execRet), b = a + 2;
	}
	else if (prev_ln[a + 1])
	{
	for (b = a + 1; prev_ln[b] && prev_ln[b] != '$' && prev_ln[b] != ' '; b++)
		;
	length = b - (a + 1);
	substitute = env_value(&prev_ln[a + 1], length);
	}
	current_ln = malloc(a + _strlen(substitute) + _strlen(&prev_ln[b]) + 1);
	if (!current_ln)
		return;
	current_ln[0] = '\0';
	_strncat(current_ln, prev_ln, a);
	if (substitute)
	{
		_strcat(current_ln, substitute);
		free(substitute);
		substitute = NULL;
	}
	_strcat(current_ln, &prev_ln[b]);
	free(prev_ln);
	*stream = prev_ln = current_ln, a = -1;
	}
	}
}
