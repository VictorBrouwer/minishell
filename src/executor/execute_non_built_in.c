#include "shell.h"
#include "libft.h"

void	execute_non_built_in(t_shell *shell, t_command *curr)
{
	char	*command_with_path;

	command_with_path = get_command_path(shell, curr->args[0]);
	if (!command_with_path)
		exit(ERROR);
	handle_redirs_curr_cmd(shell, curr);
	if (redirect_std_in(shell->read_fd) == -1)
		exit (1);
	if (redirect_std_out(shell->write_fd) == -1)
		exit (1);
	if (execve(command_with_path, curr->args, shell->envp) == -1)
		exit_and_print_error_command("command not found", 127, \
		command_with_path);
}
