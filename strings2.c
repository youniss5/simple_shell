#include "shell.h"

/**
 * _strcpy - copies a string.
 * @dst: the destination of newly allocated buffer.
 * @src: the source.
 * Return: pointer to the new destination.
 */
char *_strcpy(char *dst, char *src)
{
	int x = 0;

	if (dst == src || src == 0)
		return (dst);
	while (src[x])
	{
		dst[x] = src[x];
		x++;
	}
	dst[x] = 0;
	return (dst);
}

/**
 * put_s - prints a string.
 * @str: the inputted string.
 * Return: void.
 */
void put_s(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		put_char(str[x]);
		x++;
	}
}

/**
 * put_char - prints the character c to standard output.
 * @c: The character to be printed.
 * Return: 1 (success), -1 (failure).
 */
int put_char(char c)
{
	static int x;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(1, buff, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buff[x++] = c;
	return (1);
}

/**
 * _strdup - duplicates a string.
 * @str: string to be duplicated.
 * Return: the duplicated string.
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *dup;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	dup = malloc(sizeof(char) * (length + 1));
	if (!dup)
		return (NULL);
	for (length++; length--;)
		dup[length] = *--str;
	return (dup);
}
