#include "shell.h"
/**
 * my_env - prints the current environment.
 * @inf: Structure containing the arguments.
 * Return: Always 0 (success).
 */
int my_env(inf_t *inf)
{
	print_list_str(inf->env);
	return (0);
}

/**
 * get_env - gets the environ's variable value.
 * @inf: Structure containing the arguments.
 * @name: env var name.
 * Return: the variable's value.
 */
char *get_env(inf_t *inf, const char *name)
{
	list_t *node = inf->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
		{
			return (p);
		}
		node = node->next;
	}
	return (NULL);
}

/**
 * set_env - Initializing a new environment variable or modifying an existing
 *             one.
 * @inf: Structure containing the arguments.
 *  Return: Always 0 (success).
 */
int set_env(inf_t *inf)
{
	if (inf->argc != 3)
	{
		e_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (_set_env(inf, inf->argv[1], inf->argv[2]))
	{
		return (0);
	}
	return (1);
}

/**
 * unset_env - Removes a variable of the environment.
 * @inf: Structure containing the arguments.
 *  Return: Always 0 (success).
 */
int unset_env(inf_t *inf)
{
	int i;

	if (inf->argc == 1)
	{
		e_puts("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= inf->argc; i++)
		_unset_env(inf, inf->argv[i]);

	return (0);
}

/**
 * env_list - populates the env linked list.
 * @inf: Structure containing the arguments.
 * Return: Always 0 (success).
 */
int env_list(inf_t *inf)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	inf->env = node;
	return (0);
}
