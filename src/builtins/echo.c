#include "libft.h"
#include "shell.h"
#include <sys/errno.h>

static int	skip_flags(char ***args);
static int	print_args(char **args, int flag);
static int	check_flag(char *arg);

/*TODO: echo "test"test"test"  vs echo dit is een test */
int builtin_echo(char **args)
{
	int		flag;
	char	**tmp;

	if (!args)
		return (ERROR);
	tmp = args;
	tmp++;
	flag = skip_flags(&tmp);
	/* flag = check_flag(*args); */
	/* while (*args && flag) */
	/* { */
	/* 	flag = check_flag(*args); */
	/* 	if (flag) */
	/* 		args++; */
	/* 	else */
	/* 	{ */
	/* 		flag = 1; */
	/* 		break; */
	/* 	} */
	/* } */
	if (print_args(tmp, flag) == 1)
		return (1);
	return (0);
	/* while (*args) */
	/* { */
	/* 	if (ft_putstr_fd_protected(*args, STDOUT_FILENO, 0) == -1) */
	/* 		return (ERROR); */
	/* 	if (*(args + 1)) */
	/* 	{ */
	/* 		if (ft_putstr_fd_protected(" ", STDOUT_FILENO, 0) == -1) */
	/* 			return (ERROR); */
	/* 	} */
	/* 	args++; */
	/* } */
	/* if (ft_putstr_fd_protected("", STDOUT_FILENO, flag < 1) == -1) */
	/* 	return (ERROR); */
}

static int	skip_flags(char ***args)
{
	int flag;

	flag = check_flag(**args);
	while (*args && flag)
	{
		flag = check_flag(**args);
		if (flag)
			(*args)++;
		else
		{
			flag = 1;
			break;
		}
	}
	return (flag);
}

static int	print_args(char **args, int flag)
{
	while (*args)
	{
		if (ft_putstr_fd_protected(*args, STDOUT_FILENO, 0) == -1)
			return (1);
		if (*(args + 1))
		{
			if (ft_putstr_fd_protected(" ", STDOUT_FILENO, 0) == -1)
				return (1);
		}
		args++;
	}
	if (ft_putstr_fd_protected("", STDOUT_FILENO, flag < 1) == -1)
		return (1);
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
