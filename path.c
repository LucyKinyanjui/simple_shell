#include "shell.h"

/**
 * find_cmd - a function that locates a command in a path
 * @command: The command to find
 * Return: The command path, otherwise NULL
 */
char *find_cmd(char *command)
{
	char **path_list, *temp_path;
	list_t *dir_list, *head;
	struct stat st;

	path_list = get_env("PATH");
	if (!path_list || !(*path_list))
		return (NULL);
	dir_list = get_dir(*path_list + 5);
	head = dir_list;
	while (dir_list)
	{
		temp_path = malloc(_strlen(dir_list->path) + _strlen(command) + 2);
		if (!temp_path)
			return (NULL);
		_strcpy(temp_path, dir_list->path);
		_strcat(temp_path, "/");
		_strcat(temp_path, command);

		if (stat(temp_path, &st) == 0)
		{
			free_list(head);
			return (temp_path);
		}
		dir_list = dir_list->next;
		free(temp_path);
	}
	free_list(head);
	return (NULL);
}

/**
 * path_fill - a function that copies path,
 * replaces directory path with current working directory
 * @path: the list of directories
 * Return: the path replaced with current working directory
 */
char *path_fill(char *path)
{
	int i, len = 0;
	char *path_copy, *pwd;

	pwd = *(get_env("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				len += _strlen(pwd) + 1;
			else
				len++;
		}
		else
			len++;
	}
	path_copy = malloc(sizeof(char) * (len + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				_strcat(path_copy, path);
				_strcat(path_copy, ":");
			}
			else
				_strcat(path_copy, ":");
		}
		else
		{
			_strncat(path_copy, &path[i], 1);
		}
	}
	return (path_copy);
}

/**
 * get_dir - a function that Tokenizes list separated by a colon
 * @path: the list of directories separated by colon
 * Return: a pointer to the linked list
 */
list_t *get_dir(char *path)
{
	int i;
	char **dir_list, *path_copy;
	list_t *head = NULL;

	path_copy = path_fill(path);
	if (!path_copy)
		return (NULL);
	dir_list = str_tok(path_copy, ":");
	free(path_copy);
	if (!dir_list)
		return (NULL);
	for (i = 0; dir_list[i]; i++)
	{
		if (add_node_end(&head, dir_list[i]) == NULL)
		{
			free_list(head);
			free(dir_list);

			return (NULL);
		}
	}
	free(dir_list);
	return (head);
}
