#include "shell.h"

/**
 * _exitshell - exits the shell
 * @inf: Structure containing potential arguments.
 *  Return: (Zero) if inf.argv[0] != "exit"
 */
int _exitshell(inf_t *inf)
{
	int exitcheck;

	if (inf->argv[1])
	{
		exitcheck = err_atoi(inf->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_err(inf, "Illegal number: ");
			_eputs(inf->argv[1]);
			_eputchar('\n');
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
 *  Return: 0 always ( success)
 */
int _cdir(inf_t *inf)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
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
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(inf, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((dir = get_env(inf, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(inf->argv[1]);
	if (chdir_ret == -1)
	{
		print_err(inf, "can't cd to ");
		_eputs(inf->argv[1]), _eputchar('\n');
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
 *  Return: 0 (success)
 */
int _pdir(inf_t *inf)
{
	char **arg_array;

	arg_array = inf->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
