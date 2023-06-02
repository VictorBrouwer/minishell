#include "libft.h"
#include "shell.h"

static int check_flag(char **args);

int ft_echo(char **args)
{
	int flag;

	flag = check_flag(args);
	if (flag)
		args++;
	while (*args)
	{
		if (ft_putstr_fd_protected(*args, 1, 0) == -1)
			return (1);
		if (*(args + 1))
		{
			if (ft_putstr_fd_protected(" ", 1, 0) == -1)
				return (1);
		}
		args++;
	}
	if (ft_putstr_fd_protected("", 1, (flag == 0)) == -1)
		return (1);
	return (0);
}

static int check_flag(char **args)
{
	if (args[0] && ft_strncmp(*args, "-n", 3) == 0)
			return (1);
	return	(0);
}

// int main(int argc, char **argv)
// {
// 	(void) argc;
// 	argv++;
// 	ft_echo(argv);
// 	return (0);
// }