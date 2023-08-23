#include "shell.h"
/**
 * interactive_md - returns true when shell is in an interactive mode.
 * @inf: struct address.
 * Return: 1 in case of interactive mode, 0 otherwise.
 */
int interactive_md(inf_t *inf)
{
	return (isatty(STDIN_FILENO) && inf->read_fd <= 2);
}

/**
 *_isalpha - search for alphabetic characters.
 *@c: The character to be inputted.
 *Return: 1 if c is an alphabet , 0 otherwise.
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 *_atoi - converts a string to an integer fourm.
 *@s: the string to be converted.
 *Return: 0 if no numbers, returns converted number otherwise.
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, oput;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
		{
			sign *= -1;
		}

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
		{
			flag = 2;
		}
	}

	if (sign == -1)
	{
		oput = -result;
	}
	else
		oput = result;
	return (oput);
}

/**
 * delim_chk - checks if the character matches the delimeter.
 * @c: the char to check.
 * @delim: the delimeter.
 * Return: if true returns 1, if false returns 0.
 */
int delim_chk(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
		{
			return (1);
		}
	}
	return (0);
}
