#include "shell.h"

/**
 * msh - the main shell loop
 * @inf: the parameter & return info struct
 * @av: the argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */
int msh(inf_t *inf, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(inf);
		if (interactive(inf))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(inf);
		if (r != -1)
		{
			set_info(inf, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(inf, 0);
	}
	write_h(inf);
	free_info(inf, 1);
	if (!interactive(inf) && inf->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (inf->err_num == -1)
			exit(inf->status);
		exit(inf->err_num);
	}
	return (builtin_ret);
}

/**
 * find_built_in - finds a builtin command
 * @inf: parameter
 * Return: -1 if builtin not found,
 * -2 if builtin signals exit()
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 */
int find_built_in(inf_t *inf)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _exitshell},
		{"env", my_env},
		{"help", _myhelp},
		{"history", _history},
		{"setenv", set_env},
		{"unsetenv", unset_env},
		{"cd", _mycdir},
		{"alias", _alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(inf->argv[0], builtintbl[i].type) == 0)
		{
			inf->line_count++;
			built_in_ret = builtintbl[i].func(inf);
			break;
		}
	return (built_in_ret);
}

/**
 * f_cmd - finds a command in path
 * @inf: parameter
 * Return: void
 */
void f_cmd(inf_t *inf)
{
	char *path = NULL;
	int i, k;

	inf->path = inf->argv[0];
	if (inf->linecount_flag == 1)
	{
		inf->line_count++;
		inf->linecount_flag = 0;
	}
	for (i = 0, k = 0; inf->arg[i]; i++)
		if (!is_delim(inf->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(inf, get_env(inf, "PATH="), inf->argv[0]);
	if (path)
	{
		inf->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(inf) || get_env(inf, "PATH=")
			|| inf->argv[0][0] == '/') && is_cmd(inf, inf->argv[0]))
			fork_cmd(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->status = 127;
			print_err(inf, "not found\n");
		}
	}
}

/**
 * fork_cmd - fork an executed thread to run cmd
 * @inf: the parameter
 * Return: void
 */
void fork_cmd(inf_t *inf)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(inf->path, inf->argv, get_environ(inf)) == -1)
		{
			free_info(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(inf->status));
		if (WIFEXITED(inf->status))
		{
			inf->status = WEXITSTATUS(inf->status);
			if (inf->status == 126)
				print_err(inf, "Permission denied\n");
		}
	}
}
