#include "shell.h"
/**
* get_newLength - gets the new line size,divided by ";", "||", "&&&", or "#".
* @stream: the line to be checked
* Return: size of new line
* Description: cuts short lines containing '#'* comments with '\0'.
*/
ssize_t get_newLength(char *stream)
{
size_t m;
char present, new;
ssize_t newLength = 0;

for (m = 0; stream[m]; m++)
{
present = stream[m], new = stream[m + 1];
if (present == '#')
{
if (m == 0 || stream[m - 1] == ' ')
{
stream[m] = '\0';
break;
}
}
else if (m != 0)
{
if (present == ';')
{
if (new == ';' && stream[m - 1] != ' ' && stream[m - 1] != ';')
{
newLength += 2;
continue;
}
else if (stream[m - 1] == ';' && new != ' ')
{
newLength += 2;
continue;
}
if (stream[m - 1] != ' ')
newLength++;
if (new != ' ')
newLength++;
}
else
check_for_ops(&stream[m], &newLength);
}
else if (present == ';')
{
if (m != 0 && stream[m - 1] != ' ')
newLength++;
if (new != ' ' && new != ';')
newLength++;
}
newLength++;
}
return (newLength);
}
/**
* check_for_ops - a function that checks a line for
* logical operators "||" or "&&".
* @stream:a line pointer to be checked for logical operators
* @newLength: Pointer to newLength in get_newLength function.
*/
void check_for_ops(char *stream, ssize_t *newLength)
{
char prev, present, new;

prev = *(stream - 1);
present = *stream;
new = *(stream + 1);

if (present == '&')
{
if (new == '&' && prev != ' ')
(*newLength)++;
else if (prev == '&' && new != ' ')
(*newLength)++;
}
else if (present == '|')
{
if (new == '|' && prev != ' ')
(*newLength)++;
else if (prev == '|' && new != ' ')
(*newLength)++;
}
}
