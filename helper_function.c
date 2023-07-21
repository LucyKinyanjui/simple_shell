#include "shell.h"

/**
  * args_free -  a function that frees arguments memory
  * @args: pointer to argument strings
  * @head: The first argument
  */
void args_free(char **args, char **head)
{
	size_t i;

	for (i = 0; args[i]; i++)
		free(args[i]);
	free(head);
}
/**
  * get_pid - locates the current process id
  * Description - This function opens the stat file, which is a
  *	space-delimited file containing information about the current process.
  *	The first word in the file is the PID (Process ID). The function reads
  *	the PID into a buffer and replaces the space at the end with a null byte.
  * Return: current process id, Null otherwise
  */
char *get_pid(void)
{
	size_t i = 0;
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
	while (buffer[i] != ' ')
		i++;
	buffer[i] = '\0';

	close(file);
	return (buffer);
}
/**
  *env_val - a function that returns value of environmental variable
  * @env:  the env variable to search for
  * @len:  the env variable length
  * Return: the env variable value, otherwise NULL
  */
char *env_val(char *env, int len)
{
	char **var_address;
	char *change = NULL, *tmp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, env, len);
	var_address = get_env(var);
	if (var_address != NULL)
	{
		tmp = *var_address;
		while (*tmp != '=')
			tmp++;
		tmp++;
		if (*tmp)
		{
			change = malloc(_strlen(tmp) + 1);
			if (change)
				_strcpy(change, tmp);
		}
	}
	free(var);
	return (change);
}
/**
  * change_var - a function that does variable replacement
  * @line: pointer to input strings
  * @exec_ret: pointer to last executed command return value
  */
void change_var(char **line, int *exec_ret)
{
	int x, y = 0, len;
	char *change = NULL, *prev_ln = NULL, *current_ln;

	prev_ln = *line;
	for (x = 0; prev_ln[x]; x++)
	{
	if (prev_ln[x] == '$' && prev_ln[x + 1] && prev_ln[x + 1] != ' ')
	{
	if (prev_ln[x + 1] == '$')
	{
		change = get_pid();
		y = x + 2;
	}
	else if (prev_ln[x + 1] == '?')
	{
		change = int_to_str(*exec_ret), y = x + 2;
	}
	else if (prev_ln[x + 1])
	{
	for (y = x + 1; prev_ln[y] && prev_ln[y] != '$' && prev_ln[y] != ' '; y++)
		;
	len = y - (x + 1);
	change = env_val(&prev_ln[x + 1], len);
	}
	current_ln = malloc(x + _strlen(change) + _strlen(&prev_ln[y]) + 1);
	if (!current_ln)
		return;
	current_ln[0] = '\0';
	_strncat(current_ln, prev_ln, x);
	if (change)
	{
		_strcat(current_ln, change);
		free(change);
		change = NULL;
	}
	_strcat(current_ln, &prev_ln[y]);
	free(prev_ln);
	*line = prev_ln = current_ln, x = -1;
	}
	}
}
