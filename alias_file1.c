#include "shell.h"

/**
  * custom_alias - prints aliases and sets aliases
  * @args: pointer to string arrays
  * @first: the first argument in args
  * Return: 0, -1 otherwise
  */
int custom_alias(char **args, char __attribute__((__unused__)) **first)
{
	alias_t *tmp = aliases;
	int itr, retVal = 0;
	char *value;

	if (!args[0])
	{
		while (tmp)
		{
			printAlias(tmp);
			tmp = tmp->next;
		}
		return (retVal);
	}
	for (itr = 0; args[itr]; itr++)
	{
		tmp = aliases;
		value = _strchr(args[itr], '=');
		if (!value)
		{
			while (tmp)
			{
				if (_strcmp(args[itr], tmp->name) == 0)
				{
					printAlias(tmp);
					break;
				}
				tmp = tmp->next;
			}
			if (!tmp)
				retVal = write_error(args + 1, 1);
		}
		else
			getAlias(args[itr], value);
	}
	return (retVal);
}
/**
  * getAlias - sets new command name and value
  *	changes value of existing command
  * @name: name of the aliase command
  * @value: Alias Value
  */
void getAlias(char *name, char *value)
{
	alias_t *tmp = aliases;
	int length, a, b;
	char *newVal;

	*value = '\0';
	value++;
	length = _strlen(value) - _strspn(value, "'\"");
	newVal = malloc(sizeof(char) * (length + 1));
	if (!newVal)
		return;
	for (a = 0, b = 0; value[a]; a++)
	{
		if (value[a] != '\'' && value[a] != '"')
			newVal[b++] = value[a];
	}
	newVal[b] = '\0';
	while (tmp)
	{
		if (_strcmp(name, tmp->name) == 0)
		{
			free(tmp->value);
			tmp->value = newVal;
			break;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		addAliasEnd(&aliases, name, value);
	else
		free(newVal);
}

/**
  * printAlias - prints alias
  * @alias: pointer to alias
  */
void printAlias(alias_t *alias)
{
	char *the_string;
	int length = _strlen(alias->name) + _strlen(alias->value) + 4;

	the_string = malloc(sizeof(char) * (length + 1));
	if (!the_string)
		return;
	_strcpy(the_string, alias->name);
	_strcat(the_string, "='");
	_strcat(the_string, alias->value);
	_strcat(the_string, "'\n");
	write(STDOUT_FILENO, the_string, length);
	free(the_string);
}
/**
  * aliasesReplace - replaces matching aliases with value
  * @args: pointer to arrays of argument strings
  * Return: args
  */
char **aliasesReplace(char **args)
{
	alias_t *tmp;
	int itr;
	char *newVal;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (itr = 0; args[itr]; itr++)
	{
		tmp = aliases;
		while (tmp)
		{
			if (_strcmp(args[itr], tmp->name) == 0)
			{
				newVal = malloc(sizeof(char) * (_strlen(tmp->value) + 1));
				if (!newVal)
				{
					argsFree(args, args);
					return (NULL);
				}
				_strcpy(newVal, tmp->value);
				free(args[itr]);
				args[itr] = newVal;
				itr--;
				break;
			}
			tmp = tmp->next;
		}
	}
	return (args);
}
