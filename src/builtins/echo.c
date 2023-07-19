#include "libft.h"
#include "shell.h"
#include <sys/errno.h>

static int check_flag(char *arg);

int builtin_echo(char **args)
{
	int flag;

	if (!args)
		return (ERROR);
	args++;
	flag = check_flag(*args);
	while (*args && flag)
	{
		flag = check_flag(*args);
		if (flag)
			args++;
		else
		{
			flag = 1;
			break;
		}
	}
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
	if (ft_putstr_fd_protected("", STDOUT_FILENO, flag < 1) == -1)
		return (ERROR);
	return (0);
}

static int check_flag(char *arg)
{
	if (!arg || *arg != '-')
		return (0);
	arg++;
	while (*arg)
	{
		if (*arg == 'n')
			arg++;
		else
			return (0);
	}
	return	(1);
}

// int main(int argc, char **argv)
// {
// 	(void) argc;
// 	argv++;
// 	ft_echo(argv);
// 	return (0);
// }
