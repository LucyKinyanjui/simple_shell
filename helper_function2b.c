#include "shell.h"

/**
* get_new_length - a function that gets the new line size,
* divided by ";", "||", "&&&", or "#".
* @line: the line to be checked
* Return: size of new line
* Description: cuts short lines containing '#'* comments with '\0'.
*/
ssize_t get_new_length(char *line)
{
size_t k;
char present, new;
ssize_t new_length = 0;

for (k = 0; line[k]; k++)
{
present = line[k], new = line[k + 1];
if (present == '#')
{
if (k == 0 || line[k - 1] == ' ')
{
line[k] = '\0';
break;
}
}
else if (k != 0)
{
if (present == ';')
{
if (new == ';' && line[k - 1] != ' ' && line[k - 1] != ';')
{
new_length += 2;
continue;
}
else if (line[k - 1] == ';' && new != ' ')
{
new_length += 2;
continue;
}
if (line[k - 1] != ' ')
new_length++;
if (new != ' ')
new_length++;
}
else
search_logical_ops(&line[k], &new_length);
}
else if (present == ';')
{
if (k != 0 && line[k - 1] != ' ')
new_length++;
if (new != ' ' && new != ';')
new_length++;
}
new_length++;
}
return (new_length);
}

/**
* search_logical_ops - a function that checks a line for
* logical operators "||" or "&&".
* @line: a line pointer to be checked for logical operators
* @new_length: Pointer to new length in get_new_length function.
*/
void search_logical_ops(char *line, ssize_t *new_length)
{
char prev, present, new;

prev = *(line - 1);
present = *line;
new = *(line + 1);

if (present == '&')
{
if (new == '&' && prev != ' ')
(*new_length)++;
else if (prev == '&' && new != ' ')
(*new_length)++;
}
else if (present == '|')
{
if (new == '|' && prev != ' ')
(*new_length)++;
else if (prev == '|' && new != ' ')
(*new_length)++;
}
}
