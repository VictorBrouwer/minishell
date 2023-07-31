#include "shell.h"
#include "libft.h"
#include <unistd.h>

bool	execute_compound_command(t_shell *shell, t_command *curr);

void	pipe_line(t_shell *shell)
{
	t_command	*curr;
	int			pipefd[2];
	pid_t		pid;

	curr = shell->command_node;
	while (curr->next)
	{
		if (execute_compound_command(shell, curr))
			return ;
		curr = curr->next;
	}
	check_hd_curr_cmd(shell, curr);
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
		execute_last_child(curr, shell, pipefd);
	if (shell->read_fd != STDIN_FILENO)
		close(shell->read_fd);
	update_status(pid);
	while (wait(NULL) > 0)
		continue ;
	return ;
}

bool	execute_compound_command(t_shell *shell, t_command *curr)
{
	int			pipefd[2];
	pid_t		pid;

	check_hd_curr_cmd(shell, curr);
	if (pipe(pipefd) == -1)
		return (ERROR);
	pid = fork();
	if (pid == -1)
		return (ERROR);
	if (pid == 0)
		execute_child(curr, shell, pipefd);
	if (shell->read_fd != STDIN_FILENO)
		close(shell->read_fd);
	shell->read_fd = pipefd[READ];
	shell->read_fd = dup(shell->read_fd);
	close(pipefd[READ]);
	close(pipefd[WRITE]);
	return (SUCCESS);
}

void	execute_child(t_command *curr, t_shell *shell, int pipefd[])
{
	close(pipefd[READ]);
	redirect_std_out(pipefd[WRITE]);
	if (!(curr->args[0]))
	{
		handle_redirs_curr_cmd(shell, curr);
		exit(0);
	}
	if (handle_built_in(shell, curr))
		exit(0);
	execute_non_built_in(shell, curr);
}

void	execute_last_child(t_command *curr, t_shell *shell, int pipefd[])
{
	close(pipefd[READ]);
	close(pipefd[WRITE]);
	shell->write_fd = STDOUT_FILENO;
	if (!(curr->args[0]))
	{
		handle_redirs_curr_cmd(shell, curr);
		exit(0);
	}
	if (handle_built_in(shell, curr))
		exit(0);
	execute_non_built_in(shell, curr);
}
