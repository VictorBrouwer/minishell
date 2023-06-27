#include "shell.h"
#include "libft.h"

void	simple_command(t_shell *shell)
{
	check_hd_curr_cmd(shell, shell->command_node);
	if (!(shell->command_node->args[0]))
	{
		handle_redirs_curr_cmd(shell, shell->command_node);
		return ;
	}
	else if (execute_built_in(shell, shell->command_node))
		return ;
	else
		execute_child_without_pipe(shell, shell->command_node);
	wait(NULL);
}

void	execute_child_without_pipe(t_shell *shell, t_command *curr)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
			return ;
	if (pid == 0)
		execute_non_built_in(shell, curr);
}