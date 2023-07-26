#include "shell.h"

/**
 * add_alias_end - a function that adds a node
 * to the end of a alias_t linked list
 * @head: pointer to the head of the of the list_t list
 * @name: the name of the new alias to be added
 * @val: the value of the new alias to be added
 * Return: pointer to the new node, otherwise NULL incase of an error
 */
alias_t *add_alias_end(alias_t **head, char *name, char *val)
{
	alias_t *tail;
	alias_t *new_node = malloc(sizeof(alias_t));

	if (!new_node)
		return (NULL);

	new_node->next = NULL;
	new_node->name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->val = val;
	_strcpy(new_node->name, name);

	if (*head)
	{
		tail = *head;
		while (tail->next != NULL)
			tail = tail->next;
		tail->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * add_node_end - a function that adds a node
 * at the end of a list_t linked list
 * @head: pointer to the head of a linked list
 * @path: the directory path for the new node to contain
 * Return: pointer to the new node, otherwise NULL incase of an error
 */
list_t *add_node_end(list_t **head, char *path)
{
	list_t *new_node = malloc(sizeof(list_t));
	list_t *tail;

	if (!new_node)
		return (NULL);

	new_node->path = path;
	new_node->next = NULL;

	if (*head)
	{
		tail = *head;
		while (tail->next != NULL)
			tail = tail->next;
		tail->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * free_alias_list - a function that frees a alias_t linked list
 * @head: the head of the alias_t list
 */
void free_alias_list(alias_t *head)
{
	alias_t *next;

	while (head)
	{
		next = head->next;
		free(head->name);
		free(head->val);
		free(head);
		head = next;
	}
}

/**
 * free_list - a function that frees a list_t linked list
 * @head: the head of the list_t list
 */
void free_list(list_t *head)
{
	list_t *next;

	while (head)
	{
		next = head->next;
		free(head->path);
		free(head);
		head = next;
	}
}
