#include "shell.h"

/**
 * _strcat - concatenates two strings.
 * @src: the source string.
 * @dest: the destination string.
 * Return: pointer to dest buffer.
 */
char *_strcat(char *dest, char *src)
{
	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (dest);
}

/**
 * _strlen - returns the length of a certain string.
 * @s: the string being checked.
 * Return: length of string.
 */
int _strlen(char *s)
{
	int x = 0;

	if (!s)
		return (0);

	while (*s++)
		x++;
	return (x);
}

/**
 * _strcmp - compares two strangs.
 * @s1: the 1st string.
 * @s2: the second string.
 * Return: (positive) if s1 > s2, (negative) if s1 < s2, (0) if s1 == s2.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
	{
		return (0);
	}
	else
	{
		return (*s1 < *s2 ? -1 : 1);
	}
}

/**
 * goes_by - checks if a substring starts with a haystack.
 * @str: string being searched.
 * @substr: the certain substring.
 * Return: next char of haystack or NULL.
 */
char *goes_by(const char *str, const char *substr)
{
	while (*substr)
		if (*substr++ != *str++)
			return (NULL);
	return ((char *)str);
}
