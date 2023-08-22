#include "shell.h"

/**
 * clear_inf - clears inf_t struct.
 * @inf: address of struct.
 */
void clear_inf(inf_t *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
}

/**
 * set_inf - initializes struct inf_t.
 * @inf: address of struct.
 * @av: arg vector.
 */
void set_inf(inf_t *inf, char **av)
{
	int x = 0;

	inf->fname = av[0];
	if (inf->arg)
	{
		inf->argv = strtow(inf->arg, " \t");
		if (!inf->argv)
		{

			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{
				inf->argv[0] = _strdup(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		for (x = 0; inf->argv && inf->argv[x]; x++)
			;
		inf->argc = x;

		replace_alias(inf);
		replace_vars(inf);
	}
}

/**
 * _ffree_inf - frees struct inf_t.
 * @inf: address of struct.
 * @x: true if freeing all fields
 */
void _ffree_inf(inf_t *inf, int x)
{
	_ffree(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;

	if (x)
	{
		if (!inf->cmd_buf)
			free(inf->arg);
		if (inf->env)
			free_list(&(inf->env));
		if (inf->history)
			free_list(&(inf->history));
		if (inf->alias)
			free_list(&(inf->alias));
		_ffree(inf->environ);
			inf->environ = NULL;
		bfree((void **)inf->cmd_buf);
		if (inf->read_fd > 2)
			close(inf->read_fd);
		_putchar(BUF_FLUSH);
	}
}
