#include "shell.h"

/**
 * _exitshell - exits the shell.
 * @inf: Structure includes arguments.
 *  Return: (Zero) if inf.argv[0] != "exit".
 */
int _exitshell(inf_t *inf)
{
	int exitcheck;

	if (inf->argv[1])
	{
		exitcheck = err_atoi(inf->argv[1]);
		if (exitcheck == -1)
		{
			inf->status = 2;
			p_err(inf, "Illegal number: ");
			e_puts(inf->argv[1]);
			e_putchar('\n');
			return (1);
		}
		inf->err_num = err_atoi(inf->argv[1]);
		return (-2);
	}
	inf->err_num = -1;
	return (-2);
}

/**
 * _cdir - changes the current dir.
 * @inf: Structure containing potential arguments.
 *  Return: 0 always (success).
 */
int _cdir(inf_t *inf)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		put_s("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->argv[1])
	{
		dir = get_env(inf, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = get_env(inf, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(inf->argv[1], "-") == 0)
	{
		if (!get_env(inf, "OLDPWD="))
		{
			put_s(s);
			put_char('\n');
			return (1);
		}
		put_s(get_env(inf, "OLDPWD=")), put_char('\n');
		chdir_ret =
			chdir((dir = get_env(inf, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(inf->argv[1]);
	if (chdir_ret == -1)
	{
		p_err(inf, "can't cd to ");
		e_puts(inf->argv[1]), e_putchar('\n');
	}
	else
	{
		_set_envir(inf, "OLDPWD", get_env(inf, "PWD="));
		_set_envir(inf, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * _pdir - changes the process current dir.
 * @inf: Structure containing potential arguments.
 *  Return: 0 (success).
 */
int _pdir(inf_t *inf)
{
	char **arg_array;

	arg_array = inf->argv;
	put_s("help call works. Function not yet implemented \n");
	if (0)
		put_s(*arg_array);
	return (0);
}
