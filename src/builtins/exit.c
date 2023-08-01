#include "libft.h"
#include "shell.h"
#include <unistd.h>

int	builtin_exit(char **args, t_shell *shell)
{
	if (shell->command_count > 1)
		exit(0);
	if (args[1])
	{
		if (args[2])
		{
			ft_putstr_fd_protected("exit: too many arguments\n", STDERR_FILENO, 0);
			return (1);
		}
		else if (ft_stris_x(args[1], ft_isdigit))
		{
			ft_putstr_fd_protected("exit", STDOUT_FILENO, 1);
			exit(ft_atoi(args[1]));
		}
		else
		{
			ft_putstr_fd_protected("exit", STDOUT_FILENO, 1);
			ft_putstr_fd_protected("nutshell: exit: ", STDERR_FILENO, 0);
			ft_putstr_fd_protected(args[1], STDERR_FILENO, 0);
			ft_putstr_fd_protected(": numeric argument is required\n", STDERR_FILENO, 0);
			exit(255);
		}
	}
	clean_shell(shell);
	rl_clear_history();
	exit(0);
 }
