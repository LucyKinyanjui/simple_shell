#include "shell.h"

/**
 * _strchr -  a function that locates a character in a string
 * @str: the string to be searched
 * @chr: the character to be located
 * Return: A pointer to the character once found, NULL if chr is not found
 */
char *_strchr(char *str, char chr)
{
	int i;

	for (i = 0; str[i]; i++)
	{
		if (str[i] == chr)
			return (str + 1);
	}

	return (NULL);
}

/**
 * _strspn - a function that gets the length of a prefix substring
 * @str: the string to be searched
 * @prefix: the prefix to be measured
 * Return: number of bytes in string which contains only of bytes from prefix
 */
int _strspn(char *str, char *prefix)
{
	int bytes = 0;
	int i;

	while (*str)
	{
		for (i = 0; prefix[i]; i++)
		{
			if (*str == prefix[i])
			{
				bytes++;
				break;
			}
		}
		str++;
	}
	return (bytes);
}

/**
 * _strcmp - A function that compares two strings
 * @str1: first string to be compared
 * @str2: second string to be compared
 * Return: if str1 > str2 return the difference, 0 if str1 = str2,
 * if str1 < str2 return negative bytes
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}

	if (*str1 != *str2)
		return (*str1 - *str2);

	return (0);
}

/**
 * _strncmp - a function that compares two strings
 * @str1: first string to be compared
 * @str2: second string to be compared
 * @n: first n bytes of the strings to compare
 * Return: 0 if str1 = str2, a positive val if str1 > str2,
 * negative val if str1 < str2
 */
int _strncmp(const char *str1, const char *str2, size_t n)
{
	size_t k;

	for (k = 0; str1[k] && str2[k] && k < n; k++)
	{
		if (str1[k] > str2[k])
			return (str1[k] - str2[k]);
		else if (str1[k] < str2[k])
			return (str1[k] - str2[k]);
	}

	if (k == n)
		return (0);
	else
		return (-15);
}
