#include "shell.h"

/**
 * _history - displays the list of history
 * @inf: Structure containing shell arguments.
 *  Return: 0 (success).
 */
int _history(inf_t *inf)
{
	print_list(inf->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @inf: struct parameter.
 * @str: string alias.
 * Return:  0 (success), 1 (error).
 */
int unset_alias(inf_t *inf, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(inf->alias),
		get_node_index(inf->alias, node_starts_with(inf->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string.
 * @inf: struct parameter.
 * @str: the string alias.
 * Return: 0 (success), 1 (error).
 */
int set_alias(inf_t *inf, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(inf, str));

	unset_alias(inf, str);
	return (add_node_end(&(inf->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string.
 * @node: the alias node.
 * Return: 0 (success), 1 (error).
 */
int print_alias(list_t *node)
{
	char *p = NULL, *pt = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (pt = node->str; pt <= p; pt++)
			put_char(*pt);
		put_char('\'');
		put_s(p + 1);
		put_s("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias - mimics the alias.
 * @inf: Structure includes arguments.
 *  Return: 0 (success).
 */
int _alias(inf_t *inf)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (inf->argc == 1)
	{
		node = inf->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; inf->argv[i]; i++)
	{
		p = _strchr(inf->argv[i], '=');
		if (p)
			set_alias(inf, inf->argv[i]);
		else
			print_alias(node_starts_with(inf->alias, inf->argv[i], '='));
	}

	return (0);
}
