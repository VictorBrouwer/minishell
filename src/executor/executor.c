#include "shell.h"
#include "libft.h"

int	executor(t_shell *shell)
{
	if (!shell->command_node->next)
		simple_command(shell);
	else
		pipe_line(shell);
	return (SUCCESS);
}

void	simple_command(t_shell *shell)
{
	check_hd_curr_cmd(shell, shell->command_node);
	if (check_built_in(shell->command_node->args[0]))
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

void	pipe_line(t_shell *shell)
{
	t_command	*curr;
	int			pipefd[2];
	pid_t		pid;

	curr = shell->command_node;
	while (curr)
	{
		check_hd_curr_cmd(shell, curr);
		if (pipe(pipefd) == -1)
			return ;
		// if (check_built_in(curr->args[0]))
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
			execute_child(curr, shell, pipefd);
		shell->read_fd = pipefd[READ];
		if (curr->next)
		{
			if (curr->next->next) // bij het 1-na laatste command niet de write end sluiten anders wordt ie dubbel gesloten in execute_last_child. dit moet echter wel gebeuren als laatste command een builtin is 
				close(pipefd[WRITE]);
		}
		curr = curr->next;
	}
	waitpid(-1, &shell->exit_status, 0);
	close(pipefd[READ]);
	close(pipefd[WRITE]);
	return ;
}

void	execute_child(t_command *curr, t_shell *shell, int pipefd[])
{
	close(pipefd[READ]);
	if (curr->next)
	{
		shell->write_fd = pipefd[WRITE];
	}
	else
	{
		close(pipefd[WRITE]);
		shell->write_fd = STDOUT_FILENO; // set standard write_fd to STDOUT and handle redirs afterwards
	}
	execute_non_built_in(shell, curr);
}
