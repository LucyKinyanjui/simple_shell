#include "shell.h"

/**
  * allHelp - displays info on bultin command 'alias'
  */
void allHelp(void)
{
	char *stream = "MyShell\nThese shell commands are defined internally.\n";

	write(STDOUT_FILENO, stream, _strlen(stream));
	stream = "Type 'help' to see this list.\nType 'help name' to find ";
	write(STDOUT_FILENO, stream, _strlen(stream));
	stream = "out more about the function 'name'.\n\n  alias   \t";
	write(STDOUT_FILENO, stream, _strlen(stream));
	stream = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";
	write(STDOUT_FILENO, stream, _strlen(stream));
	stream = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
	write(STDOUT_FILENO, stream, _strlen(stream));
	stream = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
	write(STDOUT_FILENO, stream, _strlen(stream));
	stream = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, stream, _strlen(stream));
}
/**
  * aliasHelp - displays info on builtin command 'alias'
  */
void aliasHelp(void)
{
	char *stream = "alias: alias [NAME[='VALUE'] ...]\n\tHandles aliases.\n";

	write(STDOUT_FILENO, stream, _strlen(stream));
	stream = "\n\talias: Prints a list of all aliases, one per line, in ";
	write(STDOUT_FILENO, stream, _strlen(stream));
	stream = "the format NAME='VALUE'.\n\talias name [name2 ...]:prints";
	write(STDOUT_FILENO, stream, _strlen(stream));
	stream = " the aliases name, name2, etc. one per line, in the ";
	write(STDOUT_FILENO, stream, _strlen(stream));
	stream = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
	write(STDOUT_FILENO, stream, _strlen(stream));
	stream = " an alias for each NAME whose VALUE is given. If NAME ";
	write(STDOUT_FILENO, stream, _strlen(stream));
	stream = "is already an alias, replace its value with VALUE.\n";
	write(STDOUT_FILENO, stream, _strlen(stream));
}
/**
  * cdHelp - displays info on builtin command 'cd'
  */
void cdHelp(void)
{
	char *stream = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";

	write(STDOUT_FILENO, stream, _strlen(stream));
	stream = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
	write(STDOUT_FILENO, stream, _strlen(stream));
	stream = "command is interpreted as cd $HOME. If the argument '-' is";
	write(STDOUT_FILENO, stream, _strlen(stream));
	stream = " given, the command is interpreted as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, stream, _strlen(stream));
	stream = "\tThe environment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, stream, _strlen(stream));
	stream = "after a change of directory.\n";
	write(STDOUT_FILENO, stream, _strlen(stream));
}
/**
  * exitHelp - displays info on builtin command 'exit'
  */
void exitHelp(void)
{
	char *stream = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, stream, _strlen(stream));
	stream = "STATUS argument is the integer used to exit the shell.";
	write(STDOUT_FILENO, stream, _strlen(stream));
	stream = " If no argument is given, the command is interpreted as";
	write(STDOUT_FILENO, stream, _strlen(stream));
	stream = " exit 0.\n";
	write(STDOUT_FILENO, stream, _strlen(stream));
}
/**
  * helpHelp - displays info on builtin command 'help'
  */
void helpHelp(void)
{
	char *stream = "help: help\n\tSee all possible Shellby builtin commands.\n";

	write(STDOUT_FILENO, stream, _strlen(stream));
	stream = "\n      help [BUILTIN NAME]\n\tSee specific information on each ";
	write(STDOUT_FILENO, stream, _strlen(stream));
	stream = "builtin command.\n";
	write(STDOUT_FILENO, stream, _strlen(stream));
}
