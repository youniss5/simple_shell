#include "shell.h"
/**
 * _mem_set - fills memory with a const byte.
 * @s: pointer to memory area.
 * @b: byte to fill *s.
 * @n: amount of bytes to be filled.
 * Return: s (pointer to the memory area).
 */
char *_mem_set(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		s[i] = b;
	}
	return (s);
}

/**
 * _ffree - frees a str of strings
 * @pp: str of strings
 */
void _ffree(char **pp)
{
	char **a = pp;

	if (!pp)
	{
		return;
	}
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - function that reallocates a block of memory.
 * @ptr: pointer to previous mallocated block.
 * @old_size: byte size of previous block.
 * @new_size: byte size of new block.
 * Return: pointer to the buffer after extension if any.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
	{
		return (malloc(new_size));
	}
	if (!new_size)
	{
		return (free(ptr), NULL);
	}
	if (new_size == old_size)
	{
		return (ptr);
	}
	p = malloc(new_size);
	if (!p)
	{
		return (NULL);
	}
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
