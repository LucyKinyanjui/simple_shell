#include "shell.h"
/**
* _mycd - changes the current directory of custom process.
* @args: An array of arguments.
* @front: A double pointer to the beginning of args.
* Return: -2 if the string isn't a directory -1 if error, 0 ow.
*/
int _mycd(char **args, char __attribute__((__unused__)) **front)
{
char *pwd = NULL, **info, *new_line = "\n", *old_pwd = NULL;
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
if (get_env("OLDPWD") != NULL)
(chdir(*get_env("OLDPWD") + 7));
}
else
{
free(old_pwd);
return (generate_error(args, 2));
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
return (generate_error(args, 2));
}
}
}
else
{
if (get_env("HOME") != NULL)
chdir(*(get_env("HOME")) + 5);
}
pwd = getcwd(pwd, 0);
if (!pwd)
return (-1);
info = malloc(sizeof(char *) * 2);
if (!info)
return (-1);
info[0] = "OLDPWD", info[1] = old_pwd;
if (_mysetenv(info, info) == -1)
return (-1);
info[0] = "PWD", info[1] = pwd;
if (_mysetenv(info, info) == -1)
return (-1);
if (args[0] && args[0][0] == '-' && args[0][1] != '-')
{
write(STDOUT_FILENO, pwd, _strlen(pwd));
write(STDOUT_FILENO, new_line, 1);
}
free(old_pwd), free(pwd), free(info);
return (0);
}
/**
* _mybuiltin - used to match a cmd with a corresponing
* custom builtin function
* @cmd: The command to match.
*
* Return: A function pointer to the corresponding builtin.
*/
int (*_mybuiltin(char *cmd))(char **args, char **front)
{
int k;

builtin_t funcs[] = {
{ "exit", _myexit },
{ "env", _myenv },
{ "setenv", _mysetenv },
{ "unsetenv", _myunsetenv },
{ "cd", _mycd },
{ "alias", _myalias },
{ "help", _myhelp },
{ NULL, NULL }
};

for (k = 0; funcs[k].name; k++)
{
if (_strcmp(funcs[k].name, cmd) == 0)
break;
}
return (funcs[k].cmd_fn);
}

/**
* _myhelp - Displays information about shellby builtin commands.
* @args: An array of arguments.
* @front: A pointer to the beginning of args.
*
* Return: If an error occurs - -1.
*         Otherwise - 0.
*/
int _myhelp(char **args, char __attribute__((__unused__)) **front)
{
if (!args[0])
all_help();
else if (_strcmp(args[0], "alias") == 0)
alias_help();
else if (_strcmp(args[0], "cd") == 0)
cd_help();
else if (_strcmp(args[0], "exit") == 0)
exit_help();
else if (_strcmp(args[0], "env") == 0)
env_help();
else if (_strcmp(args[0], "setenv") == 0)
setenv_help();
else if (_strcmp(args[0], "unsetenv") == 0)
unsetenv_help();
else if (_strcmp(args[0], "help") == 0)
help_help();
else
write(STDERR_FILENO, args[0], _strlen(args[0]));

return (0);
}

/**
* _myexit - Causes normal process termination for the shell.
* @args: An array of arguments containing the exit value.
* @front: A double pointer to the beginning of args.
* Return: If there are no arguments - -3.
*         If the given exit value is invalid - 2.
*         Otherwise - exits with the given status value.
* Description: Upon returning -3, the program exits back in the main function.
*/
int _myexit(char **args, char **front)
{
int k = 0;
int int_length = 10;
unsigned int num = 0, max_num = 1 << (sizeof(int) * 8 - 1);

if (args[0])
{
if (args[0][0] == '+')
{
k = 1;
int_length++;
}
for (; args[0][k]; k++)
{
if (k <= int_length && args[0][k] >= '0' && args[0][k] <= '9')
num = (num * 10) + (args[0][k] - '0');
else
return (generate_error(--args, 2));
}
}
else
{
return (-3);
}
if (num > max_num - 1)
return (generate_error(--args, 2));
args -= 1;
args_free(args, front);
env_free();
free_alias_list(aliases);
exit(num);
}
