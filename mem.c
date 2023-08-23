#include "shell.h"

/**
 * befree - NULL the adress and free the pointer
 * @ptr: address of the pointer to free
 * Return: 1 (freed), 0 (else)
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
