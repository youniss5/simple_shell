#include "shell.h"

/**
 * buff_input - chained commands for buffers.
 * @inf: struct parameter.
 * @buff: buffer address.
 * @len: len var address.
 * Return: number of charcters being read.
 */
ssize_t buff_input(inf_t *inf, char **buff, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buff, &len_p, stdin);
#else
		r = get_line(inf, buff, &len_p);
#endif
		if (r > 0)
		{
			if ((*buff)[r - 1] == '\n')
			{
				(*buff)[r - 1] = '\0';
				r--;
			}
			inf->linecount_flag = 1;
			delete_comm(*buff);
			build_h_list(inf, *buff, inf->histcount++);
			{
				*len = r;
				inf->cmd_buf = buff;
			}
		}
	}
	return (r);
}

/**
 * get_length - gets a line without the newline.
 * @inf: struct parameter.
 * Return: length of buffer.
 */
ssize_t get_length(inf_t *inf)
{
	static size_t i, x, len;
	static char *buff;
	ssize_t r = 0;
	char **buff_p = &(inf->arg), *p;

	put_char(BUF_FLUSH);
	r = buff_input(inf, &buff, &len);
	if (r == -1)
	{
		return (-1);
	}
	if (len)
	{
		x = i;
		p = buff + i;

		chain_rev(inf, buff, &x, i, len);
		while (x < len)
		{
			if (chain_delim(inf, buff, &x))
				break;
			x++;
		}

		i = x + 1;
		if (i >= len)
		{
			i = len = 0;
			inf->cmd_buf_type = CMD_NORM;
		}

		*buff_p = p;
		return (_strlen(p));
	}
	*buff_p = buff;
	return (r);
}

/**
 * buff_read - reads the inputted buffer.
 * @inf: struct parameter.
 * @buff: buffer.
 * @size: buffer size.
 * Return: r
 */
ssize_t buff_read(inf_t *inf, char *buff, size_t *size)
{
	ssize_t r = 0;

	if (*size)
		return (0);
	r = read(inf->read_fd, buff, READ_BUF_SIZE);
	if (r >= 0)
		*size = r;
	return (r);
}

/**
 * get_line - gets the next line of input.
 * @inf: struct parameter.
 * @ptr: pointer to buffer.
 * @length: size of pre_allocated ptr buffer whether not NULL.
 * Return: s
 */
int get_line(inf_t *inf, char **ptr, size_t *length)
{
	static size_t i, len;
	size_t k;0
	static char buff[READ_BUF_SIZE];
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
	{
		s = *length;
	}
	if (i == len)
		i = len = 0;

	r = buff_read(inf, buff, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);00

	c = _strchr(buff + i, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
	{
		return (p ? free(p), -1 : -1);
	}
	if (s)
	{
		_strncat(new_p, buff + i, k - i);
	}
	else
		_strncpy(new_p, buff + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigint_Handler - stops ctrl + C.
 * @signal_num: signal number.
 * Return: void.
 */
void sigint_Handler(__attribute__((unused))int signal_num)
{
	put_s("\n");
	put_s("$ ");
	put_char(BUF_FLUSH);
}
