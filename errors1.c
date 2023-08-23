#include "shell.h"

/**
 *e_puts - prints an input string.
 * @str: string to be printed.
 * Return: Void.
 */
void e_puts(char *str)
{
	int x = 0;

	if (!str)
	{
		return;
	}
	while (str[x] != '\0')
	{
		e_putchar(str[x]);
		x++;
	}
}

/**
 * e_putchar - writes the char c to stderr.
 * @c: The character to be printed.
 * Return: 1 (success) , -1 (error).
 */
int e_putchar(char c)
{
	static int x;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(2, buff, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buff[x++] = c;
	return (1);
}

/**
 * put_fd - writes to given fd the character c.
 * @c:  char to be printed.
 * @fd:  fd to write to.
 * Return: 1 ( success), 0 ( error).
 */
int put_fd(char c, int fd)
{
	static int x;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(fd, buff, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buff[x++] = c;
	return (1);
}

/**
 * put_sfd - prints an input str.
 * @str: string to be printed.
 * @fd: fd to write to.
 * Return: number of chars.
 */
int put_sfd(char *str, int fd)
{
	int x = 0;

	if (!str)
		return (0);
	while (*str)
	{
		x += put_fd(*str++, fd);
	}
	return (x);
}
