#include "libft.h"
#include "shell.h"
#include <sys/errno.h>

static int check_flag(char **args);

// TODO: FIX multple -n flags
int builtin_echo(char **args)
{
	int flag;

	if (args)
		args++;
	flag = 0;
	flag += check_flag(args);
	args += flag;
	while (*args)
	{
		if (ft_putstr_fd_protected(*args, STDOUT_FILENO, 0) == -1)
			return (ERROR);
		if (*(args + 1))
		{
			if (ft_putstr_fd_protected(" ", STDOUT_FILENO, 0) == -1)
				return (ERROR);
		}
		args++;
	}
	/* if (ft_putstr_fd_protected("", STDOUT_FILENO, (flag == 0)) == -1) */
	if (ft_putstr_fd_protected("", STDOUT_FILENO, flag < 1) == -1)
		return (ERROR);
	return (0);
}

static int check_flag(char **args)
{
	int	i;
	int	flag;

	flag = 0;
	if (!args[flag])
		return (flag);
	while (args[flag])
	{
		i = 0;
		if (!(args[flag][i] == '-'))
			break ;
		i++;
		while (args[flag][i])
		{
			if (args[flag][i] != 'n')
				return (flag);
			i++;
		}
		flag++;
		/* if (ft_strncmp(args[0], "-n", 2) == 0) */
		/* 	return (1); */
	}
	return	(0);
}

// int main(int argc, char **argv)
// {
// 	(void) argc;
// 	argv++;
// 	ft_echo(argv);
// 	return (0);
// }
