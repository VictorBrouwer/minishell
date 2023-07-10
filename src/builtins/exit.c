#include "libft.h"
#include "shell.h"
#include <unistd.h>

int	builtin_exit(char **args, t_shell *shell)
{
	ft_putstr_fd_protected("exit\n", STDOUT_FILENO, 0);
 	if (args[1])
 	{
 		if (args[2])
 		{
 			ft_putstr_fd_protected("exit: too many arguments\n", STDERR_FILENO, 0);
 			// free;
			return(-1);
 		}
 		else if (ft_stris_x(args[1], ft_isdigit))
 		{
 			// free
			ft_putstr_fd_protected("exit\n", STDOUT_FILENO, 1);
			exit(0);
 		}
 		else
		{
 			ft_putstr_fd_protected("exit: %s: numeric argument is required\n", STDERR_FILENO, 0);
 			ft_putstr_fd_protected(args[1], STDERR_FILENO, 0);
 			ft_putstr_fd_protected(": numeric argument is required\n", STDERR_FILENO, 0);
 			// free;
 			exit(255);
 		}
 	}
 	/* free + clear_everything */
	printf("test\n");
	clean_shell(shell);
	rl_clear_history();
	exit(0);
 }
