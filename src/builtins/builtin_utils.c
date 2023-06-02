#include "libft.h"
#include "shell.h"

int	ft_putstr_fd_protected(char *s, int fd, int newline)
{
	int	x;

	x = 0;
	while (s[x])
	{
		if (write(fd, &s[x], 1) == -1)
			return (-1);
		x++;
	}
	if (newline)
	{
		if (write(fd, "\n", 1) == -1)
			return (-1);
	}
	return (x);
}