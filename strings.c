#include "shell.h"

/**
 * _strlen - a function that returns the length of a string
 * @str: pointer to the characters of the string
 * Return: the length of the string
 */
int _strlen(const char *str)
{
	int len = 0;

	if (str == NULL)
		return (0);
	while (str[len] != '\0')
		len++;
	return (len);
}

/**
 * _strcpy - copies the string pointed to by src
 * including NULL byte to buffer pointed by dest
 * @dest: where to copy string to
 * @src: where to copy string from
 * Return: The copied string
 */
char *_strcpy(char *dest, const char *src)
{
	size_t k;

	for (k = 0; src[k] != '\0'; k++)
		dest[k] = src[k];
	dest[k] = '\0';

	return (dest);
}

/**
 * _strcat - a function that concatenates two strings
 * @dest : where to take the string
 * @src: where to get the string from
 * Return: the concatenated string
 */
char *_strcat(char *dest, const char *src)
{
	char *dest_temp;
	const char *src_temp;

	dest_temp = dest;
	src_temp = src;

	while (*dest_temp != '\0')
	{
		dest_temp++;
	}

	while (*src_temp != '\0')
	{
		*dest_temp++ = *src_temp++;
	}

	*dest_temp = '\0';

	return (dest);
}

/**
 * _strncat - A function that concatenates two strings,
 * where n number of bytes are copied
 * @dest: where to take the string
 * @src: where to get the string from
 * @n: number of bytes to copy
 * Return: concatenated string
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t des_len = _strlen(dest);
	size_t k;

	for (k = 0; k < n && src[k] != '\0'; k++)
		dest[des_len + k] = src[k];
	dest[des_len + k] = '\0';

	return (dest);
}
