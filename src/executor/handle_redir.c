/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:16:15 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/08/15 14:09:23 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

typedef bool						(*t_redir_jumpt_table)	(t_redir *curr, \
															t_shell *shell);

static const t_redir_jumpt_table	g_redir_func[] = {
[GREAT] = &redir_outfile,
[APPEND] = &append_outfile,
[LESS] = &redir_infile,
[HEREDOC] = &handle_hd,
};

void	handle_redirs_curr_cmd(t_shell *shell, t_command *curr)
{
	t_redir	*redir;

	if (!curr)
		return ;
	if (!curr->redir)
		return ;
	redir = curr->redir;
	while (redir)
	{
		if (redir->redir_type >= GREAT && \
				redir->redir_type <= HEREDOC)
		{
			if ((g_redir_func[redir->redir_type])(redir, shell))
				return ;
		}
		redir = redir->next;
	}
	return ;
}

bool	redir_outfile(t_redir *curr, t_shell *shell)
{
	if (shell->write_fd != STDOUT_FILENO)
		close(shell->write_fd);
	shell->write_fd = open(curr->file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (shell->write_fd == -1)
		return (perror(curr->file_name), ERROR);
	return (SUCCESS);
}

bool	append_outfile(t_redir *curr, t_shell *shell)
{
	if (shell->write_fd != STDOUT_FILENO)
		close(shell->write_fd);
	shell->write_fd = open(curr->file_name, O_WRONLY | O_APPEND | \
													O_CREAT, 0644);
	if (shell->write_fd == -1)
		return (perror(curr->file_name), ERROR);
	return (SUCCESS);
}

bool	redir_infile(t_redir *curr, t_shell *shell)
{
	if (shell->read_fd != STDIN_FILENO)
		close(shell->read_fd);
	shell->read_fd = open(curr->file_name, O_RDONLY);
	if (shell->read_fd == -1)
	{
		g_status = 1;
		return (perror(curr->file_name), ERROR);
	}
	return (SUCCESS);
}

bool	handle_hd(t_redir *curr, t_shell *shell)
{
	char	*line;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (print_error_and_set_status("pipe fail", 1), ERROR);
	line = readline("> ");
	while (line && !(strings_equal(line, curr->file_name)))
	{
		write(pipefd[WRITE], line, ft_strlen(line));
		write(pipefd[WRITE], "\n", 1);
		free(line);
		line = readline("> ");
	}
	if (line)
		free(line);
	close(pipefd[WRITE]);
	if (shell->read_fd != STDIN_FILENO)
		close(shell->read_fd);
	shell->read_fd = pipefd[READ];
	return (SUCCESS);
}
