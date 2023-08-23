#include "shell.h"

/**
 * mem_free - frees the pointer.
 * @ptr: the pointer to be freed.
 * Return: 1 (freed), 0 (failure).
 */
int mem_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
