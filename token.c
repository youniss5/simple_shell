#include "shell.h"

/**
 * splitter - splits a string into tokens.
 * @str: the string to be splitted.
 * @delim: the delimiter.
 * Return: a pointer to an array of strings.
 */

char **splitter(char *str, char *delim)
{
	int i, x, k, m, ntoken = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], delim) && (is_delim(str[i + 1], delim)
				|| !str[i + 1]))
			ntoken++;

	if (ntoken == 0)
		return (NULL);
	s = malloc((1 + ntoken) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, x = 0; x < ntoken; x++)
	{
		while (is_delim(str[i], delim))
			i++;
		k = 0;
		while (!is_delim(str[i + k], delim) && str[i + k])
			k++;
		s[x] = malloc((k + 1) * sizeof(char));
		if (!s[x])
		{
			for (k = 0; k < x; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[x][m] = str[i++];
		s[x][m] = 0;
	}
	s[x] = NULL;
	return (s);
}

/**
 * splitter2 - splits a string into tokens.
 * @str: the string to be splitted.
 * @delim: the delimiter.
 * Return: a pointer to an array of strings.
 */
char **splitter2(char *str, char delim)
{
	int i, x, k, m, ntoken = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delim && str[i + 1] == delim) ||
		    (str[i] != delim && !str[i + 1]) || str[i + 1] == delim)
			ntoken++;
	if (ntoken == 0)
		return (NULL);
	s = malloc((1 + ntoken) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, x = 0; x < ntoken; x++)
	{
		while (str[i] == delim && str[i] != delim)
			i++;
		k = 0;
		while (str[i + k] != delim && str[i + k] && str[i + k] != delim)
			k++;
		s[x] = malloc((k + 1) * sizeof(char));
		if (!s[x])
		{
			for (k = 0; k < x; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[x][m] = str[i++];
		s[x][m] = 0;
	}
	s[x] = NULL;
	return (s);
}
