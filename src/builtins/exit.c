#include "libft.h"
#include "shell.h"

static void	exit_numeric_args_required(char *arg, t_shell *shell);
static void	exit_with_status(char *arg, t_shell *shell);

int	builtin_exit(char **args, t_shell *shell)
{
	if (shell->command_count > 1)
		;
	else if (args[1])
	{
		if (args[2])
		{
			ft_putstr_fd_prot("exit: too many arguments\n", STDERR_FILENO, 0);
			return (1);
		}
		else if (ft_stris_x(args[1], ft_isdigit) || \
			(args[1][0] == '-' && ft_stris_x(args[1] + 1, ft_isdigit)))
			exit_with_status(args[1], shell);
		else
			exit_numeric_args_required(args[1], shell);
	}
	clean_shell(shell);
	rl_clear_history();
	exit(0);
}

static void	exit_with_status(char *arg, t_shell *shell)
{
	int	status;

	status = 0;
	if (ft_putstr_fd_prot("exit", STDOUT_FILENO, 1) == -1)
		status = 1;
	clean_shell(shell);
	rl_clear_history();
	if (status == 1)
		exit (1);
	exit(ft_atoi(arg));
}

static void	exit_numeric_args_required(char *arg, t_shell *shell)
{
	int	status;

	status = 0;
	if (ft_putstr_fd_prot("exit", STDOUT_FILENO, 1) == -1)
		status = 1;
	else if (ft_putstr_fd_prot("nutshell: exit: ", STDERR_FILENO, 0) == -1)
		status = 1;
	else if (ft_putstr_fd_prot(arg, STDERR_FILENO, 0) == -1)
		status = 1;
	else if (ft_putstr_fd_prot(": numeric argument required\n", STDERR_FILENO, 0) == -1)
		status = 1;
	clean_shell(shell);
	rl_clear_history();
	if (status == 1)
		exit(1);
	exit (255);
}
