#include "shell.h"
#include "libft.h"

static int	read_hd_lines(int pipefd, const char *hd_delim);
static int	update_status_hd(int status, int fd);

bool	handle_hd(t_redir *curr, t_shell *shell)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipefd) == -1)
		return (print_error_and_set_status("pipe fail", 1), ERROR);
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
	if (update_status_hd(status, pipefd[READ]) == 1)
		return (1);
	if (shell->read_fd != STDIN_FILENO)
		close(shell->read_fd);
	shell->read_fd = pipefd[READ];
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
