#include "shell.h"
#include "libft.h"

void	execute_non_built_in(t_shell *shell, t_command *curr)
{
	char	*command_with_path;

	command_with_path = get_command_path(shell, curr->args[0]);
	if (command_with_path == NULL)
		return ;
	// handle_redirs_curr_cmd(shell, curr);
	// redirect_std_in(shell->read_fd);
	// redirect_std_out(shell->write_fd);
	execve(command_with_path, curr->args, shell->envp);
}