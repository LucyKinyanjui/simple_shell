#include "shell.h"
/**
  * call_args - separates operators from commands and calls them.
  * @args: pointer to argument strings
  * @front: the first argument in the list
  * @exec_ret: the last executed command parent process return value
  * Return: last executed command parent process return value
  */
int call_args(char **args, char **front, int *exec_ret)
{
int ret_val, i;

if (!args[0])
return (*exec_ret);
for (i = 0; args[i]; i++)
{
if (_strncmp(args[i], "||", 2) == 0)
{
free(args[i]), args[i] = NULL, args = replace_aliases(args);
ret_val = run_args(args, front, exec_ret);
if (*exec_ret != 0)
{
args = &args[++i], i = 0;
}
else
{
for (i++; args[i]; i++)
free(args[i]);
return (ret_val);
}
}
else if (_strncmp(args[i], "&&", 2) == 0)
{
free(args[i]), args[i] = NULL, args = replace_aliases(args);
ret_val = run_args(args, front, exec_ret);
if (*exec_ret == 0)
{
args = &args[++i], i = 0;
}
else
{
for (i++; args[i]; i++)
free(args[i]);
return (ret_val);
}
}
}
args = replace_aliases(args), ret_val = run_args(args, front, exec_ret);
return (ret_val);
}
