#include "shell.h"
#include "libft.h"

void	pipe_line(t_shell *shell)
{
	t_command	*curr;
	int			pipefd[2];
	int			status;
	pid_t		pid;

	curr = shell->command_node;
	while (curr->next)
	{
		check_hd_curr_cmd(shell, curr);
		if (pipe(pipefd) == -1)
			return ;
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
			execute_child(curr, shell, pipefd);
		shell->read_fd = pipefd[READ];
		shell->read_fd = dup(shell->read_fd);
		close(pipefd[READ]);
		close(pipefd[WRITE]);
		curr = curr->next;
	}
	check_hd_curr_cmd(shell, curr);
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
		execute_last_child(curr, shell, pipefd);
	while (pid > 0) // wait functie moet beter
		pid = waitpid(-1, &status, 0);
		// if (WIFEXITED(status) == 0) // if child terminated abnormally
		// 	shell->exit_status = status;
	return ;
}

void	execute_child(t_command *curr, t_shell *shell, int pipefd[])
{
	close(pipefd[READ]);
	redirect_std_out(pipefd[WRITE]); // als je dit niet doet blijft de write end van de pipe open en gaat voor problem zorgen
	if (handle_built_in(shell, curr))
		exit(0);// if it is a built_in, the child process needs to be killed
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
	if (handle_built_in(shell, curr))
		exit(0);// if it is a built_in, the child process needs to be killed
	if (!(curr->args[0]))
	{
		handle_redirs_curr_cmd(shell, curr);
		return ;
	}
	execute_non_built_in(shell, curr);
}
