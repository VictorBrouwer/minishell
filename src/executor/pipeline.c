#include "shell.h"
#include "libft.h"
#include <unistd.h>

static void	execute_compound_command(t_shell *shell, t_command *curr);

void	pipe_line(t_shell *shell)
{
	t_command	*curr;
	pid_t		pid;

	curr = shell->command_node;
	while (curr->next)
	{
		execute_compound_command(shell, curr);
		curr = curr->next;
	}
	check_hd_curr_cmd(shell, curr);
	pid = fork();
	if (pid == -1)
		exit_and_print_error("fork fail", 1);
	if (pid == 0)
		execute_last_child(curr, shell);
	if (shell->read_fd != STDIN_FILENO)
		close(shell->read_fd);
	update_status(pid);
	while (wait(NULL) > 0)
		continue ;
	return ;
}

static void	execute_compound_command(t_shell *shell, t_command *curr)
{
	int			pipefd[2];
	pid_t		pid;

	check_hd_curr_cmd(shell, curr);
	if (pipe(pipefd) == -1)
		exit_and_print_error("pipe fail", 1);
	pid = fork();
	if (pid == -1)
		exit_and_print_error("fork fail", 1);
	if (pid == 0)
		execute_child(curr, shell, pipefd);
	if (shell->read_fd != STDIN_FILENO)
		close(shell->read_fd);
	shell->read_fd = dup(pipefd[READ]);
	close(pipefd[READ]);
	close(pipefd[WRITE]);
}

void	execute_child(t_command *curr, t_shell *shell, int pipefd[])
{
	close(pipefd[READ]);
	redirect_std_out(pipefd[WRITE]);
	if (!(curr->args[0]))
	{
		handle_redirs_curr_cmd(shell, curr);
		close_open_fds(shell);
		exit(0);
	}
	if (check_built_in(curr))
		exit(handle_built_in(shell, curr));
	execute_non_built_in(shell, curr);
}

void	execute_last_child(t_command *curr, t_shell *shell)
{
	shell->write_fd = STDOUT_FILENO;
	if (!(curr->args[0]))
	{
		handle_redirs_curr_cmd(shell, curr);
		close_open_fds(shell);
		exit(0);
	}
	if (check_built_in(curr))
		exit(handle_built_in(shell, curr));
	execute_non_built_in(shell, curr);
}
