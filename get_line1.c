#include "shell.h"
/**
 * get_line - a function that reads input from a stream
 * @lineptr: the buffer that stores the input
 * @n_len: the size of line path
 * @stream: the stream to read from
 * Return: the number of bytes read
 */
ssize_t get_line(char **lineptr, size_t *n_len, FILE *stream)
{
        int r;
        static ssize_t input;
        ssize_t ret_val;
        char *buffer, t = 'z';

        if (input == 0)
                fflush(stream);
        else
                return (-1);
	input = 0;

        buffer = malloc(sizeof(char) * BUFSIZE);
        if (buffer == 0)
                return (-1);
        while (t != '\n')
        {
                r = read(STDIN_FILENO, &t, 1);
                if (r == -1 || (r == 0 && input == 0))
                {
                        free(buffer);
                        return (-1);
                }
                if (r == 0 && input != 0)
                {
                        input++;
                        break;
			}
                if (input >= BUFSIZE)
                        buffer = _realloc(buffer, input, input + 1);
                buffer[input] = t;
                input++;
        }
        buffer[input] = '\0';
        bring_line(lineptr, n_len, buffer, input);
        ret_val = input;
        if (r != 0)
                input = 0;
        return (ret_val);
}
