#include "shell.h"


/**
* custom_env - a function that prints current environment variable.
* @args: argument array passed to the shell
* @first: A double pointer to the beginning of args.
*Return: -1 inewLinease of error or 0.
*Description: Prints one variable per line in the
*              format 'variable'='value'.
*/
int custom_env(char **args, char __attribute__((__unused__)) **first)
{
char newLine = '\n';
int index;


if (!environ)
return (-1);

for (index = 0; environ[index]; index++)
{
write(STDOUT_FILENO, environ[index], _strlen(environ[index]));
write(STDOUT_FILENO, &newLine, 1);
}

(void)args;
return (0);
}

/**
* custom_setenv - a function that changes or adds environmental
* variable to the PATH.
* @args: argument array passed to the shell
* @first: A double pointer to the beginning of args array.
* Return: -1 incase of an error or 0.
* Description: args[1] is the name of the new or existing PATH variable.
*              args[2] is the value to set the new or changed variable to.
*/
int custom_setenv(char **args, char __attribute__((__unused__)) **first)
{
char **newEnvn, *newVal;
char **environVar = NULL;
int index;
size_t size;

if (!args[0] || !args[1])
return (write_error(args, -1));
newVal = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
if (!newVal)
return (write_error(args, -1));
_strcpy(newVal, args[0]);
_strcat(newVal, "=");
_strcat(newVal, args[1]);
environVar = locate_env(args[0]);
if (environVar)
{
free(*environVar);
*environVar = newVal;
return (0);
}
for (size = 0; environ[size]; size++)
;

newEnvn = malloc(sizeof(char *) * (size + 2));
if (!newEnvn)
{
free(newVal);
return (write_error(args, -1));
}
for (index = 0; environ[index]; index++)
newEnvn[index] = environ[index];
newEnvn[index++] = newVal;
newEnvn[index] = NULL;
free(environ);
environ = newEnvn;
return (0);
}

/**
* custom_unsetenv - a function that deletes an environmental variable
* from the PATH.
* @args: argument array pased to the shell
* @first: A double pointer to the beginning of args.
* Description: args[1] is the PATH variable to remove.
* Return: -1 incase of an error or 0 otherwise.
*/
int custom_unsetenv(char **args, char __attribute__((__unused__)) **first)
{
int index, pos2;
char **newEnvn;
char **environVar;
size_t size;

if (!args[0])
return (write_error(args, -1));
environVar = locate_env(args[0]);
if (!environVar)
return (0);

for (size = 0; environ[size]; size++)
;

newEnvn = malloc(sizeof(char *) * size);
if (!newEnvn)
return (write_error(args, -1));

for (index = 0, pos2 = 0; environ[index]; index++)
{
if (*environVar == environ[index])
{
free(*environVar);
continue;
}
newEnvn[pos2] = environ[index];
pos2++;
}
free(environ);
environ = newEnvn;
environ[size - 1] = NULL;

return (0);
}
