#include "shell.h"
#include "libft.h"

int	executor(t_shell *shell)
{
	pid_t			id;
	// int				status;

	if (!shell->command_node->next)
		id = simple_command(shell);
	else
		id = pipe_line(shell);
	// waitpid(id, &status, 0);
	return (SUCCESS);
}

pid_t	simple_command(t_shell *shell)
{
	pid_t	pid;

	check_hd_curr_cmd(shell, shell->command_node);
	// if (check_built_in(shell->command_node->args[0]))
		// handle built_in
	pid = fork();
	if (pid == -1)
			return (ERROR) ;
	if (pid == 0)
		execute_non_built_in(shell, shell->command_node);
	return (pid);
}

pid_t	pipe_line(t_shell *shell)
{
	t_command	*curr;
	int			pipefd[2];
	pid_t		pid;

	curr = shell->command_node;
	while (curr)
	{
		check_hd_curr_cmd(shell, curr);
		if (pipe(pipefd) == -1)
			return (ERROR);
		// if (check_built_in(curr->args[0]))
		pid = fork();
		if (pid == -1)
			return (ERROR);
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
	close(pipefd[READ]);
	close(pipefd[WRITE]);
	return (pid);
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
	handle_redirs_curr_cmd(shell, curr);
	redirect_std_in(shell->read_fd);
	redirect_std_out(shell->write_fd);
	execute_non_built_in(shell, curr);
}
