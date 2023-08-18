/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:16:23 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/08/18 16:06:43 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

static int	execute_compound_command(t_shell *shell, t_command *curr);

void	pipe_line(t_shell *shell)
{
	t_command	*curr;
	pid_t		pid;

	curr = shell->command_node;
	while (curr->next)
	{
		if (execute_compound_command(shell, curr) == 1)
			return ;
		curr = curr->next;
	}
	if (handle_redirs_curr_cmd(shell, curr) == 1)
		return (set_status(1));
	pid = fork();
	if (pid == -1)
		return (print_error_and_set_status("fork fail", 1));
	if (pid == 0)
		execute_last_child(curr, shell);
	if (shell->read_fd != STDIN_FILENO)
		close(shell->read_fd);
	update_status(pid);
	while (wait(NULL) > 0)
		continue ;
	return ;
}

static int	execute_compound_command(t_shell *shell, t_command *curr)
{
	int			pipefd[2];
	pid_t		pid;

	if (handle_redirs_curr_cmd(shell, curr) == 1)
	{
		shell->read_fd = -1;
		return (set_status(1), 0);
	}
	if (pipe(pipefd) == -1)
		return (print_error_and_set_status("pipe fail", 1), 1);
	pid = fork();
	if (pid == -1)
		return (print_error_and_set_status("fork fail", 1), 1);
	if (pid == 0)
		execute_child(curr, shell, pipefd);
	if (shell->read_fd != STDIN_FILENO)
		close(shell->read_fd);
	shell->read_fd = dup(pipefd[READ]);
	close(pipefd[READ]);
	close(pipefd[WRITE]);
	return (0);
}

void	execute_child(t_command *curr, t_shell *shell, int pipefd[])
{
	close(pipefd[READ]);
	redirect_std_out(pipefd[WRITE]);
	if (!(curr->args[0]))
	{
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
		// if (handle_redirs_curr_cmd(shell, curr) == 1)
		// 	exit(1);
		close_open_fds(shell);
		exit(0);
	}
	if (check_built_in(curr))
		exit(handle_built_in(shell, curr));
	execute_non_built_in(shell, curr);
}
