#include "shell.h"

/**
 * env_free - a function that frees the copied environment
 * Return: nothing
 */
void env_free(void)
{
	int index;

	for (index = 0; environ[index]; index++)
		free(environ[index]);
	free(environ);
}

/**
 * get_env - a function used to get an environmental variable
 * @var: the name of the environmental var to get
 * Return: A pointer to the environmental variable, NULL if the var is absent
 */
char **get_env(const char *var)
{
	int index;
	int length;

	length = _strlen(var);
	for (index = 0; environ[index]; index++)
	{
		if (_strcmp(var, environ[index], length) == 0)
			return (&environ[index]);
	}

	return (NULL);
}
