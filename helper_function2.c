#include "shell.h"
/**
* lineHandler - a function that divides a line read from stdin.
* @stream: A pointer to the read line.
* @read: The length of line.
*/
void lineHandler(char **stream, ssize_t read)
{
ssize_t newLength;
char *oldLine, *newLine, prev, present, new;
size_t m, n;

newLength = get_newLength(*stream);
if (newLength == read - 1)
return;
newLine = malloc(newLength + 1);
if (!newLine)
return;
n = 0;
oldLine = *stream;
for (m = 0; oldLine[m]; m++)
{
present = oldLine[m];
new = oldLine[m + 1];
prev = (m != 0) ? oldLine[m - 1] : '\0';
newLine[n++] = (present == ';' && new == ';' && prev != ' ' && prev != ';')
? ' ' :
(present == ';' && prev == ';' && new != ' ') ? ';' :
(present == ';' && prev != ' ') ? ' ' :
(present == ';') ? ';' :
(present == '&' && new == '&' && prev != ' ') ? ' ' :
(present == '&' && prev == '&' && new != ' ') ? '&' :
(present == '&') ? ' ' :
(present == '|' && new == '|' && prev != ' ') ? ' ' :
(present == '|' && prev == '|' && new != ' ') ? '|' :
(present == '|') ? ' ' :
oldLine[m];
if (present == ';')
{
if (m != 0 && prev != ' ')
newLine[n++] = ' ', newLine[n++] = ';';
if (new != ' ' && new != ';')
newLine[n++] = ' ';
}
}
newLine[n] = '\0';
free(*stream);
*stream = newLine;
}
