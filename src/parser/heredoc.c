#include "shell.h"
#include "libft.h"

void	check_hd_curr_cmd(t_shell *shell, t_command *curr)
{
	t_redir *redir;

	if (!curr)
		return ;
	if (!curr->redir)
		return ;
	redir = curr->redir;
	while (redir)
	{
		if (redir->redir_type == HEREDOC)
			handle_hd(shell, redir->file_name);
		redir = redir->next;
	}
}

void	handle_hd(t_shell *shell, char *hd_delim)
{
	char	*line;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return ;// handle errors
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
	shell->read_fd = pipefd[READ]; // unsure if the old read needs to be closed with multiple heredocs in  single command
}

