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
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
			execute_child(curr, shell, pipefd);
		close(pipefd[WRITE]);
		if (shell->read_fd != STDIN_FILENO) // als read fd iets anders is dan stdin moet ie nog gesloten worden van de vorige keer
			close (shell->read_fd);
		shell->read_fd = pipefd[READ];
		shell->read_fd = dup(shell->read_fd);
		close(pipefd[READ]);
		curr = curr->next;
	}
	check_hd_curr_cmd(shell, curr);
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
		execute_last_child(curr, shell, pipefd);
	close(shell->read_fd);
	while (wait(NULL) > 0)
		continue ;
	update_status(pid);
	return ;
}

void	execute_child(t_command *curr, t_shell *shell, int pipefd[])
{
	close(pipefd[READ]);
	redirect_std_out(pipefd[WRITE]); // als je dit niet doet blijft de write end van de pipe open en gaat voor problem zorgen
	if (!(curr->args[0]))
	{
		handle_redirs_curr_cmd(shell, curr);
		exit(0);
	}
	if (check_built_in(curr))
		handle_built_in(shell, curr);
	else
		execute_non_built_in(shell, curr);
	exit(glob_status);// if it is a built_in or the non_built-in does not exit for some reason, the child process needs to be killed
}

void	execute_last_child(t_command *curr, t_shell *shell, int pipefd[])
{
	close(pipefd[READ]);
	close(pipefd[WRITE]);
	shell->write_fd = STDOUT_FILENO; // set standard write_fd to STDOUT and handle redirs afterwards
	if (!(curr->args[0]))
	{
		handle_redirs_curr_cmd(shell, curr);
		exit(0);
	}
	if (check_built_in(curr))
		handle_built_in(shell, curr);
	else
		execute_non_built_in(shell, curr);
	exit(glob_status);// if it is a built_in or the non_built-in does not exit for some reason, the child process needs to be killed
}
