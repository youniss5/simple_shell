#include "shell.h"
/**
 * is_cmd - check if a file is an executable file.
 * @inf: the inf struct.
 * @path: path to the file.
 * Return: 1 (success) and 0 (failure)
 */
int is_cmd(inf_t *inf, char *path)
{
	struct stat st;

	(void)inf;
	if (!path || stat(path, &st))
	{
		return (0);
	}
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_char - duplicates characters.
 * @pathstr: the path str.
 * @start: start index.
 * @stop: stop index.
 * Return: pointer to the new buffer.
 */
char *dup_char(char *pathstr, int start, int stop)
{
	static char buff[1024];
	int x = 0, k = 0;

	for (k = 0, x = start; x < stop; x++)
		if (pathstr[x] != ':')
			buff[k++] = pathstr[x];
	buff[k] = 0;
	return (buff);
}

/**
 * f_path - finds this cmd in the path str.
 * @inf: the inf struct.
 * @pathstr: the path str.
 * @cmd: the cmd to find.
 * Return: full path of cmd if found or not (NULL).
 */
char *f_path(inf_t *inf, char *pathstr, char *cmd)
{
	int i = 0, current = 0;
	char *path;

	if (!pathstr)
	{
		return (NULL);
	}
	if ((_strlen(cmd) > 2) && goes_by(cmd, "./"))
	{
		if (is_cmd(inf, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_char(pathstr, current, i);
			if (!*path)
			{
				_strcat(path, cmd);
			}
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(inf, path))
			{
				return (path);
			}
			if (!pathstr[i])
				break;
			current = i;
		}
		i++;
	}
	return (NULL);
}
