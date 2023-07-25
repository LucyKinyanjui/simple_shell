#include "shell.h"
/**
* custom_cd - changes the current directory of custom process.
* @args: An array of arguments.
* @first: A double pointer to the beginning of args.
* Return: -2 if the string isn't a directory -1 if error, 0 ow.
*/
int custom_cd(char **args, char __attribute__((__unused__)) **first)
{
char *pwd = NULL, **dirStatus, *newLine = "\n", *old_pwd = NULL;
struct stat dir;

old_pwd = getcwd(old_pwd, 0);
if (!old_pwd)
return (-1);
if (args[0])
{
if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
{
if ((args[0][1] == '-' && args[0][2] == '\0') ||
args[0][1] == '\0')
{
if (locate_env("OLDPWD") != NULL)
(chdir(*locate_env("OLDPWD") + 7));
}
else
{
free(old_pwd);
return (write_error(args, 2));
}
}
else
{
if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
&& ((dir.st_mode & S_IXUSR) != 0))
chdir(args[0]);
else
{
free(old_pwd);
return (write_error(args, 2));
}
}
}
else
{
if (locate_env("HOME") != NULL)
chdir(*(locate_env("HOME")) + 5);
}
pwd = getcwd(pwd, 0);
if (!pwd)
return (-1);
dirStatus = malloc(sizeof(char *) * 2);
if (!dirStatus)
return (-1);
dirStatus[0] = "OLDPWD", dirStatus[1] = old_pwd;
if (custom_setenv(dirStatus, dirStatus) == -1)
return (-1);
dirStatus[0] = "PWD", dirStatus[1] = pwd;
if (custom_setenv(dirStatus, dirStatus) == -1)
return (-1);
if (args[0] && args[0][0] == '-' && args[0][1] != '-')
{
write(STDOUT_FILENO, pwd, _strlen(pwd));
write(STDOUT_FILENO, newLine, 1);
}
free(old_pwd), free(pwd), free(dirStatus);
return (0);
}
/**
* locate_custom - used to match a cmd with a corresponing
* custom builtin function
* @cmd: The command to match.
*
* Return: A function pointer to the corresponding builtin.
*/
int (*locate_custom(char *cmd))(char **args, char **first)
{
int j;

builtin_t funcs[] = {
{ "exit", custom_exit },
{ "env", custom_env },
{ "setenv", custom_setenv },
{ "unsetenv", custom_unsetenv },
{ "cd", custom_cd },
{ "alias", custom_alias },
{ "help", custom_help },
{ NULL, NULL }
};

for (j = 0; funcs[j].name; j++)
{
if (_strcmp(funcs[j].name, cmd) == 0)
break;
}
return (funcs[j].p_cmd_fn);
}

/**
* custom_help - Displays information about shellby builtin commands.
* @args: An array of arguments.
* @first: A pointer to the beginning of args.
*
* Return: If an error occurs - -1.
*         Otherwise - 0.
*/
int custom_help(char **args, char __attribute__((__unused__)) **first)
{
if (!args[0])
allHelp();
else if (_strcmp(args[0], "alias") == 0)
aliasHelp();
else if (_strcmp(args[0], "cd") == 0)
cdHelp();
else if (_strcmp(args[0], "exit") == 0)
exitHelp();
else if (_strcmp(args[0], "env") == 0)
envHelp();
else if (_strcmp(args[0], "setenv") == 0)
setenvHelp();
else if (_strcmp(args[0], "unsetenv") == 0)
unsetenvHelp();
else if (_strcmp(args[0], "help") == 0)
helpHelp();
else
write(STDERR_FILENO, args[0], _strlen(args[0]));

return (0);
}

/**
* custom_exit - Causes normal process termination for the shell.
* @args: An array of arguments containing the exit value.
* @first: A double pointer to the beginning of args.
* Return: If there are no arguments - -3.
*         If the given exit value is invalid - 2.
*         O/w - exits with the given status value.
* Description: Upon returning -3, the program exits back in the main function.
*/
int custom_exit(char **args, char **first)
{
int j = 0;
int int_len = 10;
unsigned int number = 0, max_num = 1 << (sizeof(int) * 8 - 1);

if (args[0])
{
if (args[0][0] == '+')
{
j = 1;
int_len++;
}
for (; args[0][j]; j++)
{
if (j <= int_len && args[0][j] >= '0' && args[0][j] <= '9')
number = (number * 10) + (args[0][j] - '0');
else
return (write_error(--args, 2));
}
}
else
{
return (-3);
}
if (number > max_num - 1)
return (write_error(--args, 2));
args -= 1;
argsFree(args, first);
envFree();
freeAliasList(aliases);
exit(number);
}
