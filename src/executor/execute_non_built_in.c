#include "shell.h"
#include "libft.h"

void	execute_non_built_in(t_shell *shell, t_command *curr)
{
	char	*command_with_path;

	command_with_path = get_command_path(shell, curr->args[0]);
	if (!command_with_path)
	{
		ft_putstr_fd_protected("Could not find file or directory\n", 2, 0);
		clean_commands(shell->command_node);
		exit(ERROR);
	}
	if (handle_redirs_curr_cmd(shell, curr))
		return (clean_commands(shell->command_node), exit(ERROR));
	if (shell->read_fd != STDIN_FILENO)
		redirect_std_in(shell->read_fd);
	if (shell->write_fd != STDOUT_FILENO)
		redirect_std_out(shell->write_fd);
	// printf("command = %s, read fd = %d, write fd = %d\n", command_with_path, shell->read_fd, shell->write_fd);
	if (execve(command_with_path, curr->args, shell->envp) == -1)
	{
		perror(command_with_path);
		clean_commands(shell->command_node);
		exit(ERROR);
	}
}