#include "shell.h"
#include "libft.h"

void	check_hd_curr_cmd(t_shell *shell_str)
{
	t_redir *redir;

	if (!shell_str->command_node)
		return ;
	if (!shell_str->command_node->redir)
		return ;
	redir = shell_str->command_node->redir;
	while (redir)
	{
		if (redir->redir_type == HEREDOC)
			handle_hd(shell_str, redir->file_name);
		redir = redir->next;
	}
}

void	handle_hd(t_shell *shell_str, char *hd_delim)
{
	char	*line;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return ;// handle errors
	line = readline("> ");
	while (line && !(strings_equal(line, hd_delim)))
	{
		write(pipefd[WRITE], line, ft_strlen(line));
		free(line);
		line = readline("> ");
	}
	if (line)
		free(line);
	close(pipefd[WRITE]);
	shell_str->read_fd = pipefd[READ]; // unsure if the old read needs to be closed with multiple heredocs in  single command
}

bool	strings_equal(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (false);
		s1++;
		s2++;
	}
	return (*s1 == '\0' && *s2 == '\0');
}