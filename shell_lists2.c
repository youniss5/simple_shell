#include "shell.h"
/**
 * get_node_index - gets the index of a node.
 * @head: pointer to the list head.
 * @node: pointer to the node.
 * Return: -1 or index of node.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t x = 0;

	while (head)
	{
		if (head == node)
		{
			return (x);
		}
		head = head->next;
		x++;
	}
	return (-1);
}
/**
 * print_list - prints all elements of a list_t linked list.
 * @h: pointer to the first node.
 * Return: size of the list.
 */
size_t print_list(const list_t *h)
{
	size_t x = 0;

	while (h)
	{
		put_s(transfer_numb(h->num, 10, 0));
		put_char(':');
		put_char(' ');
		put_s(h->str ? h->str : "(nil)");
		put_s("\n");
		h = h->next;
		x++;
	}
	return (x);
}

/**
 * node_starts_with - gets node its str starts with prefix.
 * @node: pointer to list head.
 * @prefix: str to match.
 * @c: next character after prefix to match.
 * Return: null or match node.
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = goes_by(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
/**
 * list_len - gets the length of a linked list.
 * @head: pointer to the first node.
 * Return: size of the list.
 */
size_t list_len(const list_t *head)
{
	size_t x = 0;

	while (head)
	{
		head = head->next;
		x++;
	}
	return (x);
}

/**
 * list_to_strings - returns an array of strs of the list->str.
 * @head: pointer to the first node.
 * Return: array of strings.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head);
	size_t x;
	char **strs;
	char *str;

	if (!head || !i)
	{
		return (NULL);
	}
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
	{
		return (NULL);
	}
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (x = 0; x < i; x++)
				free(strs[x]);
			free(strs);
			return (NULL);
		}
		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}
