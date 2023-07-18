#include "shell.h"

/**
 * dup_env - a function that creates a copy of the environment
 * Return: A pointer to the new copy, otherwise incase of error NULL
 */
char **dup_env(void)
{
	char **new_env;
	size_t size;
	int index;

	for (size = 0; environ[size]; size++)
		;
	new_env = malloc(sizeof(char *) * (size + 1));
	if (!new_env)
		return (NULL);

	for (index = 0; environ[index]; index++)
	{
		new_env[index] = malloc(_strlen(environ[index]) + 1);

		if (!new_env[index])
		{
			for (index--; index >= 0; index--)
				free(new_env[index]);
			free(new_env);
			return (NULL);
		}
		_strcpy(new_env[index], environ[index]);
	}
	new_env[index] = NULL;

	return (new_env);
}
