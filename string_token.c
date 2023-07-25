#include "shell.h"

/**
 * tok_length - a function that locates the delimeter index
 * @str: the string containing delimeters
 * @deli: the delimeter character
 * Return: the length of the string before delimeter
 */
int tok_length(char *str, char *deli)
{
	int i = 0, len = 0;

	while (*(str + i) && *(str + i) != *deli)
	{
		len++;
		i++;
	}

	return (len);
}
/**
 * count_tokens - a function that counts the number of words deliminated
 * @str: the string to search
 * @deli: the delimeter character
 * Return: the number of words in the string
 */
int count_tokens(char *str, char *deli)
{
	int i, tokens = 0, len = 0;

	for (i = 0; *(str + i); i++)
		len++;
	for (i = 0; i < len; i++)
	{
		if (*(str + i) != *deli)
		{
			tokens++;
			i += tok_length(str + i, deli);
		}
	}

	return (tokens);
}

/**
 * str_tok - a function that tokenizes a string
 * @str: the string to tokenize
 * @deli: the delimeter characters
 * Return: pointer to array containing the tokenized words
 */
char **str_tok(char *str, char *deli)
{
	char **tokens;
	int i = 0;
	int the_tokens, t, letters, l;

	the_tokens = count_tokens(str, deli);
	if (the_tokens == 0)
		return (NULL);
	tokens = malloc(sizeof(char *) * (the_tokens + 2));
	if (!tokens)
		return (NULL);
	for (t = 0; t < the_tokens; t++)
	{
		while (str[i] == *deli)
			i++;
		letters = tok_length(str + i, deli);
		tokens[t] = malloc(sizeof(char) * (letters + 1));
		if (!tokens[t])
		{
			for (i -= 1; i >= 0; i--)
				free(tokens[i]);
			free(tokens);
			return (NULL);
		}
		for (l = 0; l < letters; l++)
		{
			tokens[t][l] = str[i];
			i++;
		}
		tokens[t][l] = '\0';
	}
	tokens[t] = NULL;
	tokens[t + 1] = NULL;
	return (tokens);
}
