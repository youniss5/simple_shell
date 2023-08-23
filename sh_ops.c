#include "shell.h"
/**
 * cmd_loop - the main shell loop.
 * @inf: the struct parameter.
 * @av: main func arg vector.
 * Return: 0 on success, 1 on error, or error code.
 */
int cmd_loop(inf_t *inf, char **av)
{
	ssize_t r = 0;
	int bin_ret = 0;

	while (r != -1 && bin_ret != -2)
	{
		clear_inf(inf);
		if (interactive_md(inf))
			put_s("$ ");
		e_putchar(BUF_FLUSH);
		r = get_length(inf);
		if (r != -1)
		{
			set_inf(inf, av);
			bin_ret = f_bin(inf);
			if (bin_ret == -1)
				find_cmd(inf);
		}
		else if (interactive_md(inf))
			put_char('\n');
		_ffree_inf(inf, 0);
	}
	write_h(inf);
	_ffree_inf(inf, 1);
	if (!interactive_md(inf) && inf->status)
		exit(inf->status);
	if (bin_ret == -2)
	{
		if (inf->err_num == -1)
			exit(inf->status);
		exit(inf->err_num);
	}
	return (bin_ret);
}

/**
 * f_bin - finds a builtin cmd.
 * @inf: struct parameter.
 * Return: -1 if builtin not found,
 * -2 if builtin signals exit()
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 */
int f_bin(inf_t *inf)
{
	int i, binn_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _exitshell},
		{"env", my_env},
		{"help", _pdir},
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
			binn_ret = builtintbl[i].func(inf);
			break;
		}
	return (binn_ret);
}

/**
 * f_cmd - finds a command path.
 * @inf: struct parameter.
 * Return: void.
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
		if (!delim_chk(inf->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = f_path(inf, get_env(inf, "PATH="), inf->argv[0]);
	if (path)
	{
		inf->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive_md(inf) || get_env(inf, "PATH=")
			|| inf->argv[0][0] == '/') && is_cmd(inf, inf->argv[0]))
			fork_cmd(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->status = 127;
			p_err(inf, "not found\n");
		}
	}
}

/**
 * fork_cmd - fork an executed thread to run cmd.
 * @inf: the struct parameter.
 * Return: void.
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
		if (execve(inf->path, inf->argv, get_envir(inf)) == -1)
		{
			_ffree_inf(inf, 1);
			if (errno == EACCES)
			{
				exit(126);
			}
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
				p_err(inf, "Permission denied\n");
		}
	}
}
