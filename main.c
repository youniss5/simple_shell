#include "shell.h"
/**
 * main - entry point.
 * @ac: arg count.
 * @av: arg vector.
 * Return: 0 (success)or 1 (error).
 */
int main(int ac, char **av)
{
	inf_t inf[] = { inf_init };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
			{
				exit(126);
			}
			if (errno == ENOENT)
			{
				e_puts(av[0]);
				e_puts(": 0: Can't open ");
				e_puts(av[1]);
				e_putchar('\n');
				e_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inf->read_fd = fd;
	}
	env_list(inf);
	read_h(inf);
	cmd_loop(inf, av);
	return (EXIT_SUCCESS);
}
