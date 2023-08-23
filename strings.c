#include "shell.h"

/**
 * _strncpy - copies a string.
 * @dest: the destination that the string will be copied to.
 * @src: the string that will be copied.
 * @n: the number of characters to be copied.
 * Return: the copied string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, x;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		x = i;
		while (x < n)
		{
			dest[x] = '\0';
			x++;
		}
	}
	return (s);
}

/**
 * _strncat - concatenates two strings.
 * @dest: 1st string
 * @src: 2nd string
 * @n: the number of bytes to be added.
 * Return: the new string after concatenating.
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, x;
	char *s = dest;

	i = 0;
	x = 0;
	while (dest[i] != '\0')
		i++;
	while (src[x] != '\0' && j < n)
	{
		dest[i] = src[x];
		i++;
		x++;
	}
	if (x < n)
		dest[i] = '\0';
	return (s);
}

/**
 * _strchr - locating a character within a string.
 * @s: the parsed string.
 * @c: the character to search for.
 * Return: (s) the first occurance of the specified character.
 */
char *_strchr(char *s, char c)
{
	while (*s != c && *s != '\0')
	{
		s++;
	}
	if (*s == c)
	{
		return (s);
	}
	else
	{
		return (NULL);
	}
}
