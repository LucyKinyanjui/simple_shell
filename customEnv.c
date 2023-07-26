#include "shell.h"


/**
* _myenv - a function that prints current environment variable.
* @args: the argument array passed to the shell
* @front: A double pointer to the beginning of args.
*Return: -1 inewLinease of error or 0.
*Description: Prints one variable per line in the
*              format 'variable'='value'.
*/
int _myenv(char **args, char __attribute__((__unused__)) **front)
{
char new_line = '\n';
int index;


if (!environ)
return (-1);

for (index = 0; environ[index]; index++)
{
write(STDOUT_FILENO, environ[index], _strlen(environ[index]));
write(STDOUT_FILENO, &new_line, 1);
}

(void)args;
return (0);
}

/**
* _mysetenv - a function that changes or adds environmental
* variable to the PATH.
* @args: the argument array passed to the shell
* @front: A double pointer to the beginning of args array.
* Return: -1 incase of an error or 0.
* Description: args[1] is the name of the new or existing PATH variable.
*              args[2] is the value to set the new or changed variable to.
*/
int _mysetenv(char **args, char __attribute__((__unused__)) **front)
{
char **new_envn, *new_val;
char **environ_var = NULL;
int index;
size_t size;

if (!args[0] || !args[1])
return (generate_error(args, -1));
new_val = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
if (!new_val)
return (generate_error(args, -1));
_strcpy(new_val, args[0]);
_strcat(new_val, "=");
_strcat(new_val, args[1]);
environ_var = get_env(args[0]);
if (environ_var)
{
free(*environ_var);
*environ_var = new_val;
return (0);
}
for (size = 0; environ[size]; size++)
;

new_envn = malloc(sizeof(char *) * (size + 2));
if (!new_envn)
{
free(new_val);
return (generate_error(args, -1));
}
for (index = 0; environ[index]; index++)
new_envn[index] = environ[index];
new_envn[index++] = new_val;
new_envn[index] = NULL;
free(environ);
environ = new_envn;
return (0);
}

/**
* _myunsetenv - a function that deletes an environmental variable
* from the PATH.
* @args: the argument array pased to the shell
* @front: A double pointer to the beginning of args.
* Description: args[1] is the PATH variable to remove.
* Return: -1 incase of an error or 0 otherwise.
*/
int _myunsetenv(char **args, char __attribute__((__unused__)) **front)
{
int index, index2;
char **new_envn;
char **environ_var;
size_t size;

if (!args[0])
return (generate_error(args, -1));
environ_var = get_env(args[0]);
if (!environ_var)
return (0);

for (size = 0; environ[size]; size++)
;

new_envn = malloc(sizeof(char *) * size);
if (!new_envn)
return (generate_error(args, -1));

for (index = 0, index2 = 0; environ[index]; index++)
{
if (*environ_var == environ[index])
{
free(*environ_var);
continue;
}
new_envn[index2] = environ[index];
index2++;
}
free(environ);
environ = new_envn;
environ[size - 1] = NULL;

return (0);
}
