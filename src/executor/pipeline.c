#include "shell.h"
#include "libft.h"

void	pipe_line(t_shell *shell)
{
	t_command	*curr;
	int			pipefd[2];
	pid_t		pid;

	curr = shell->command_node;
	while (curr->next)
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
		if (curr->next) // bij het 1-na laatste command niet de write end sluiten anders wordt ie dubbel gesloten in execute_last_child. dit moet echter wel gebeuren als laatste command een builtin is 
			close(pipefd[WRITE]);
		curr = curr->next;
	}
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
		execute_last_child(curr, shell, pipefd);
	waitpid(-1, &shell->exit_status, 0);
	close(pipefd[READ]);
	close(pipefd[WRITE]);
	return ;
}

void	execute_child(t_command *curr, t_shell *shell, int pipefd[])
{
	close(pipefd[READ]);
	shell->write_fd = pipefd[WRITE];
	if (!(curr->args[0]))
	{
		handle_redirs_curr_cmd(shell, curr);
		return ;
	}
	execute_non_built_in(shell, curr);
}

void	execute_last_child(t_command *curr, t_shell *shell, int pipefd[])
{
	close(pipefd[READ]);
	close(pipefd[WRITE]);
	shell->write_fd = STDOUT_FILENO; // set standard write_fd to STDOUT and handle redirs afterwards
	if (!(curr->args[0]))
	{
		handle_redirs_curr_cmd(shell, curr);
		return ;
	}
	execute_non_built_in(shell, curr);
}



// pid_t	pipe_line(t_shell *shell)
// {
// 	t_command	*curr;
// 	int			pipefd[2];
// 	pid_t		pid;

// 	curr = shell->command_node;
// 	while (curr->next)
// 	{
// 		check_hd_curr_cmd(shell, curr);
// 		if (pipe(pipefd) == -1)
// 			return (ERROR);
// 		// if (check_built_in(curr->args[0]))
// 		pid = fork();
// 		if (pid == -1)
// 			return (ERROR);
// 		if (pid == 0)
// 			execute_child(curr, shell, pipefd);
// 		shell->read_fd = pipefd[READ];
// 		if (curr->next->next) // bij het 1-na laatste command niet de write end sluiten anders wordt ie dubbel gesloten in execute_last_child. dit moet echter wel gebeuren als laatste command een builtin is 
// 			close(pipefd[WRITE]);
// 		curr = curr->next;
// 	}
// 	check_hd_curr_cmd(shell, curr);
// 	if (pipe(pipefd) == -1)
// 		return (ERROR);
// 	// if (check_built_in(curr->args[0]))
// 	pid = fork();
// 	if (pid == -1)
// 		return (ERROR);
// 	if (pid == 0)
// 		execute_child(curr, shell, pipefd);
// 	close(pipefd[READ]);
// 	close(pipefd[WRITE]);
// 	return (pid);
// }


// void	execute_last_child(t_command *curr, t_shell *shell, int pipefd[2])
// {
// 	handle_redirs_curr_cmd(shell, curr);
// 	redirect_std_in(shell->read_fd);
// 	redirect_std_out(shell->write_fd);
// 	printf("std-out fd = %d, std-in fd = %d", shell->write_fd, shell->read_fd);
// 	execute_non_built_in(shell, curr);
// }