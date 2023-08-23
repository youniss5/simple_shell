#include "shell.h"
/**
 * err_atoi - converts a str to an int.
 * @s: str to be converted.
 * Return: 0 if no numbers to convert in str, converted number or
 *       -1 (error).
 */
int err_atoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * p_err - prints an error message.
 * @inf: the parameter and return inf struct.
 * @estr: str containing error type.
 * Return: 0 if no numbers in str, converted number or
 *        -1 (error).
 */
void p_err(inf_t *inf, char *estr)
{
	e_puts(inf->fname);
	e_puts(": ");
	print_d(inf->line_count, STDERR_FILENO);
	e_puts(": ");
	e_puts(inf->argv[0]);
	e_puts(": ");
	e_puts(estr);
}

/**
 * print_d -  prints int number to base 10.
 * @input: input.
 * @fd: the file descriptor to write to.
 * Return: no. of chars printed.
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = put_char;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = e_putchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;
	return (count);
}

/**
 * transfer_numb - function that converts (a clone of atoi).
 * @num: number.
 * @base: base.
 * @flags: argument flags.
 * Return: str.
 */
char *transfer_numb(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
	{
		*--ptr = sign;
	}
	return (ptr);
}

/**
 * delete_comm -  replaces first instance of '#' with '\0'.
 * @buff: address of the str to modify.
 * Return: 0 (success).
 */
void delete_comm(char *buff)
{
	int i;

	for (i = 0; buff[i] != '\0'; i++)
		if (buff[i] == '#' && (!i || buff[i - 1] == ' '))
		{
			buff[i] = '\0';
			break;
		}
}
