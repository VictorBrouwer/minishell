#include "shell.h"
#include "libft.h"

static int	read_hd_lines(int pipefd, const char *hd_delim);
static int	update_status_hd(int status, int fd);

int	check_hd_curr_cmd(t_command *curr)
{
	t_redir	*redir;

	if (!curr)
		return (0);
	if (!curr->redir)
		return (0);
	redir = curr->redir;
	while (redir)
	{
		if (redir->redir_type == HEREDOC)
		{
			if (handle_hd(redir))
				return (1);
		}
		redir = redir->next;
	}
	return (0);
}

bool	handle_hd(t_redir *curr)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (curr->hd_fd != 0)
		close(curr->hd_fd);
	if (pipe(pipefd) == -1)
		return (print_error_and_set_status("pipe fail", 1), ERROR);
	init_signals(3);
	pid = fork();
	if (pid == -1)
		return (print_error_and_set_status("fork fail", 1), ERROR);
	if (pid == 0)
	{
		close(pipefd[READ]);
		read_hd_lines(pipefd[WRITE], curr->file_name);
	}
	close(pipefd[WRITE]);
	waitpid(pid, &status, 0);
	init_signals(1);
	rl_catch_signals = 0;
	if (update_status_hd(status, pipefd[READ]) == 1)
		return (1);
	curr->hd_fd = pipefd[READ];
	return (SUCCESS);
}

static int	read_hd_lines(int pipefd, const char *hd_delim)
{
	char	*line;

	init_signals(2);
	line = readline("> ");
	while (line && !(strings_equal(line, hd_delim)))
	{
		write(pipefd, line, ft_strlen(line));
		write(pipefd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	if (line)
		free(line);
	close(pipefd);
	exit(0);
}

static int	update_status_hd(int status, int fd)
{
	if (WEXITSTATUS(status) == 1)
	{
		g_status = 1;
		close(fd);
		return (1);
	}
	return (0);
}
