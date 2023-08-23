#include "shell.h"

/**
 * get_envir - returns the array copy of environ.
 * @inf: Structure containing arguments.
 * Return: Always 0 (success).
 */
char **get_envir(inf_t *inf)
{
	if (!inf->environ || inf->env_changed)
	{
		inf->environ = list_to_strings(inf->env);
		inf->env_changed = 0;
	}
	return (inf->environ);
}

/**
 * _unset_envir - Removes a variable of environment.
 * @inf: Structure containing arguments.
 * Return: (1) on delete, (0) otherwise.
 * @var: env var property.
 */
int _unset_envir(inf_t *inf, char *var)
{
	list_t *node = inf->env;
	size_t x = 0;
	char *p;

	if (!node || !var)
	{
		return (0);
	}
	while (node)
	{
		p = goes_by(node->str, var);
		if (p && *p == '=')
		{
			inf->env_changed = delete_node_at_index(&(inf->env), x);
			x = 0;
			node = inf->env;
			continue;
		}
		node = node->next;
		x++;
	}
	return (inf->env_changed);
}

/**
 * _set_envir - Initializing a new env var or modify an existing one.
 * @inf: Structure containing arguments.
 * @var: env var property.
 * @val: env var value.
 *  Return: Always 0 (success).
 */
int _set_envir(inf_t *inf, char *var, char *val)
{
	char *buff = NULL;
	list_t *node;
	char *p;

	if (!var || !val)
		return (0);

	buff = malloc(_strlen(var) + _strlen(val) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, val);
	node = inf->env;
	while (node)
	{
		p = goes_by(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buff;
			inf->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(inf->env), buff, 0);
	free(buff);
	inf->env_changed = 1;
	return (0);
}
