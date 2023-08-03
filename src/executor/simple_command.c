#include "shell.h"
#include "libft.h"

static void	execute_child_without_pipe(t_shell *shell, t_command *curr);

void	simple_command(t_shell *shell)
{
	int	temp_std_in;
	int	temp_std_out;
	check_hd_curr_cmd(shell, shell->command_node);
	if (!(shell->command_node->args[0]))
	{
		temp_std_in = dup(STDIN_FILENO);
		temp_std_out = dup(STDOUT_FILENO);
		handle_redirs_curr_cmd(shell, shell->command_node);
		if (shell->write_fd != STDOUT_FILENO)
			close(shell->write_fd);
		if (shell->read_fd != STDIN_FILENO)
			close(shell->read_fd);
		redirect_std_in(temp_std_in);
		redirect_std_out(temp_std_out);
	}
	else if (check_built_in(shell->command_node))
	{
		temp_std_in = dup(STDIN_FILENO);
		temp_std_out = dup(STDOUT_FILENO);
		handle_built_in(shell, shell->command_node);
		if (shell->write_fd != STDOUT_FILENO)
			close(shell->write_fd);
		if (shell->read_fd != STDIN_FILENO)
			close(shell->read_fd);
		redirect_std_in(temp_std_in);
		redirect_std_out(temp_std_out);
		return ;
	}
	else
		execute_child_without_pipe(shell, shell->command_node);
}

static void	execute_child_without_pipe(t_shell *shell, t_command *curr)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_and_print_error("fork fail", 1);
	if (pid == 0)
		execute_non_built_in(shell, curr);
	else
		update_status(pid);
}
