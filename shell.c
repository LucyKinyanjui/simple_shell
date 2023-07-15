#include "shell.h"
/**
 * main - simple shell program that executes shell commands
 * @argc: the number of command line arguments
 * @argv: an array of command line arguments
 * Return: the exit status of the last executed command
 */
int main(int argc, char *argv[])
{
	int exit_status = 0, return_val, *exec_ret = &return_val;
	char *new_line = "\n", *prompt = "$ ";

	aliases = NULL;
	signal(SIGINT, shell_prompt);
	*exec_ret = 0;
	environ = dup_env();
	if (!environ)
		exit(-100);
	if (argc != 1)
	{
		exit_status = run_cmd(argv[1], exec_ret);
		env_free();
		free_alias_list(aliases);
		return (*exec_ret);
	}
	if (!isatty(STDIN_FILENO))
	{
		while (exit_status != END_OF_FILE && exit_status != EXIT)
			exit_status = handle_arguments(exec_ret);
		env_free();
		free_alias_list(aliases);
		return (*exec_ret);
	}
	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		exit_status = handle_arguments(exec_ret);
		if (exit_status == END_OF_FILE || exit_status == EXIT)
		{
			if (exit_status == END_OF_FILE)
				write(STDOUT_FILENO, new_line, 1);
			env_free();
			free_alias_list(aliases);
			exit(*exec_ret);
		}
	}
	env_free();
	free_alias_list(aliases);
	return (*exec_ret);
}
