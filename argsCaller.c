#include "shell.h"
/**
  * argsCaller - separates operators from commands and calls them.
  * @args: pointer to argument strings
  * @first: the first argument in the list
  * @execRet: the last executed command parent process return value
  * Return: last executed command parent process return value
  */
int argsCaller(char **args, char **first, int *execRet)
{
int retVal, itr;

if (!args[0])
return (*execRet);
for (itr = 0; args[itr]; itr++)
{
if (_strncmp(args[itr], "||", 2) == 0)
{
free(args[itr]), args[itr] = NULL, args = aliasesReplace(args);
retVal = argsRunner(args, first, execRet);
if (*execRet != 0)
{
args = &args[++itr], itr = 0;
}
else
{
for (itr++; args[itr]; itr++)
free(args[itr]);
return (retVal);
}
}
else if (_strncmp(args[itr], "&&", 2) == 0)
{
free(args[itr]), args[itr] = NULL, args = aliasesReplace(args);
retVal = argsRunner(args, first, execRet);
if (*execRet == 0)
{
args = &args[++itr], itr = 0;
}
else
{
for (itr++; args[itr]; itr++)
free(args[itr]);
return (retVal);
}
}
}
args = aliasesReplace(args), retVal = argsRunner(args, first, execRet);
return (retVal);
}
