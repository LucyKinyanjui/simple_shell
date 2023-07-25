#include "shell.h"
/**
* handle_line - a function that divides a line read from stdin.
* @line: A pointer to the read line.
* @read: The length of line.
*/
void handle_line(char **line, ssize_t read)
{
ssize_t new_length;
char *old_line, *new_line, prev, present, new;
size_t k, l;

new_length = get_new_length(*line);
if (new_length == read - 1)
return;
new_line = malloc(new_length + 1);
if (!new_line)
return;
l = 0;
old_line = *line;
for (k = 0; old_line[k]; k++)
{
present = old_line[k];
new = old_line[k + 1];
prev = (k != 0) ? old_line[k - 1] : '\0';
new_line[l++] = (present == ';' && new == ';' && prev != ' ' && prev != ';')
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
old_line[k];
if (present == ';')
{
if (k != 0 && prev != ' ')
new_line[l++] = ' ', new_line[l++] = ';';
if (new != ' ' && new != ';')
new_line[l++] = ' ';
}
}
new_line[l] = '\0';
free(*line);
*line = new_line;
}
