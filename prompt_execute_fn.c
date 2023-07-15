#include "shell.h"

/**
 * shell_prompt - A function that prints a new prompt when called
 * @sign: The signal
 */
void shell_prompt(int sign)
{
	char *new_prompt = "\n$ ";


	(void)sign;
	signal(SIGINT, shell_prompt);
	write(STDIN_FILENO, new_prompt, 3);
}

/**
 * exec_cmd - A function that executes a command in a child process
 * @args: An array of arguments
 * @front: A double pointer to the beginning of arguments
 * Return: Corresponding error code, otherwise last value of last executed cmd
 */
int exec_cmd(char **args, char **front)
{
	pid_t child_pid;
	int status, flag = 0, exit_status = 0;
	char *command = args[0];
	alias_t *aliases = NULL;

	if (command[0] != '/' && command[0] != '.')
	{
		flag = 1, command = find_cmd(command);
	}
	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
			exit_status = (generate_error(args, 126));
		else
			exit_status = (generate_error(args, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(command), perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
		execve(command, args, environ);
		if (errno == EACCES)
		exit_status = (generate_error(args, 126)), env_free(), free_args
		(args, front), free_alias_list(aliases), _exit(exit_status);
		}
		else
		{
			wait(&status), exit_status = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(command);
	return (exit_status);
}
