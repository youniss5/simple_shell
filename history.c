#include "shell.h"
/**
 * get_h_file - function that gets the history file
 * @inf: the parameter struct
 * Return: str with history file inside
 */

char *get_h_file(inf_t *inf)
{
	char *dir, *buff;

	dir = get_env(inf, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dir);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_h - creates a file, or appends to an existing one
 * @inf: the parameter struct
 * Return: 1 (success), else -1
 */
int write_h(inf_t *inf)
{
	ssize_t fd;
	char *filename = get_h_file(inf);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = inf->history; node; node = node->next)
	{
		put_sfd(node->str, fd);
		put_fd('\n', fd);
	}
	put_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_h - reads history from a file
 * @inf: the parameter struct
 * Return: histcount on success, 0 for else
 */
int read_h(inf_t *inf)
{
	int i, linecount = 0, last = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *filename = get_h_file(inf);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(fd, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			build_h_list(inf, buff + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_h_list(inf, buff + last, linecount++);
	free(buff);
	inf->histcount = linecount;
	while (inf->histcount-- >= HIST_MAX)
		delete_node_at_index(&(inf->history), 0);
	renumber_h(inf);
	return (inf->histcount);
}

/**
 * build_h_list - functions that adds entry to a history linked list
 * @inf: Structure containing arguments
 * @buff: buffer
 * @linecount: the history linecount and histcount
 * Return: 0 (success)
 */
int build_h_list(inf_t *inf, char *buff, int linecount)
{
	list_t *node = NULL;

	if (inf->history)
		node = inf->history;
	add_node_end(&node, buff, linecount);

	if (!inf->history)
		inf->history = node;
	return (0);
}

/**
 * renumber_h - renumbers the history linked list
 * @inf: Structure containing arguments
 * Return:the new histcount
 */
int renumber_h(inf_t *inf)
{
	list_t *node = inf->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (inf->histcount = i);
}
