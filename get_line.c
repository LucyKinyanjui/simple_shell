#include "shell.h"

/**
 * _realloc - a function that reallocates memory
 * @ptr:  a pointer to previous memory location
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 * Return: pointer to allocated memory block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *temp, *filler;
	void *mem;
	unsigned int index;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		mem = malloc(new_size);
		if (mem == NULL)
			return (NULL);
		return (mem);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	temp = ptr;
	mem = malloc(new_size);
	if (mem == NULL)
	{
		free(ptr);
		return (NULL);
	}

	filler = mem;

	for (index = 0; index < old_size && index < new_size; index++)
		filler[index] = *temp++;

	free(ptr);
	return (mem);
}

/**
 * bring_line - a function that reassigns the variable pointer for get_line
 * @lineptr: the buffer that stores the input string
 * @buffer: string that is to be assigned to lineptr
 * @n_len: the size of the line
 * @b_len: the size of the buffer
 */
void bring_line(char **lineptr, size_t *n_len, char *buffer, size_t b_len)
{
	if (*lineptr == NULL)
	{
		if (b_len > BUFSIZE)
			*n_len = b_len;

		else
			*n_len = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*n_len < b_len)
	{
		if (b_len > BUFSIZE)
			*n_len = b_len;
		else
			*n_len = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}
