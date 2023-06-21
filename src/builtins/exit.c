#include "libft.h"
#include "shell.h"

void	builtin_exit(t_command *cmd)
{
	ft_putstr_fd_protected("exit\n", STDOUT_FILENO, 1);
	if (cmd->args[1])
	{
		if (!cmd->args[2])
		{
			ft_putstr_fd_protected("Error, exit takes max one argument.\n");
			// free;
			exit(255);
		}
		else if (ft_stris_x(cmd->args[1], ft_isdigit))
		{
			// free
		}
		else
		{
			ft_putstr_fd_protected("Error, argument is not a number.\n");
			// free;
			exit(255);
		}
	}
	clear_everything
	exit(0);


}