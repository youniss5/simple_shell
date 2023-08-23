#include "shell.h"
/**
 * alias_exchange - exchanges an alias in the token.
 * @inf: the struct parameter.
 * Return: 1 (success), 0 otherwise.
 */
int alias_exchange(inf_t *inf)
{
	int x;
	list_t *node;
	char *p;

	for (x = 0; x < 10; x++)
	{
		node = node_starts_with(inf->alias, inf->argv[0], '=');
		if (!node)
			return (0);
		free(inf->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
		{
			return (0);
		p = _strdup(p + 1);
		}
		if (!p)
		{
			return (0);
		inf->argv[0] = p;
		}
	}
	return (1);
}

/**
 * vars_exchange - exchanges vars in the token.
 * @inf: the struct parameter.
 * Return: 1 (success), 0 otherwise.
 */
int vars_exchange(inf_t *inf)
{
	int x = 0;
	list_t *node;

	for (x = 0; inf->argv[x]; x++)
	{
		if (inf->argv[x][0] != '$' || !inf->argv[x][1])
			continue;
		if (!_strcmp(inf->argv[x], "$?"))
		{
			string_replace(&(inf->argv[x]),
				_strdup(transfer_numb(inf->status, 10, 0)));
			continue;
		}
		if (!_strcmp(inf->argv[x], "$$"))
		{
			string_replace(&(inf->argv[x]),
				_strdup(transfer_numb(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(inf->env, &inf->argv[x][1], '=');
		if (node)
		{
			string_replace(&(inf->argv[x]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		string_replace(&inf->argv[x], _strdup(""));
	}
	return (0);
}

/**
 * string_replace - replaces a string.
 * @prev: previous string address.
 * @new: the new string.
 * Return: 1 (success), 0 otherwise.
 */
int string_replace(char **prev, char *new)
{
	free(*prev);
	*prev = new;
	return (1);
}

/**
 * chain_delim - checks if a char in a buffer is a chain delimiter.
 * @inf: the struct parameter.
 * @buff: the buffer.
 * @p: current position in buff.
 * Return: 1 (success), 0 otherwise.
 */
int chain_delim(inf_t *inf, char *buff, size_t *p)
{
	size_t x = *p;

	if (buff[x] == '|' && buff[x + 1] == '|')
	{
		buff[x] = 0;
		x++;
		inf->cmd_buf_type = CMD_OR;
	}
	else if (buff[x] == '&' && buff[x + 1] == '&')
	{
		buff[x] = 0;
		x++;
		inf->cmd_buf_type = CMD_AND;
	}
	else if (buff[x] == ';')
	{
		buff[x] = 0;
		inf->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = x;
	return (1);
}

/**
 * chain_rev - checks if to keep chaining based on last stat.
 * @inf: the struct parameter.
 * @buff: the buffer.
 * @p: current position in buff.
 * @i: starting position in buff.
 * @len: length of buff.
 * Return: Void.
 */
void chain_rev(inf_t *inf, char *buff, size_t *p, size_t i, size_t len)
{
	size_t x = *p;

	if (inf->cmd_buf_type == CMD_AND)
	{
		if (inf->status)
		{
			buff[i] = 0;
			x = len;
		}
	}
	if (inf->cmd_buf_type == CMD_OR)
	{
		if (!inf->status)
		{
			buff[i] = 0;
			x = len;
		}
	}
	*p = x;
}
