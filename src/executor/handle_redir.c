/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:16:15 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/08/21 10:22:48 by vbrouwer         ###   ########.fr       */
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
[HEREDOC] = &handle_hd_2,
};

int	handle_redirs_curr_cmd(t_shell *shell, t_command *curr)
{
	t_redir	*redir;

	if (!curr)
		return (0);
	if (!curr->redir)
		return (0);
	redir = curr->redir;
	while (redir)
	{
		if (redir->redir_type >= GREAT && \
				redir->redir_type <= HEREDOC)
		{
			if ((g_redir_func[redir->redir_type])(redir, shell))
				return (1);
		}
		redir = redir->next;
	}
	return (0);
}

bool	redir_outfile(t_redir *curr, t_shell *shell)
{
	int	temp_fd;

	if (shell->write_fd != STDOUT_FILENO)
		close(shell->write_fd);
	temp_fd = open(curr->file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (temp_fd == -1)
		return (perror(curr->file_name), 1);
	shell->write_fd = temp_fd;
	return (SUCCESS);
}

bool	append_outfile(t_redir *curr, t_shell *shell)
{
	int	temp_fd;

	if (shell->write_fd != STDOUT_FILENO)
		close(shell->write_fd);
	temp_fd = open(curr->file_name, O_WRONLY | O_APPEND | \
													O_CREAT, 0644);
	if (temp_fd == -1)
		return (perror(curr->file_name), 1);
	shell->write_fd = temp_fd;
	return (SUCCESS);
}

bool	redir_infile(t_redir *curr, t_shell *shell)
{
	int	temp_fd;

	if (shell->read_fd != STDIN_FILENO)
		close(shell->read_fd);
	temp_fd = open(curr->file_name, O_RDONLY);
	if (temp_fd == -1)
	{
		g_status = 1;
		return (perror(curr->file_name), 1);
	}
	shell->read_fd = temp_fd;
	return (SUCCESS);
}

bool	handle_hd_2(t_redir *curr, t_shell *shell)
{
	if (curr->hd_fd != 0)
		shell->read_fd = curr->hd_fd;
	return (SUCCESS);
}
