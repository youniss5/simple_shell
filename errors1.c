#include "shell.h"

/**
 *e_puts - prints an input string
 * @str: string to be printed
 * Return: Void
 */
void e_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		e_putchar(str[i]);
		i++;
	}
}

/**
 * e_putchar - writes the char c to stderr
 * @c: The character to print
 * Return: 1 (success) , -1 (error)
 */
int e_putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * put_fd - writes to given fd the character c.
 * @c:  char to print
 * @fd:  fd to write to
 * Return: 1 ( success) , 0 ( error)
 */
int put_fd(char c, int fd)
{
	static int i;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buff, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buff[i++] = c;
	return (1);
}

/**
 *put_sfd - prints an input str
 * @str: string to be printed
 * @fd: fd to write to
 * Return: number of chars
 */
int put_sfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += put_fd(*str++, fd);
	}
	return (i);
}
