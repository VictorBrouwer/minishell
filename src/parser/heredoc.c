/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:17:45 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/08/11 10:17:46 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

static int	handle_hd(t_shell *shell, char *hd_delim);

void	check_hd_curr_cmd(t_shell *shell, t_command *curr)
{
	t_redir	*redir;

	if (!curr)
		return ;
	if (!curr->redir)
		return ;
	redir = curr->redir;
	while (redir)
	{
		if (redir->redir_type == HEREDOC)
		{
			if (handle_hd(shell, redir->file_name) == -1)
				return ;
		}
		redir = redir->next;
	}
}

static int	handle_hd(t_shell *shell, char *hd_delim)
{
	char	*line;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);
	line = readline("> ");
	while (line && !(strings_equal(line, hd_delim)))
	{
		write(pipefd[WRITE], line, ft_strlen(line));
		write(pipefd[WRITE], "\n", 1);
		free(line);
		line = readline("> ");
	}
	if (line)
		free(line);
	close(pipefd[WRITE]);
	shell->read_fd = pipefd[READ];
	return (0);
}
