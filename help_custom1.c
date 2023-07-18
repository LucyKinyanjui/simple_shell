#include "shell.h"

/**
  * envHelp - Displays info on builtin command 'env'
  */
void envHelp(void)
{
	char *stream = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, stream, _strlen(stream));
}
/**
  * setenvHelp - Displays infor on builtin command 'setenv'
  */
void setenvHelp(void)
{
	char *stream = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, stream, _strlen(stream));
	stream = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, stream, _strlen(stream));
	stream = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, stream, _strlen(stream));
}
/**
  * unsetenvHelp - Displays info on builtin command 'unsetenv'
  */
void unsetenvHelp(void)
{
	char *stream = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, stream, _strlen(stream));
	stream = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, stream, _strlen(stream));
	stream = "message to stderr.\n";
	write(STDOUT_FILENO, stream, _strlen(stream));
}
