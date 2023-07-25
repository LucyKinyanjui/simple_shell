#include "shell.h"

/**
  * alias_custom -  a builtin command that prints aliases and sets aliases
  * @args: pointer to string arrays
  * @front: the first argument in args
  * Return: 0, -1 otherwise
  */
int alias_custom(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *temp = aliases;
	int i, ret_val = 0;
	char *val;

	if (!args[0])
	{
		while (temp)
		{
			print_alias(temp);
			temp = temp->next;
		}
		return (ret_val);
	}
	for (i = 0; args[i]; i++)
	{
		temp = aliases;
		val = _strchr(args[i], '=');
		if (!val)
		{
			while (temp)
			{
				if (_strcmp(args[i], temp->name) == 0)
				{
					print_alias(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				ret_val = generate_error(args + 1, 1);
		}
		else
			get_alias(args[i], val);
	}
	return (ret_val);
}
/**
  * get_alias - sets new command name and value
  *	changes value of existing command
  * @name: name of the aliase command
  * @val: Alias Value
  */
void get_alias(char *name, char *val)
{
	alias_t *temp = aliases;
	int len, x, y;
	char *new_val;

	*val = '\0';
	val++;
	len = _strlen(val) - _strspn(val, "'\"");
	new_val = malloc(sizeof(char) * (len + 1));
	if (!new_val)
		return;
	for (x = 0, y = 0; val[x]; y++)
	{
		if (val[x] != '\'' && val[x] != '"')
			new_val[y++] = val[x];
	}
	new_val[y] = '\0';
	while (temp)
	{
		if (_strcmp(name, temp->name) == 0)
		{
			free(temp->val);
			temp->val = new_val;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		add_alias_end(&aliases, name, val);
	else
		free(new_val);
}

/**
  * print_alias - prints alias
  * @alias: pointer to alias
  */
void print_alias(alias_t *alias)
{
	char *the_string;
	int len = _strlen(alias->name) + _strlen(alias->val) + 4;

	the_string = malloc(sizeof(char) * (len + 1));
	if (!the_string)
		return;
	_strcpy(the_string, alias->name);
	_strcat(the_string, "='");
	_strcat(the_string, alias->val);
	_strcat(the_string, "'\n");
	write(STDOUT_FILENO, the_string, len);
	free(the_string);
}
/**
  * replace_aliases - replaces matching aliases with value
  * @args: pointer to arrays of argument strings
  * Return: args
  */
char **replace_aliases(char **args)
{
	alias_t *temp;
	int i;
	char *new_val;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (i = 0; args[i]; i++)
	{
		temp = aliases;
		while (temp)
		{
			if (_strcmp(args[i], temp->name) == 0)
			{
				new_val = malloc(sizeof(char) * (_strlen(temp->val) + 1));
				if (!new_val)
				{
					args_free(args, args);
					return (NULL);
				}
				_strcpy(new_val, temp->val);
				free(args[i]);
				args[i] = new_val;
				i--;
				break;
			}
			temp = temp->next;
		}
	}
	return (args);
}
