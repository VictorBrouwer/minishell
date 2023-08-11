#include "libft.h"
#include "shell.h"

static int	skip_flags(char ***args);
static int	print_args(char **args, int flag);
static int	check_flag(char *arg);

int	builtin_echo(char **args)
{
	int		flag;
	char	**tmp;

	if (!args)
		return (ERROR);
	tmp = args + 1;
	flag = skip_flags(&tmp);
	if (print_args(tmp, flag) == 1)
		return (1);
	return (0);
}

static int	skip_flags(char ***args)
{
	int	flag;

	flag = check_flag(**args);
	while (*args && flag)
	{
		flag = check_flag(**args);
		if (flag)
			(*args)++;
		else
		{
			flag = 1;
			break ;
		}
	}
	return (flag);
}

static int	print_args(char **args, int flag)
{
	while (*args)
	{
		if (ft_putstr_fd_prot(*args, STDOUT_FILENO, 0) == -1)
			return (1);
		if (*(args + 1))
		{
			if (ft_putstr_fd_prot(" ", STDOUT_FILENO, 0) == -1)
				return (1);
		}
		args++;
	}
	if (ft_putstr_fd_prot("", STDOUT_FILENO, flag < 1) == -1)
		return (1);
	return (0);
}

static int	check_flag(char *arg)
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
	return (1);
}
